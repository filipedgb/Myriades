#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Piece.h"
#include "Cube.h"
#include <GL/glut.h>
#include "CGFappearance.h"

class Board {	
	vector<vector<Piece*>> board;
	int size;

	CGFappearance* boardApp;

public:
	Board();
	Board(int s);
	Board(vector<vector<Piece*>> boardIn);

	void boardParser(string answer);
	void draw();
	void drawBase();
	void drawBox();
	void setAppearance();
	void setAppearance(CGFappearance* a);

	int getPieceNumber(int row, int col);

	string toString();
};

#endif
