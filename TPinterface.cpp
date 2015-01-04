#include "TPinterface.h"
#include "ProjScene.h"

TPinterface::TPinterface() {}

GLUI_StaticText* TPinterface::gameOutput = new GLUI_StaticText();
GLUI_StaticText* TPinterface::currentPiece = new GLUI_StaticText();

void TPinterface::initGUI() {

	//game panel
	GLUI_Panel* gamePanel = addPanel("Game",1); 

	GLUI_Rollout* newGameR = addRolloutToPanel(gamePanel,"New Game",0);
	GLUI_Button* newGame = addButtonToPanel(newGameR,"Start",12);
	GLUI_Spinner *boardSize = addSpinnerToPanel(newGameR,"Board size: ", GLUI_SPINNER_INT,&(((ProjScene*) scene)->newBoardSize));
	boardSize->set_int_limits(3,11, GLUI_LIMIT_WRAP);
	boardSize->set_int_val(5);

	GLUI_RadioGroup* opponent = addRadioGroupToPanel(newGameR,&(((ProjScene*)scene)->opponent));
	addRadioButtonToGroup(opponent,"Human vs Human");
	addRadioButtonToGroup(opponent,"Human vs PC");
	addRadioButtonToGroup(opponent,"PC vs PC");

	addSeparatorToPanel(newGameR);

	GLUI_RadioGroup* level = addRadioGroupToPanel(newGameR,&(((ProjScene*)scene)->level));
	addRadioButtonToGroup(level,"Easy");
	addRadioButtonToGroup(level,"Medium");
	addRadioButtonToGroup(level,"Hard");

	GLUI_Panel* addPieceP = addPanelToPanel(gamePanel,"",GLUI_PANEL_NONE);
	GLUI_Button* addPiece = addButtonToPanel(addPieceP,"Add Piece",11);
	addColumnToPanel(addPieceP);
	GLUI_Spinner *pieceValue = addSpinnerToPanel(addPieceP,"Value: ", GLUI_SPINNER_INT,&(((ProjScene*) scene)->addNewPieceValue));
	pieceValue->set_int_limits(0,49, GLUI_LIMIT_WRAP);
	pieceValue->set_int_val(0);

	GLUI_Panel* replayP = addPanelToPanel(gamePanel,"",GLUI_PANEL_NONE);
	GLUI_Button* replay = addButtonToPanel(replayP,"Replay",17);
	addColumnToPanel(replayP);
	GLUI_Rollout* replayR = addRolloutToPanel(replayP,"Time",0,0);
	GLUI_Spinner* replayTime = addSpinnerToPanel(replayR,"Replay Time",2,&(((ProjScene*) scene)->replayTime));
	replayTime->set_int_limits(1,30, GLUI_LIMIT_WRAP);

	GLUI_EditText* playTime = addEditTextToPanel(replayR,"Move time",&(((ProjScene*) scene)->playTime),19);
	playTime->set_int_limits(30,5*60, GLUI_LIMIT_WRAP);

	GLUI_Panel* tempPanel = addPanelToPanel(gamePanel,"",GLUI_PANEL_NONE);
	GLUI_Button* undo = addButtonToPanel(tempPanel,"Undo player move",14);
	addColumnToPanel(tempPanel);
	GLUI_Button* exitGame = addButtonToPanel(tempPanel,"Exit Game",15);

	////////////////////////////////////////////////////////////////////////////////////////////
	addColumn();

	GLUI_Panel* output = addPanel("Output",1); 
	gameOutput = addStaticTextToPanel(output,"Move or add a piece.");

	addSeparatorToPanel(output);
	currentPiece = addStaticTextToPanel(output,"No piece selected.");

	addColumn();

	/////////////////////////////////////////////////////////////////////////////////////////////

	//options panel
	GLUI_Rollout* panel = addRollout("Environment Options",0);

	//add ambient
	GLUI_Listbox *ambient = addListboxToPanel(panel,"Ambient ",&(((ProjScene*) scene)->ambientState),16);
	for(unsigned int i = 0; i < ((ProjScene*) scene)->getAmbientID().size(); i++) {
		ambient->add_item(i, ((ProjScene*) scene)->getAmbientID()[i].c_str());
	}

	//add centered panel for drawing options
	GLUI_Rollout *drawing = addRolloutToPanel(panel,"Drawing",0);

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

	//adding panel for controling lights
	GLUI_Rollout *lights = addRolloutToPanel(panel,"Lights",0);

	//adding checkBoxes for each light to the panel
	addCheckboxToPanel(lights, "default", &(((ProjScene*) scene)->lightState[0]),0);

	for(unsigned int i = 1; i < ((ProjScene*)scene)->lightState.size(); i++) {
		char* a = (char*) ((ProjScene*) scene)->getLights()[i-1]->getId();
		addCheckboxToPanel(lights, a, &(((ProjScene*) scene)->lightState[i]), i);
	}

	//add column
	addColumnToPanel(panel);

	//CAMERAS
	GLUI_Rollout *cameras = addRolloutToPanel(panel, "Cameras",0);

	GLUI_Panel* tempCameras = addPanelToPanel(cameras,"",GLUI_PANEL_NONE);

	GLUI_Rollout *changeCamera = addRolloutToPanel(tempCameras, "Change camera",0);

	GLUI_RadioGroup *camera = addRadioGroupToPanel(changeCamera, &(((ProjScene*) scene)->cameraState),10);

	addRadioButtonToGroup(camera, "Free View");
	//adding radio buttons for each camera to the panel
	for(unsigned int i=0; i<((ProjScene*)scene)->getCameras().size();i++) {
		addRadioButtonToGroup(camera, ((ProjScene*)scene)->getCameras()[i]->getId());
	}

	addColumnToPanel(tempCameras);

	GLUI_Rollout* moveCameras = addRolloutToPanel(tempCameras,"Move camera",0);

	GLUI_Panel* translationP = addPanelToPanel(moveCameras,"",GLUI_PANEL_NONE);
	GLUI_Rotation* rot = addRotationToPanel(translationP,"Rotation", ((ProjScene*)scene)->cameraRotation, 20); 

	addSeparatorToPanel(translationP);

	GLUI_Panel* translationP1 = addPanelToPanel(translationP,"",GLUI_PANEL_NONE);

	GLUI_Translation* transXY = addTranslationToPanel(translationP1,"Translation xy", GLUI_TRANSLATION_XY, ((ProjScene*)scene)->cameraTranslationXY, 21);
	transXY->set_speed(0.005);
	addColumnToPanel(translationP1);
	GLUI_Translation* transZ = addTranslationToPanel(translationP1,"Translation z", GLUI_TRANSLATION_Z, &((ProjScene*)scene)->cameraTranslationZ, 21); 
	transZ->set_speed(0.005);
}

void TPinterface::processGUI(GLUI_Control *ctrl) {
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
		((ProjScene*) scene)->resetCameras();
		break;
	case 11:
		printf("Button addPiece\n");
		((ProjScene*) scene)->addPieceValue();
		break;
	case 12:
		printf("Button new Game\n");
		((ProjScene*) scene)->newGame();
		break;
	case 14:
		printf("Button player undo\n");
		((ProjScene*) scene)->undo();
		break;
	case 15:
		printf("Button exit game\n");
		((ProjScene*) scene)->getSck()->quit();
		exit(0);
		break;
	case 16:
		printf("Change ambient\n");
		((ProjScene*) scene)->changeTextures();
		break;
	case 17:
		printf("Replay game\n");
		((ProjScene*) scene)->replay();
		break;
	case 18:
		printf("Play time\n");
		((ProjScene*) scene)->changePlayLimit();
		break;
	case 20:
		printf("Moving Camera\n");
		break;
	case 21:
		printf("Moving Camera\n");
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

		((ProjScene*)scene)->pickingActions(selected[0],selected[1]);

		for (unsigned int i=0; i<nselected; i++) { 
			printf("%d ",selected[i]);
		}
		printf("\n");
	}
	else
		printf("Nothing selected while picking \n");	
}


