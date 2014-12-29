#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"

class TPinterface: public CGFinterface {
	GLUI_Spinner *segment_spinner;
	
public:
	TPinterface();

	virtual void initGUI();
	virtual void processGUI(GLUI_Control *ctrl);

	virtual void processMouse(int button, int state, int x, int y);	
	void performPicking(int x, int y);
	void processHits(GLint hits, GLuint buffer[]); 

	static GLUI_StaticText* gameOutput;

	static void setOutput(char* output) {
		gameOutput->set_text(output);
	}
};


#endif
