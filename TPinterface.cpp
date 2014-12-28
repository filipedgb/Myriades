#include "TPinterface.h"
#include "ProjScene.h"

#include <iostream> 

TPinterface::TPinterface() {}

void TPinterface::initGUI() {
	//main panel
	GLUI_Panel* panel = addPanel("Environment Options",1); 

	//adding panel for controling lights
	GLUI_Panel *lights = addPanelToPanel(panel,"Lights",1);

	//adding checkBoxes for each light to the panel
	addCheckboxToPanel(lights, "default", &(((ProjScene*) scene)->lightState[0]),0);

	for(unsigned int i=1; i < ((ProjScene*)scene)->lightState.size(); i++) {
		char* a = (char*) ((ProjScene*) scene)->getLights()[i-1]->getId();
		addCheckboxToPanel(lights, a, &(((ProjScene*) scene)->lightState[i]), i);
	}
	//add column
	addColumnToPanel(panel);

	//add centered panel for drawing options
	GLUI_Panel *drawing = addPanelToPanel(panel,"Drawing",1);

	//MODE
	GLUI_Panel *modeP = addPanelToPanel(drawing,"Mode",1);

	//adding radio button to toggle mode
	GLUI_RadioGroup *mode = addRadioGroupToPanel(modeP,&(((ProjScene*) scene)->mode),8);

	addRadioButtonToGroup(mode, "Fill");
	addRadioButtonToGroup(mode, "Line");
	addRadioButtonToGroup(mode, "Point");

	addColumnToPanel(drawing);

	//SHADING
	GLUI_Panel *shadingP = addPanelToPanel(drawing,"Shading",1);

	//adding radio button to toggle mode
	GLUI_RadioGroup *shading = addRadioGroupToPanel(shadingP, &(((ProjScene*) scene)->shading),9);

	addRadioButtonToGroup(shading, "Flat");
	addRadioButtonToGroup(shading, "Gouraud");

	//CAMERAS
	GLUI_Panel *cameras = addPanelToPanel(panel, "Cameras",1);

	GLUI_RadioGroup *camera = addRadioGroupToPanel(cameras, &(((ProjScene*) scene)->cameraState),10);

	addRadioButtonToGroup(camera, "Free View");
	//adding checkBoxes for each camera to the panel
	for(unsigned int i=0; i<((ProjScene*)scene)->getCameras().size();i++) {
		addRadioButtonToGroup(camera, ((ProjScene*)scene)->getCameras()[i]->getId());
	}

	addColumnToPanel(panel);


	//////////////////////////////////
	//game panel
	GLUI_Panel* gamePanel = addPanel("Game",1); 

	GLUI_Button* addPiece = addButtonToPanel(gamePanel,"addPiece",11);
	GLUI_Button* movePiece = addButtonToPanel(gamePanel,"movePiece",12);
}

void TPinterface::processGUI(GLUI_Control *ctrl)
{
	printf ("GUI control id: %d\n  ",ctrl->user_id);

	switch (ctrl->user_id)
	{
	case 0:
		printf ("Light 0: %d\n",(((ProjScene*) scene)->lightState[0]));
		break;
	case 1:
		printf ("Light 1: %d\n",(((ProjScene*) scene)->lightState[1]));
		break;
	case 2:
		printf ("Light 2: %d\n",(((ProjScene*) scene)->lightState[2]));
		break;
	case 3:
		printf ("Light 3: %d\n",(((ProjScene*) scene)->lightState[3]));
		break;
	case 4:
		printf ("Light 4: %d\n",(((ProjScene*) scene)->lightState[4]));
		break;
	case 5:
		printf ("Light 5: %d\n",(((ProjScene*) scene)->lightState[5]));
		break;
	case 6:
		printf ("Light 6: %d\n",(((ProjScene*) scene)->lightState[6]));
		break;
	case 7:
		printf ("Light 7: %d\n",(((ProjScene*) scene)->lightState[7]));
		break;
	case 8:
		printf("Mode: %d\n",(((ProjScene*) scene)->mode));
		break;
	case 9:
		printf("Shading: %d\n",(((ProjScene*) scene)->shading));
		break;
	case 10:
		printf("Camera: %d\n",(((ProjScene*) scene)->cameraState));
		break;
	case 11:
		printf("Button addPiece\n");
		break;
	case 12:
		printf("Button movePiece\n");
		break;
	};
}


// buffer to be used to store the hits during picking
#define BUFSIZE 256
GLuint selectBuf[BUFSIZE];

void TPinterface::processMouse(int button, int state, int x, int y) 
{
	CGFinterface::processMouse(button,state, x, y);

	// do picking on mouse press (GLUT_DOWN)
	// this could be more elaborate, e.g. only performing picking when there is a click (DOWN followed by UP) on the same place
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		performPicking(x,y);
}

void TPinterface::performPicking(int x, int y) {
	// Sets the buffer to be used for selection and activate selection mode
	glSelectBuffer (BUFSIZE, selectBuf);
	glRenderMode(GL_SELECT);

	// Initialize the picking name stack
	glInitNames();

	// The process of picking manipulates the projection matrix
	// so we will be activating, saving and manipulating it
	glMatrixMode(GL_PROJECTION);

	//store current projmatrix to restore easily in the end with a pop
	glPushMatrix();

	//get the actual projection matrix values on an array of our own to multiply with pick matrix later
	GLfloat projmat[16];
	glGetFloatv(GL_PROJECTION_MATRIX,projmat);

	// reset projection matrix
	glLoadIdentity();

	// get current viewport and use it as reference for 
	// setting a small picking window of 5x5 pixels around mouse coordinates for picking
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	// this is multiplied in the projection matrix
	gluPickMatrix((GLdouble) x, (GLdouble) (CGFapplication::height - y), 5.0, 5.0, viewport);

	// multiply the projection matrix stored in our array to ensure same conditions as in normal render
	glMultMatrixf(projmat);

	// force scene drawing under this mode
	// only the names of objects that fall in the 5x5 window will actually be stored in the buffer
	scene->display();

	// restore original projection matrix
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glFlush();

	// revert to render mode, get the picking results and process them
	GLint hits;
	hits = glRenderMode(GL_RENDER);
	processHits(hits, selectBuf);
}

void TPinterface::processHits(GLint hits, GLuint buffer[]) 
{
	GLuint *ptr = buffer;
	GLuint mindepth = 0xFFFFFFFF;
	GLuint *selected=NULL;
	GLuint nselected;

	// iterate over the list of hits, and choosing the one closer to the viewer (lower depth)
	for (int i=0;i<hits;i++) {
		int num = *ptr; ptr++;
		GLuint z1 = *ptr; ptr++;
		ptr++;
		if (z1 < mindepth && num>0) {
			mindepth = z1;
			selected = ptr;
			nselected=num;
		}
		for (int j=0; j < num; j++) 
			ptr++;
	}

	// if there were hits, the one selected is in "selected", and it consist of nselected "names" (integer ID's)
	if (selected!=NULL)
	{
		// this should be replaced by code handling the picked object's ID's (stored in "selected"), 
		// possibly invoking a method on the scene class and passing "selected" and "nselected"
		printf("Picked ID's: ");

		((ProjScene*)scene)->setSelectedCoords(selected[0],selected[1]);

		for (unsigned int i=0; i<nselected; i++) { 
			printf("%d ",selected[i]);
		}
		printf("\n");
	}
	else
		printf("Nothing selected while picking \n");	
}


