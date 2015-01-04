#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Piece.h"
#include <GL/glut.h>

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

	Linear* slidingBoxWtoB;
	Linear* slidingBoxBtoW;

	bool isSliding;

	Cube *score;
	int scoreB, scoreW;

	char currentPlayer;

public:
	Board();
	Board(int s);
	Board(vector<vector<Piece*>> boardIn);

	void boardParser(string answer);
	void checkBoard(vector<vector<int>> bn, vector<vector<char>> bc);
	void draw();
	void drawSolidBase();
	void drawBase();
	void drawBox();
	void drawBoxPiece();
	void drawScore();
	void setPiecesAppearances();
	void setAppearance(CGFappearance* a);
	void setTexture(char c);
	void setTexture(CGFtexture* bt, CGFtexture* pt);

	void setBoxAnimation();
	void setScore(int b, int w);
	void setPlayer(char c);

	void updateAnimation(unsigned long t) {
		if(currentPlayer == 'w') slidingBoxBtoW->update(t);
		else slidingBoxWtoB->update(t);
	}

	int getPieceNumber(int row, int col);
	char getPieceColor(int row, int col);
	int getSize() { return size;}

	string toString();	

	Board& operator= (const Board& b) {
		this->board = b.board;
		this->size = b.size;
		this->scoreB = b.scoreB;
		this->scoreW = b.scoreW;
		return *this;
	}

	Piece* getPiece(int row, int col) {
		return board[row][col];
	}

	bool operator== (const Board& b);

	bool operator!= (const Board& b) {return !(*this == b);}
};

#endif
