#include "TPinterface.h"
#include <Windows.h>
#include "ProjScene.h"
#include <time.h>


GLfloat ambientLight[4] = {0.8, 0.8, 0.8, 1};
GLfloat background[4] = {0, 0, 0, 0.8};

void ProjScene::updateDrawing() {
	switch(this->mode) {
	case 0: //fill
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 1: //line
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 2: //point
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	}

	switch(this->shading) {
	case 0:
		glShadeModel(GL_FLAT);
		break;
	case 1:
		glShadeModel(GL_SMOOTH);
		break;
	}
}

void ProjScene::setAllAmbient() {
	int size = theBoard.getSize();

	printf("Size: %d\n", size);

	GLfloat p1Pos[3] = {size,1,size+1};
	GLfloat p1Tar[3] = {size,0,size};
	GLfloat p2Pos[3] = {10,1,9};
	GLfloat p2Tar[3] = {10,0,10};
	//mudar isto
	GLfloat p3Pos[3] = {size,10,-size*2+1};
	GLfloat p3Tar[3] = {size,0,-size*2};

	/* CAMARAS */
	mainCamera = new Perspective("Sided Camera",0,0,0,p1Pos,p1Tar);;
	Perspective* p1 = new Perspective("p1",0,0,0,p1Pos,p1Tar);
	Perspective* p2 = new Perspective("p2",0,0,0,p2Pos,p2Tar);
	Perspective* p3 = new Perspective("p3",0,0,0,p3Pos,p3Tar);

	mainCamera->calculatePoints();
	mainCamera->setRotative();
	cameras.push_back(mainCamera);
	cameras.push_back(p1);
	cameras.push_back(p2);
	cameras.push_back(p3);

	/*Lights*/
	GLfloat l1Pos[3] = {0,15,3};
	GLfloat ambientl1[4] = {0.2,0.2,0.2,0.1};
	GLfloat diffusel1[4] = {0.4,0.4,0.4,0.1};
	GLfloat specularl1[4] = {0.5,0.5,0.5,0.1};
	Light* l1 = new Light("Omni", "omni",true,true,l1Pos,ambientl1,diffusel1,specularl1);

	lights.push_back(l1);

	/*Ambient*/
	CGFtexture* woodPiece = new CGFtexture("woodPiece.jpg");
	CGFtexture* woodBoard = new CGFtexture("woodBoard.jpg");

	addNewAmbient("Wood",woodPiece,woodBoard);

	CGFtexture* porcelainPiece = new CGFtexture("porcelainPiece.jpg");
	CGFtexture* porcelainBoard = new CGFtexture("porcelainBoard.jpg");

	addNewAmbient("Porcelain",porcelainPiece,porcelainBoard);

	CGFtexture* metalPiece = new CGFtexture("metalPiece.jpg");
	CGFtexture* metalBoard = new CGFtexture("metalBoard.jpg");

	addNewAmbient("Metal",metalPiece,metalBoard);
}

void ProjScene::addNewAmbient(string id, CGFtexture* pieceApp, CGFtexture* boardApp) {
	vector<CGFtexture*> ambient;

	ambientID.push_back(id);

	ambient.push_back(pieceApp);
	ambient.push_back(boardApp);

	ambients.push_back(ambient);
}

void ProjScene::pickingActions(int x, int y) { 
	if(removes > 0) { 
		oldX = x;
		oldY = y;

		string out = "You have ";
		out.append(to_string(removes));
		out.append(" adjacent pieces.\n");

		if(sck.numPieces(currentPlayer,&theBoard) < 2) { //cant change piece that moved
			removes = 0;
			return;
		}

		Piece * piece = theBoard.getPiece(x,y);

		if(piece != NULL) { 
			printf("Going to remove piece from %d %d\n",oldX,oldY);

			if(changePiece())
				removes--;
			TPinterface::setOutput(out);

			printf("Number of removes: %d\n", removes);
		}

		if(removes > 0) out = "You must remove a piece now";
		else out = "Now add a piece.\n";

		TPinterface::setOutput(out);
	}
	else if(!hasMoved && toMove) { //ja escolheu peca para mover
		newX = x;
		newY = y;

		theBoard.boardParser(sck.movePiece(&theBoard,oldX,oldY,newX,newY));
		theBoard.setScore(sck.sumOf('b',&theBoard),sck.sumOf('w',&theBoard));

		if(moves.empty() || theBoard != moves[moves.size()-1]) {
			toMove = false;
			hasMoved = true;
			moves.push_back(theBoard);
			movedX = newX;			//guardar para nao poder retirar a peca que acabou de mover
			movedY = newY;

			theBoard.getPiece(movedX,movedY)->setMoving(oldX,oldY,movedX,movedY,theBoard.getSize());

			string out = "Player ";
			out+= currentPlayer;
			out.append(": moved a piece.\n");
			TPinterface::setOutput(out);

			removes = sck.numberOfAdjacentes(movedX,movedY,&theBoard);

			if(removes > 0) out = "You must remove a piece now";
			else out = "Now add a piece.\n";

			TPinterface::setOutput(out);
		}
		else {
			string out = "Can't make that move.\n";
			TPinterface::setOutput(out);
		}
	}
	else {

		oldX = x;
		oldY = y;

		Piece * piece = theBoard.getPiece(x,y);
		if(piece != NULL) {
			string pout;
			if(piece->getColor() == 'b') pout= "Black ";
			else if(piece->getColor() == 'w') pout = "White ";
			else if(piece->getColor() == 'g') pout = "Gray ";
			pout.append("piece. Value = ");
			pout.append(to_string(piece->getNumber()));

			TPinterface::setCurrentPiece(pout);

			if(piece->getColor() == currentPlayer) {
				toMove = true;
			}
		}
		else TPinterface::setCurrentPiece("No piece selected");
	}
}

