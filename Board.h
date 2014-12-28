#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Piece.h"
#include "Rectangle.h"
#include <GL/glut.h>
#include "Appearance.h"
#include "Texture.h"

class Board {	
	vector<vector<Piece*>> board;
	int size;

	Appearance* boardApp;
	Texture* boardTex;
public:
	Board();
	Board(int s);
	Board(vector<vector<Piece*>> boardIn);

	void boardParser(string answer);
	void draw();
	void drawBase();
	void setAppearance(Appearance* a);
	void setAppearance();
	void setTexture(Texture* t);

	int getPieceNumber(int row, int col);

	string toString();
};

#endif
