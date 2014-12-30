#ifndef SOCKET_H
#define SOCKET_H

#include <iostream>
#include "Board.h"

#define IPADDRESS "127.0.0.1"
#define PORT 60070

using namespace std;

class CtoPlSocket {
public: 
	bool socketConnect();
	void envia(string s);
	void recebe(char* ans);
	void quit();

	string initBoard(int size);
	string addPiece(Board* board, Piece* p, int posX, int posY);
	string movePiece(Board* board, int posX, int posY, int newPx, int newPy);
	string addGray(Board* board, int newPx, int newPy);
	int numberOfAdjacentes(int x, int y, Board* board);
	int numPieces(char player, Board* board);
	bool isFull(Board* b);
	string getWinner(Board* b);

	string pcAdd(Board *b, char player);
	string pcMove(Board *b, char player, int lvl);
};

#endif