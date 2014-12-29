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
}

void Piece::setNumber(int n) {
	this->number = n;
}

void Piece::draw(float text_s, float text_t) {
	glPushMatrix();
	this->pieceApp->apply();
	this->piece->draw(text_s,text_t);
	glPopMatrix();
}