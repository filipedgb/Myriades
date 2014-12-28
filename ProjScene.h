#ifndef PROJSCENE_H
#define PROJSCENE_H

#include <math.h>
#include <iostream>

#include "CGFscene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "Light.h"
#include "Texture.h"

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
	vector<Texture*> texturas;
	vector<Appearance*> appearances;
	vector<Camera*> cameras; 
	vector<Animation*> animations;

	int oldX, oldY, newX,newY, toMove;

	Board theBoard;

	Piece* obj;
	CtoPlSocket sck;

public:
	void init();
	void display();
	void update(unsigned long t);
	~ProjScene();

	void setAllAmbient();

	vector<Light*>  getLights() { return lights;}
	vector<Camera*> getCameras() { return cameras;} 

	int searchCamera(char* id);
	int searchTexture(char* id);
	int searchAnimation(char* id);
	int searchAppearance(char* id);

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
};

#endif