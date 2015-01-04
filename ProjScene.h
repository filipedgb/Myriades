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

	Clock* cronometro;

	Perspective* mainCamera;

	vector<vector<CGFtexture*>> ambients;	    //each i is a vector to use in all pieces-board/boardBox
	vector<string> ambientID;					//id to show in interface

	char currentPlayer;
	int oldX, oldY, newX,newY;
	int movedX, movedY;
	bool hasMoved, toMove;
	int removes;
	Piece* removePiece;

	Cube* table;
	CGFappearance* tableApp;

	float initialTime;
	float timePassed;

	Board theBoard;
	Board lastMove;

	vector<Board> moves;
	CtoPlSocket sck;

	bool replaying;
	int replayingIndex;
	float currentReplayTime;
	float initialReplayTime;

public:
	void init();
	void display();
	void update(unsigned long t);
	~ProjScene();

	CtoPlSocket* getSck() { return &sck;}

	vector<Light*>  getLights() { return lights;}
	vector<Camera*> getCameras() { return cameras;} 

	void setTransitionalCameras(vector<vector3d> coordinates);

	/** INTERFACE OPTIONS*/
	int sceneVar;
	int displayAnimations;

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
	void addNewAmbient(string id, CGFtexture* pieceApp, CGFtexture* boardApp, CGFtexture* tableApp);
	vector<string> getAmbientID() {return ambientID;}
	void changeTextures();

	int addNewPieceValue;
	void pickingActions(int x, int y);
	void addPieceValue();
	void undo();

	bool changePiece();
	bool pcPlaying;
	int waitTime;
	int initialWaitTime;

	int newBoardSize;
	int opponent; //0-h vs h, 1-h vs pc, 2-pc vs pc
	int level; //0- easy, 1-medium, 2-hard
	void newGame();
	void showWinner();
	
	void pcVSpc();
	void findMove(int &oldx, int &oldy, int &newx, int &newy,vector<int> &removesVec, const Board& oldboard,const Board& newboard);
	void findAdd(int &num, char &color, int &x, int &y,const Board& oldboard,const Board& newboard);
	void pcRemovePieces(int number);
	void pcMove();
	void pcAdd();

	void changeCurrentPlayer();
	void replay();
	int replayTime;
	int playTime;
	void changePlayLimit();
};

#endif