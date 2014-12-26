#include "Piece.h"

Piece::Piece(int number, char* color) {
	this->color = color; 
	this->number = number;
	this->piece = new Cylinder(1,1,0.2,30,30);
}

char* Piece::getColor() const {
	return color;
}

int Piece::getNumber() const {
	return number;
}

void Piece::setColor(char* c) {
	this->color = c;
}

void Piece::setNumber(int n) {
	this->number = n;
}

void Piece::draw(float text_s, float text_t) {
	glPushMatrix();
	this->piece->draw(text_s,text_t);
	glPopMatrix();
}