void ProjScene::init() {
	resetCameras();

	currentPlayer = 'b';
	toMove = false;
	hasMoved = false;
	opponent = 0;
	level = 0;
	removes = 0;
	initialTime = 0;
	timePassed = 0;

	replaying = false;
	replayingIndex = 0;
	replayTime = 3;
	currentReplayTime = 0;
	initialReplayTime = 0;

	theBoard = Board(4);
	sck.socketConnect();

	cronometro = new Clock();
	playTime = cronometro->getTimeLimit();

	theBoard.boardParser(sck.initBoard(theBoard.getSize())); //Socket

	setAllAmbient();

	moves.push_back(theBoard);

	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(0,'w'),0,0));
	moves.push_back(theBoard);
	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(31,'b'),0,1));
	moves.push_back(theBoard);
	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(21,'w'),1,0));
	moves.push_back(theBoard);
	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(0,'g'),2,1));
	moves.push_back(theBoard);
	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(40,'b'),2,2));
	moves.push_back(theBoard);
	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(41,'b'),1,1));
	moves.push_back(theBoard);
	theBoard.setScore(sck.sumOf('b',&theBoard),sck.sumOf('w',&theBoard));
	lastMove = theBoard;

	setUpdatePeriod(50);

	/* init values */
	mode = 0;
	shading = 1;
	cameraState = 0;
	setLightState();
	ambientState = 0;
	changeTextures();

	// Enables lighting computations
	glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);  // Define ambient light

	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);

	glClearColor(background[0],background[1],background[2],background[3]);

	// Declares and enables a light
	float light0_pos[4] = {4.0, 6.0, 5.0, 1.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);

	// Defines a default normal
	glNormal3f(0,0,1);

	glEnable(GL_NORMALIZE);

	system("pause");
}

void ProjScene::update(unsigned long t) {
	for(int i = 0; i < theBoard.getSize(); i++)
		for(int k = 0; k <  theBoard.getSize(); k++) {
			if(theBoard.getPiece(i,k) != NULL && theBoard.getPiece(i,k)->isNew())
				theBoard.getPiece(i,k)->getAddingAnimation()->update(t);

			if(theBoard.getPiece(i,k) != NULL && theBoard.getPiece(i,k)->isMoving())
				theBoard.getPiece(i,k)->getMovingAnimation()->update(t);
		}

		theBoard.updateAnimation(t);

		if(initialTime == 0) initialTime = t;
		timePassed = (t - initialTime)/1000.0;

		cronometro->update(timePassed);

		if(timePassed >= cronometro->getTimeLimit()) {
			toMove = false;
			hasMoved = false;
			changeCurrentPlayer();
		}


		if(replaying) {	
			if(initialReplayTime == 0) initialReplayTime = t;
			currentReplayTime = (t - initialReplayTime)/1000.0;

			if(currentReplayTime >= replayTime) {
				theBoard = moves[replayingIndex];
				theBoard.setScore(sck.sumOf('b',&theBoard),sck.sumOf('w',&theBoard));
				replayingIndex++;
				if(replayingIndex == moves.size()) {
					replaying = false;
					replayingIndex = 0;
				}
				initialReplayTime = 0;
			}
		}
}

void ProjScene::changeTextures() {
	theBoard.setTexture(ambients[ambientState][1], ambients[ambientState][0]);
}

