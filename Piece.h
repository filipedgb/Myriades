#ifndef PIECE_H
#define PIECE_H


#include "Cylinder.h"
#include "Rectangle.h"
#include "CGFappearance.h"
#include "Linear.h"
#include "Cube.h"


class Piece: public Primitive {
	Cylinder* piece;
	Cylinder* numberPlate;

	char color; //(w)hite, (b)lack, (g)ray
	int number;

	CGFappearance* pieceApp;
	CGFappearance* numberApp;

	CGFtexture* text;	
	
	CGFappearance* numbers[9];
	
	Linear* addingPiece;
	Linear* movingPiece;

	bool newPiece;
	bool isMoving1;
	float angle;

public:
	Piece(int number, char color);
	char getColor() const;
	int getNumber() const;

	void loadTextures();
	void setColor(char c);
	void setNumber(int n);
	void draw(float text_s, float text_t);

	void setAngle(float a) {angle = a;}

	void setAppearance();
	void setAppearance(CGFappearance* a);
	void setTexture(CGFtexture* t);

	bool operator== (const Piece& p) {
		return (color == p.color && number == p.number);
	}

	bool operator!= (const Piece& p) {
		return !(*this == p);
	}

	Linear* getAddingAnimation() {return addingPiece;}
	Linear* getMovingAnimation() {return movingPiece;}

	bool isNew() {return newPiece;}
	bool isMoving() {return isMoving1;}

	void setOld() {newPiece = false;}

	void setNew(int x, int y, int size);
	void setMoving(int oldx, int oldy, int newx, int newy, int size);

	void setMoving(bool t) { isMoving1 = t;}
};

#endif