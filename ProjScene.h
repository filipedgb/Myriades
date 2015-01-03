#ifndef PROJSCENE_H
#define PROJSCENE_H

#include <math.h>
#include <iostream>
#include "CGFscene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include "Light.h"

#include "Clock.h"

#include "Perspective.h"
#include "Ortho.h"

#include "Animation.h"

#include "Board.h"
#include "Socket.h"


class ProjScene : public CGFscene {
private:
	CGFlight* light0;
	vector<Light*> lights;
	vector<Camera*> cameras; 
	vector<Animation*> animations;

	Clock* cronometro;

	Perspective* mainCamera;

	vector<vector<CGFtexture*>> ambients;	//each i is a vector to use in all pieces-board/boardBox
	vector<string> ambientID;					//id to show in interface

	char currentPlayer;
	int oldX, oldY, newX,newY;
	int movedX, movedY;
	bool hasMoved, toMove;
	int removes;

	float initialTime;
	float timePassed;


	Board theBoard;
	Board lastMove;

	vector<Board> moves;
	CtoPlSocket sck;

	bool replaying;
	int replayingIndex;
	unsigned long oldT;

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

	void setTransitionalCameras(vector<vector3d> coordinates);

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

	float cameraRotation[16];
	void rotateCamera();
	float cameraTranslationXY[2];
	float cameraTranslationZ;
	void translateCamera();
	void resetCameras();

	/* -- Ambient --*/
	int ambientState;
	void setAllAmbient();
	void addNewAmbient(string id, CGFtexture* pieceApp, CGFtexture* boardApp);
	vector<string> getAmbientID() {return ambientID;}
	void changeTextures();

	int addNewPieceValue;
	void pickingActions(int x, int y);
	void addPieceValue();
	void undo(int x);

	bool changePiece();

	int newBoardSize;
	int opponent; //0-h vs h, 1-h vs pc, 2-pc vs pc
	int level; //0- easy, 1-medium, 2-hard
	void newGame();
	void showWinner();
	void pcVSpc();

	void changeCurrentPlayer();
	void replay();
	int replayTime;
};

#endif