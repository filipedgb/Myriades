#include "ProjScene.h"

GLfloat ambientLight[4] = {0.8, 0.8, 0.8, 1};
GLfloat background[4] = {0, 0, 0, 0.8};

#define NUM_OBJS 7
#define NUM_ROWS 5
#define NUM_COLS 4


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

	/*Texturas*/
	Texture *woodBoard = new Texture("woodBoard","woodBoard.jpg",5,5);
	texturas.push_back(woodBoard);

}

void ProjScene::init() {
	setAllAmbient();

	theBoard = Board(3);
	sck.socketConnect();
	theBoard.boardParser(sck.initBoard(3)); //Socket
	theBoard.setTexture(texturas[searchTexture("woodBoard")]);

	//printBoard(boardParser("s"));
	//getchar();

	unsigned long updatePeriod=50;
	setUpdatePeriod(updatePeriod);

	theGraph = Grafo();

	printf("Size do vector animaçoes %d\n", animations.size());

	/* init values */
	mode = 0;
	shading = 1;
	cameraState = 0;
	setLightState();

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

	//obj = new Piece(1,'g');

	glEnable(GL_NORMALIZE);

	system("pause");
}

void ProjScene::update(unsigned long t) {
	for(int i = 0; i < animations.size(); i++) {
		animations[i]->update(t);
	}
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


	theBoard.draw();


	/*
	// Example 1: simple naming
	glPushMatrix();

	glPushName(-1);		// Load a default name

	int aIndex;

	for (int i=0; i< NUM_OBJS;i++)
	{
	glPushMatrix();
	glTranslatef(i*5,0,0);
	glLoadName(i);		//replaces the value on top of the name stack
	aIndex = searchAppearance((char*)obj->getColor());
	appearances[aIndex]->apply();
	obj->draw(1,1);
	glPopMatrix();
	}
	glPopMatrix();

	// example 2: structured naming
	for (int r=0; r < NUM_ROWS; r++)
	{
	glPushMatrix();
	glTranslatef(0, r*4, 0);
	glLoadName(r);
	for (int c=0; c < NUM_COLS; c++)
	{
	glPushMatrix();
	glTranslatef(0,0,(c+1)*5);
	glRotatef(90,0,1,0);
	glPushName(c);
	aIndex = searchAppearance((char*)obj->getColor());
	appearances[aIndex]->apply();
	obj->draw(1,1);
	glPopName();
	glPopMatrix();
	}
	glPopMatrix();
	}

	*/

	// Draw axis
	axis.draw();

	// ---- END Background, camera and axis setup


	// ---- BEGIN feature demos
	updateDrawing();
	updateLightState();	

	//applyMatrixDraw(theGraph.searchNode(theGraph.getRoot()), theGraph.searchNode(theGraph.getRoot())->getAppearance());


	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
}

void ProjScene::applyMatrixDraw(Node* node, Appearance *appID) {
	glPushMatrix();
	glMultMatrixf(node->getMatrix());

	if(node->getInherits()) {
		node->setAppearance(appID);
	}

	for(unsigned int k = 0; k < node->getPrimitives().size(); k++) {
		node->getAppearance()->apply();

		if(node->getAppearance()->getTextureRef() != NULL) {
			int textRef = searchTexture(node->getAppearance()->getTextureRef());
			float s = texturas[textRef]->getLengthS();
			float t = texturas[textRef]->getLengthT();
			node->getPrimitives()[k]->draw(s,t);
		}
		else node->getPrimitives()[k]->draw();
	}

	for(unsigned int i = 0; i < node->getDescendants().size(); i++) {
		Node* n = node->getDescendants()[i];

		if(n->getIndex() < n->getAnimation().size()) {
			n->getAnimation()[n->getIndex()]->draw();
			if(n->getAnimation()[n->getIndex()]->isStopped()) {
				n->incIndex();

				if(n->getIndex() < n->getAnimation().size()) {
					n->getAnimation()[n->getIndex()]->reset();
				}
			}
		}
		applyMatrixDraw(n, node->getAppearance());
		if(n->getAnimation().size()) glPopMatrix();
	}
	glPopMatrix();

}

void ProjScene::setLightState() {
	lightState.push_back(1); //light0

	for(unsigned int i=0; i< lights.size();i++) {
		if(lights[i]->getEnabled())
			lightState.push_back(1);
		else lightState.push_back(0);
	}
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

int ProjScene::searchTexture(char* id) {
	for(unsigned int i=0; i < texturas.size();i++)
		if(!strcmp(texturas[i]->getId(),id))
			return i;
	return -1;
}

int ProjScene::searchAppearance(char* id) {
	for(unsigned int i=0; i < appearances.size();i++)
		if(!strcmp(appearances[i]->getId(),id))
			return i;
	return -1;
}

ProjScene::~ProjScene() {
	delete(shader);
	delete(light0);

	for(unsigned int i=0; i<texturas.size();i++)
		delete(texturas[i]);

	for(unsigned int i=0; i<lights.size();i++)
		delete(lights[i]);

	for(unsigned int i=0; i<cameras.size();i++)
		delete(cameras[i]);
}
