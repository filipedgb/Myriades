#ifndef PIECE_H
#define PIECE_H

#include "Cylinder.h"
#include "CGFappearance.h"

class Piece: public Primitive {
	Cylinder* piece;
	char color; //(w)hite, (b)lack, (g)ray
	int number;

	CGFappearance* pieceApp;

public:
	Piece(int number, char color);
	char getColor() const;
	int getNumber() const;
	void setColor(char c);
	void setNumber(int n);
	void draw(float text_s, float text_t);

	void setAppearance();
	void setAppearance(CGFappearance* a);

	bool operator== (const Piece& p) {
		return (color == p.color && number == p.number);
	}

	bool operator!= (const Piece& p) {
		return !(*this == p);
	}
};

#endif