#include "ProjScene.h"
#include "TPinterface.h"

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
	GLfloat p1Pos[3] = {0,2,1};
	GLfloat p1Tar[3] = {0,1.5,0};
	GLfloat p2Pos[3] = {2,2,2};
	GLfloat p2Tar[3] = {0,2,0};
	GLfloat p3Pos[3] = {2,5,2};
	GLfloat p3Tar[3] = {0,0,0};
	/* CAMARAS */
	Perspective* p1 = new Perspective("p1",0,0,0,p1Pos,p1Tar);
	Perspective* p2 = new Perspective("p2",0,0,0,p2Pos,p2Tar);
	Perspective* p3 = new Perspective("p3",0,0,0,p3Pos,p3Tar);

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

void ProjScene::setSelectedCoords(int x, int y) { 
	if(!hasMoved && toMove) { //ja escolheu peca para mover
		newX = x;
		newY = y;

		theBoard.boardParser(sck.movePiece(&theBoard,oldX,oldY,newX,newY));

		if(moves.empty() || theBoard != moves[moves.size()-1]) {
			toMove = false;
			hasMoved = true;
			moves.push_back(theBoard);
			movedX = newX;			//guardar para nao poder retirar a peca que acabou de mover
			movedY = newY;

			theBoard.getPiece(movedX,movedY)->setMoving(oldX,oldY,movedX,movedY, theBoard.getSize());

			string out = "Player " + currentPlayer;
			out.append(": moved a piece.\n");
			TPinterface::setOutput(out);

			int adj = sck.numberOfAdjacentes(movedX,movedY,&theBoard);

			while(adj) {
				out = "You have ";
				out.append(to_string(adj));
				out.append(" adjacent pieces.\n");

				if(sck.numPieces(currentPlayer,&theBoard) < 2)	//cant change piece that moved
					break;

				//if(changePiece())
					adj--;

				TPinterface::setOutput(out);
			}

			out = "Now add a piece.\n";

			TPinterface::setOutput(out);
		}
		else {
			string out = "Player " + currentPlayer;
			out.append(": can't make that move.\n");

			TPinterface::setOutput(out);
		}
	}
	else {
		cout << "old x : " << oldX << " old y: " << oldY << endl;

		oldX = x;
		oldY = y;

		Piece * piece = theBoard.getPiece(x,y);
		if(piece != NULL) {
			string pout = "Selected ";
			if(piece->getColor() == 'b') pout.append("black ");
			else if(piece->getColor() == 'w') pout.append("white ");
			else if(piece->getColor() == 'g') pout.append("gray ");
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
	setAllAmbient();

	currentPlayer = 'b';
	toMove = false;
	hasMoved = false;

	theBoard = Board(3);
	sck.socketConnect();
	theBoard.boardParser(sck.initBoard(3)); //Socket

	moves.push_back(theBoard);

	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(0,'w'),0,0));
	moves.push_back(theBoard);
	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(1,'b'),0,1));
	moves.push_back(theBoard);
	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(2,'w'),1,0));
	moves.push_back(theBoard);
	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(0,'g'),2,1));
	moves.push_back(theBoard);
	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(10,'b'),1,1));
	moves.push_back(theBoard);

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
}

void ProjScene::changeTextures() {
	theBoard.setTexture(ambients[ambientState][1], ambients[ambientState][0]);
}

void ProjScene::display() {

	// ---- BEGIN Background, camera and axis setup

	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
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

	theBoard.setPlayer(currentPlayer);
	theBoard.draw();

	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup


	// ---- BEGIN feature demos
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
	cout << "Valor: " << addNewPieceValue << endl;

	theBoard.boardParser(sck.addPiece(&theBoard,new Piece(addNewPieceValue,currentPlayer),oldX,oldY));

	if(moves.empty() || theBoard != moves[moves.size()-1]) {			
		hasMoved = false;

		theBoard.getPiece(oldX,oldY)->setNew(oldY,oldX,theBoard.getSize());

		string out = "Added a piece.\n";
		TPinterface::setOutput(out);

		if(currentPlayer == 'b') currentPlayer = 'w';
		else currentPlayer = 'b';

		moves.push_back(theBoard);

		if(sck.isFull(&theBoard)) {
			showWinner(sck.getWinner(&theBoard));
			return;
		}

		out.append("Next player: Move or add a piece.\n");
		TPinterface::setOutput(out);
	}
	else {
		string out = "Can't add that piece.\n";
		TPinterface::setOutput(out);
	}
}

bool ProjScene::changePiece() {
	if(oldX != movedX || oldY!= movedY) {
		if(theBoard.getPiece(oldX,oldY) != NULL && theBoard.getPiece(oldX,oldY)->getColor() == currentPlayer)
			theBoard.boardParser(sck.addGray(&theBoard,oldX,oldY));

		if(theBoard != moves[moves.size()-1]) {
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

int ProjScene::searchCamera(char* id) {
	for(unsigned int i=0; i < cameras.size();i++)
		if(!strcmp(cameras[i]->getId(),id))
			return i;
	return -1;
}

int ProjScene::searchAnimation(char* id) {
	for(unsigned int i=0; i < animations.size();i++)
		if(!strcmp(animations[i]->getId(),id))
			return i;
	return -1;
}

ProjScene::~ProjScene() {
	delete(light0);

	for(unsigned int i=0; i<lights.size();i++)
		delete(lights[i]);

	for(unsigned int i=0; i<cameras.size();i++)
		delete(cameras[i]);
}

void ProjScene::undo() {
	if(moves.size() > 1) 
		moves.pop_back();

	theBoard = moves[moves.size()-1];
}

void ProjScene::newGame() {
	theBoard = Board(this->newBoardSize);
	theBoard.boardParser(sck.initBoard(this->newBoardSize)); //Socket

	if(moves.size())
		moves.clear();

	currentPlayer = 'b';
}

void ProjScene::showWinner(string p) {
	TPinterface::setOutput("Winner is: " + p);
}