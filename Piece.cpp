#include "Piece.h"




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
	if(color == 'b') setAppearance(new CGFappearance("black.jpg",1,1));
	else if(color == 'w') setAppearance(new CGFappearance("white.jpg",1,1));
	else if(color == 'g') setAppearance(new CGFappearance("grey.jpg",1,1));


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