#ifndef PIECE_H
#define PIECE_H

#include "Cylinder.h"
#include "Appearance.h"

class Piece: public Primitive {
	Cylinder* piece;
	char* color; //(w)hite, (b)lack, (g)ray
	int number;
	Appearance *app;

	public:
		Piece(int number, char* color);
		char* getColor() const;
		int getNumber() const;
		void setColor(char* c);
		void setNumber(int n);
		void draw(float text_s, float text_t);

};

#endif