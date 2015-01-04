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
	CGFappearance* redApp;
	CGFappearance* blueApp;


	CGFtexture* boardText;
	CGFtexture* pieceText;

	Linear* slidingBoxWtoB;
	Linear* slidingBoxBtoW;

	bool isSliding;

	Cube *score;
	int scoreB, scoreW;

	int selectedX1, selectedY1, selectedX2,selectedY2;

	char currentPlayer;

public:
	Board();
	Board(int s);
	Board(vector<vector<Piece*>> boardIn);

	void selectedFirst(int x, int y) {
		selectedX1 = x;
		selectedY1 = y;
	}

	void selectedSecond(int x, int y) {
		selectedX2 = x;
		selectedY2 = y;
	}

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
	int getSize() const { return size;}

	string toString();	

	Board& operator= (const Board& b) {
		this->board = b.board;
		this->size = b.size;
		this->scoreB = b.scoreB;
		this->scoreW = b.scoreW;
		return *this;
	}

	Piece* getPiece(int row, int col) const {
		return board[row][col];
	}

	bool operator== (const Board& b);

	bool operator!= (const Board& b) {return !(*this == b);}
};

#endif
