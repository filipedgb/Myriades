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

	vector<vector<CGFtexture*>> ambients;	//each i is a vector to use in all pieces-board/boardBox
	vector<string> ambientID;					//id to show in interface

	char currentPlayer;
	int oldX, oldY, newX,newY;
	int movedX, movedY;
	bool hasMoved, toMove;

	Board theBoard;

	vector<Board> moves;
	CtoPlSocket sck;

public:
	void init();
	void display();
	void update(unsigned long t);
	~ProjScene();

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

	/* -- Ambient --*/
	int ambientState;
	void setAllAmbient();
	void addNewAmbient(string id, CGFtexture* pieceApp, CGFtexture* boardApp);
	vector<string> getAmbientID() {return ambientID;}
	void changeTextures();

	int addNewPieceValue;
	void setSelectedCoords(int x, int y);
	void addPieceValue();
	void undo();

	int newBoardSize;
	void newGame();
};

#endif