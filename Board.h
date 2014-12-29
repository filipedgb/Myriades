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

	Piece* whitePiece;
	Piece* blackPiece;

	CGFappearance* boardApp;

	CGFappearance* whiteApp;
	CGFappearance* blackApp;

	CGFtexture* boardText;
	CGFtexture* pieceText;

public:
	Board();
	Board(int s);
	Board(vector<vector<Piece*>> boardIn);

	void boardParser(string answer);
	void draw();
	void drawSolidBase();
	void drawBase();
	void drawBox();
	void drawBoxPiece();
	void setPiecesAppearances();
	void setAppearance(CGFappearance* a);
	void setTexture(char c);
	void setTexture(CGFtexture* bt, CGFtexture* pt);

	int getPieceNumber(int row, int col);
	char getPieceColor(int row, int col);
	int getSize() { return size;}

	string toString();	

	Board& operator= (const Board& b) {
		this->board = b.board;
		this->size = b.size;
		return *this;
	}

	bool operator== (const Board& b);

	bool operator!= (const Board& b) {return !(*this == b);}
};

#endif
