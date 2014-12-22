#ifndef PROJSCENE_H
#define PROJSCENE_H

#include <math.h>
#include <iostream>


#include "CGFscene.h"
#include "CGFshader.h"
#include "CGFappearance.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "Graph.h"
#include "Light.h"
#include "Texture.h"

#include "Perspective.h"
#include "Ortho.h"

#include "Animation.h"

#include "Socket.h"

class ProjScene : public CGFscene {
private:
	Grafo theGraph;
	CGFlight* light0;
	vector<Light*> lights;
	vector<Texture*> texturas;
	vector<Camera*> cameras; 
	vector<Animation*> animations;

	Animation* teste;
	CGFshader* shader;

	CtoPlSocket sck;

public:
	void init();
	void display();
	void update(unsigned long t);
	void applyMatrixDraw(Node* node, Appearance* appID);
	~ProjScene();

	void setAllAmbient();

	vector<Light*>  getLights() { return lights;}
	vector<Camera*> getCameras() { return cameras;} 

	int searchCamera(char* id);
	int searchTexture(char* id);
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
};

#endif