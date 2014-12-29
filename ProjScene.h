#ifndef PROJSCENE_H
#define PROJSCENE_H

#include <math.h>
#include <iostream>

#include "CGFscene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "Light.h"

#include "Perspective.h"
#include "Ortho.h"

#include "Animation.h"

#include "Piece.h"
#include "Board.h"
#include "Socket.h"

class ProjScene : public CGFscene {
private:
	CGFlight* light0;
	vector<Light*> lights;
	vector<Camera*> cameras; 
	vector<Animation*> animations;

	char currentPlayer;

	int oldX, oldY, newX,newY, value;
	int movedX, movedY;
	bool hasMoved, toMove;

	Board theBoard;

	vector<Board> moves;

	Piece* obj;
	CtoPlSocket sck;

public:
	void init();
	void display();
	void update(unsigned long t);
	~ProjScene();

	void setAllAmbient();

	CtoPlSocket* getSck() { return &sck;}

	vector<Light*>  getLights() { return lights;}
	vector<Camera*> getCameras() { return cameras;} 

	int searchCamera(char* id);
	int searchAnimation(char* id);

	/** INTERFACE OPTIONS*/
	int sceneVar;

	/* -- LIGHTS -- */
	vector<int> lightState;

	//use set when creating
	void setLightState(); 
	void updateLightState();

	/* -- DRAWING -- */
	int mode, shading;
	void updateDrawing();

	/* -- CAMERAS -- */
	int cameraState;
	void setInitialCamera();	

	void setSelectedCoords(int x, int y);
	void addPieceValue(float value);
	void undo();
};

#endif