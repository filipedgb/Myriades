#ifndef TPinterface_H
#define TPinterface_H

#include "CGFinterface.h"

class TPinterface: public CGFinterface {
public:
	TPinterface();

	virtual void initGUI();
	virtual void processGUI(GLUI_Control *ctrl);

	virtual void processMouse(int button, int state, int x, int y);	
	void performPicking(int x, int y);
	void processHits(GLint hits, GLuint buffer[]); 

	static GLUI_StaticText* gameOutput;
	static GLUI_StaticText* currentPiece;

	static void setOutput(std::string output) {
		gameOutput->set_text(output.c_str());
	}

	static void setCurrentPiece(std::string output) {
		currentPiece->set_text(output.c_str());
	}
};


#endif
