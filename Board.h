#ifndef BOARD_H
#define BOARD_H


#include <vector>
#include "Piece.h"
#include "Primitive.h"
#include "Rectangle.h"
#include <GL/glut.h>


class Board {	
	vector<vector<Piece*>> board;
	int size;

public:
	Board() {
				size = 5;

	}
	Board(vector<vector<Piece*>> boardIn) {
		board = boardIn;
		size = 5;
	}
	void boardParser(string answer);
	void draw();
	void drawBase() ;
};




#endif