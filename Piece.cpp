#include "Piece.h"

GLfloat ambB1[4] = {0,0,0,1};
GLfloat ambW1[4] = {0.6,0.6,0.6,1};
GLfloat ambG1[4] = {0.2,0.2,0.2,1};

GLfloat specB1[4] = {0.2,0.2,0.2,1};
GLfloat specW1[4] = {1,1,1,1};
GLfloat specG1[4] = {0.3,0.3,0.3,1};

GLfloat black1[4] = {0.1,0.1,0.1,1};
GLfloat white1[4] = {0.9,0.9,0.9,1};
GLfloat grey1[4] = {0.2,0.2,0.2,1};

GLdouble camera_pos[3];

static GLdouble* getRealWorldPosition() {
	int viewport[4]; 
	GLdouble modelView[16], matProjection[16];

	// get matrixs and viewport:
	glGetDoublev( GL_MODELVIEW_MATRIX, modelView ); 
	glGetDoublev( GL_PROJECTION_MATRIX, matProjection ); 
	glGetIntegerv( GL_VIEWPORT, viewport ); 
	gluUnProject( (viewport[2]-viewport[0])/2 , (viewport[3]-viewport[1])/2, 
		0.0, modelView, matProjection, viewport,  
		&camera_pos[0],&camera_pos[1],&camera_pos[2]);

	return camera_pos;
}

static float getAngleForPiece() {
	GLdouble* camera_pos = getRealWorldPosition();
	float posx = camera_pos[0];
	float posy = camera_pos[1];
	float posz = camera_pos[2];

	vector3d cameraPos = vector3d(posx,posy,0.0);
	vector3d zerovec = vector3d(0.0,1.0,0.0);
	float angle = cameraPos.angleVectors(zerovec);
	vector3d temp = vector3d(0,0,-1)*cameraPos;
	if(temp.getY() < 0) angle = 360-angle;

	return angle;
}


Piece::Piece(int number, char color) {
	this->color = color; 
	this->number = number;

	if(color == 'g')
		this->piece = new Cylinder(0.7,0.7,0.2,30,30);
	else this->piece = new Cylinder(0.7,0.7,0.2,(int) number/10 + 3,30);

	this->numberPlate =  new Cylinder(0.3,0.3,0.01,30,30);

	this->newPiece = false;
	this->isMoving1 = false;
	this->addingPiece = new Linear("adding piece",2);
	this->movingPiece = new Linear("moving piece",2);

	loadTextures();

	setAppearance();
}

void Piece::loadTextures() {
	for(int i = 0; i < 9; i++) {
		string name = "tex" + std::to_string(i) + ".jpg" ;
		numbers[i] = new CGFappearance(ambW1,white1,specW1,120);
		numbers[i]->setTexture(name);
	}

	infinityApp = new CGFappearance(ambW1,white1,specW1,120);
	infinityApp->setTexture("infinity.jpg");

	nonumberApp = new CGFappearance(ambW1,white1,specW1,120);
	nonumberApp->setTexture("nonumber.jpg");
}

char Piece::getColor() const {
	return color;
}

int Piece::getNumber() const {
	return number;
}

void Piece::setAppearance(CGFappearance* a) {
	this->pieceApp = a;
}

void Piece::setAppearance() {
	if(color == 'w') setAppearance(new CGFappearance(ambW1,white1,specW1,120));
	else if(color == 'b') setAppearance(new CGFappearance(ambB1,black1,specB1,120));
	else if(color == 'g') setAppearance(new CGFappearance(ambG1,grey1,specG1,120));
}

void Piece::setTexture(CGFtexture* t) {
	this->text = t;
	setAppearance();
	this->pieceApp->setTexture(text);
}

void Piece::setNumber(int n) {
	this->number = n;
}

void Piece::draw(float text_s, float text_t) {
	int n1 = number%10;

	glPushMatrix();

	if(color == 'g') infinityApp->apply();
	else if(n1 > -1 && n1 < 10) numbers[n1]->apply();
	else nonumberApp->apply();

	angle = getAngleForPiece();

	glTranslated(0,0,-0.001);
	glRotatef(180 + 90 + angle,0,0,1);
	numberPlate->draw(1,1);
	glPopMatrix();

	glPushMatrix();

	this->pieceApp->apply();
	this->piece->draw(text_s,text_t);

	glPopMatrix();
}

void Piece::setNew(int x, int y, int size) {
	newPiece = true;
	addingPiece->addControlPoint(-3,2.25,size+1);
	addingPiece->addControlPoint(-3,3,size+1);
	addingPiece->addControlPoint(2*x,3,2*y);
	addingPiece->addControlPoint(2*x,0,2*y);
}

void Piece::setMoving(int oldx, int oldy, int newx, int newy, int size) {
	//cout << "Old x:" << oldx << "Old y:" << oldy <<endl ;
	//cout << "new x:" << newx << "new y:" << newy << endl;

	isMoving1 = true;
	this->movingPiece->reset();
	movingPiece->addControlPoint(2*oldy, 0, 2*oldx);
	movingPiece->addControlPoint(2*newy, 0, 2*newx);
}