void ProjScene::display() {

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	

	// Apply transformations corresponding to the camera position relative to the origin
	CGFapplication::activeApp->forceRefresh();

	if(cameraState == 0) 
		CGFscene::activeCamera->applyView();
	else this->cameras[cameraState-1]->applyView();

	// Draw (and update) light
	light0->draw();

	for(unsigned int i = 0; i < lights.size(); i++) {
		this->lights[i]->display();
	}

	translateCamera();
	rotateCamera();

	// Draw axis
	axis.draw();

	glPushMatrix();
	glTranslated(-2,1.5,theBoard.getSize());
	glRotated(90,0,1,0);
	cronometro->draw();
	glPopMatrix();


	// ---- END Background, camera and axis setup


	// ---- BEGIN feature demos	
	//so it changes the box
	theBoard.setPlayer(currentPlayer);
	theBoard.draw();

	updateDrawing();
	updateLightState();	

	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

void ProjScene::setLightState() {
	lightState.push_back(1); //light0

	for(unsigned int i=0; i< lights.size();i++) {
		if(lights[i]->getEnabled())
			lightState.push_back(1);
		else lightState.push_back(0);
	}
}

void ProjScene::addPieceValue() {
	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(addNewPieceValue,currentPlayer),oldX,oldY));

	if(removes == 0 && (moves.empty() || theBoard != moves[moves.size()-1])) {			
		hasMoved = false;
		toMove = false;

		theBoard.getPiece(oldX,oldY)->setNew(oldY,oldX,theBoard.getSize());
		theBoard.setScore(sck.sumOf('b',&theBoard),sck.sumOf('w',&theBoard));

		changeCurrentPlayer();

		lastMove = theBoard;
		moves.push_back(theBoard);

		if(sck.isFull(&theBoard)) {
			showWinner();
			return;
		}
		else if(opponent == 1) {
			theBoard.boardParser(sck.pcMove(&theBoard,currentPlayer,level));
			if(theBoard != moves[moves.size()-1])
				moves.push_back(theBoard);

			theBoard.boardParser(sck.pcAdd(&theBoard,currentPlayer));
			moves.push_back(theBoard);

			if(sck.isFull(&theBoard)) {
				showWinner();
				return;
			}

			changeCurrentPlayer();
		}

		string out = "Move or add a piece.";
		TPinterface::setOutput(out);
	}
	else {
		string out = "Can't add that piece.";
		TPinterface::setOutput(out);
	}
}

bool ProjScene::changePiece() {
	if(removes)
		if(oldX != movedX || oldY!= movedY) {
			if(theBoard.getPiece(oldX,oldY) != NULL && theBoard.getPiece(oldX,oldY)->getColor() == currentPlayer)
				theBoard.boardParser(sck.addGray(&theBoard,oldX,oldY));

			if(theBoard != moves[moves.size()-1]) {
				theBoard.setScore(sck.sumOf('b',&theBoard),sck.sumOf('w',&theBoard));
				moves.push_back(theBoard);
				return true;
			}
		}

		return false;
}

void ProjScene::updateLightState() {
	if(lightState[0])
		light0->enable();
	else light0->disable();

	for(unsigned int i=1; i<lightState.size();i++) {
		if(lightState[i])
			lights[i-1]->enable();
		else lights[i-1]->disable();
	}
}

ProjScene::~ProjScene() {
	delete(light0);

	for(unsigned int i=0; i<lights.size();i++)
		delete(lights[i]);

	for(unsigned int i=0; i<cameras.size();i++)
		delete(cameras[i]);
}

void ProjScene::undo(int x) {
	if(x) {
		if(moves.size() > 1) 
			moves.pop_back();

		theBoard = moves[moves.size()-1];
	}
	else {
		hasMoved = false;
		toMove = false;
		theBoard = lastMove;
	}
}

void ProjScene::newGame() {
	theBoard = Board(this->newBoardSize);
	theBoard.boardParser(sck.initBoard(this->newBoardSize)); //Socket
	theBoard.setScore(sck.sumOf('b',&theBoard),sck.sumOf('w',&theBoard));

	if(!moves.empty())
		moves.clear();

	currentPlayer = 'b';

	hasMoved = false;
	toMove = false;

	moves.push_back(theBoard);

	if(opponent == 2) pcVSpc();
	else {
		string out = "Move or add a piece.";
		TPinterface::setOutput(out);
	}
}

void ProjScene::pcVSpc() {
	while(!sck.isFull(&theBoard)) {
		theBoard.boardParser(sck.pcMove(&theBoard,currentPlayer,level));
		theBoard.setScore(sck.sumOf('b',&theBoard),sck.sumOf('w',&theBoard));

		if(theBoard != moves[moves.size()-1])
			moves.push_back(theBoard);

		theBoard.boardParser(sck.pcAdd(&theBoard,currentPlayer));
		theBoard.setScore(sck.sumOf('b',&theBoard),sck.sumOf('w',&theBoard));
		moves.push_back(theBoard);

		changeCurrentPlayer();
	}

	showWinner();
}

void ProjScene::showWinner() {
	string p = sck.getWinner(&theBoard);
	TPinterface::setOutput("Winner is: " + p);
}

void ProjScene::changeCurrentPlayer() {
	if(currentPlayer == 'b') currentPlayer = 'w';
	else currentPlayer = 'b';

	mainCamera->toggleSide();
	initialTime = 0;
	timePassed = 0;

	removes = 0;
}

void ProjScene::replay() {
	replaying = true;
}

void ProjScene::rotateCamera() {
	glMultMatrixf(this->cameraRotation);
}

void ProjScene::translateCamera() {
	glTranslatef(cameraTranslationXY[0],cameraTranslationXY[1],-cameraTranslationZ);
}

void ProjScene::resetCameras() {
	memset(cameraRotation,0,sizeof(float)*16);
	cameraRotation[0] = 1.0;
	cameraRotation[5] = 1.0;
	cameraRotation[10] = 1.0;
	cameraRotation[15] = 1.0;
	cameraTranslationXY[0] = 0.0;
	cameraTranslationXY[1] = 0.0;
	cameraTranslationZ = 0.0;
}

void ProjScene::changePlayLimit() {
	this->cronometro->setTimeLimit((float) this->playTime);
}