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

Piece::Piece(int number, char color) {
	this->color = color; 
	this->number = number;
	this->piece = new Cylinder(0.7,0.7,0.2,30,30);
	this->newPiece = false;
	this->isMoving1 = false;
	this->addingPiece = new Linear("adding piece",2);
	this->movingPiece = new Linear("moving piece",5);

	//shader= new Shader(number);

	setAppearance();
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
	//this->shader->setTexture(t);
}

void Piece::setNumber(int n) {
	this->number = n;
}

void Piece::draw(float text_s, float text_t) {
	glPushMatrix();
	//this->shader->bind();
	if(color != 'g') {
		glPushMatrix();
		if(color == 'b') (new CGFappearance(ambW1,specW1,white1,120))->apply();
		else (new CGFappearance(ambB1,specB1,black1,120))->apply();

		int n1 = number/10;
		int n2 = number%10;

		if(n1 != 0) {
			glRasterPos3f(-0.1, 0.01, 0);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0'+n1);

			glRasterPos3f(0.1, 0.01, 0);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0'+n2);
		}
		else {
			glRasterPos3f(0, 0.01, 0);
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0'+n2);
		}


		glPopMatrix();
	}

	this->pieceApp->apply();
	this->piece->draw(text_s,text_t);
	//this->shader->unbind();
	glPopMatrix();
}

void Piece::setNew(int x, int y, int size) {
	newPiece = true;
	addingPiece->addControlPoint(-3,2.25,size+1);
	addingPiece->addControlPoint(-3,3,size+1);
	addingPiece->addControlPoint(2*x,3,2*y+2);
	addingPiece->addControlPoint(2*x,0,2*y+2);
}

void Piece::setMoving(int oldx, int oldy, int newx, int newy, int size) {
	isMoving1 = true;
	this->movingPiece->reset();
	movingPiece->addControlPoint(2*oldy, 0, 2*oldx);
	movingPiece->addControlPoint(2*newy, 0, 2*newx);
}