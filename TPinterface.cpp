#include "TPinterface.h"
#include "ProjScene.h"

#include <iostream> 

TPinterface::TPinterface()
{
}

void TPinterface::initGUI()
{
	//main panel
	GLUI_Panel* panel = addPanel("Options",1); 

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
	};
}

