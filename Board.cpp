#include "Board.h"

GLfloat ambB[4] = {0.2,0.2,0.2,1};
GLfloat ambW[4] = {0.5,0.5,0.5,1};
GLfloat ambG[4] = {0.1,0.1,0.1,1};

GLfloat specB[4] = {0.5,0.5,0.5,1};
GLfloat specW[4] = {1,1,1,1};
GLfloat specG[4] = {0.8,0.8,0.8,1};

GLfloat black[4] = {0,0,0,1};
GLfloat white[4] = {1,1,1,0};
GLfloat grey[4] = {0.8,0.8,0.8,1};

Board::Board() {
	this->size = 5;
	setPiecesAppearances();
	setBoxAnimation();
	scoreB = scoreW = 0;
	this->score = new Cube();

	boardApp = new CGFappearance();
}

Board::Board(int s) {
	this->size = s;
	setPiecesAppearances();
	setBoxAnimation();
	boardApp = new CGFappearance();
	scoreB = scoreW = 0;
	this->score = new Cube();
}

Board::Board(vector<vector<Piece*>> boardIn) {
	board = boardIn;
	size = boardIn.size();

	setPiecesAppearances();
	setBoxAnimation();
	boardApp = new CGFappearance();
	scoreB = scoreW = 0;
	this->score = new Cube();
}

void Board::setBoxAnimation() {
	isSliding = false;
	slidingBoxBtoW = new Linear("sliding box b to w",2);

	slidingBoxBtoW->addControlPoint(0,0,0);
	slidingBoxBtoW->addControlPoint(1,0,0);

	slidingBoxWtoB = new Linear("sliding box w to b",2);

	slidingBoxWtoB->addControlPoint(0,0,0);
	slidingBoxWtoB->addControlPoint(-1,0,0);
}

void Board::setPiecesAppearances() {
	blackPiece = new Piece(-1,'b');
	whitePiece = new Piece(-1,'w');

	whiteApp = new CGFappearance(ambW,white,specW,120);
	blackApp =  new CGFappearance(ambB,black,specB,120);

	this->whiteApp->setTexture(pieceText);
	this->blackApp->setTexture(pieceText);
}

void Board::setAppearance(CGFappearance* a) {
	this->boardApp = a;
}

void Board::setTexture(char c) {
	switch (c) {
	case 'w':
		boardApp = whiteApp;
		break;
	case 'b':
		boardApp = blackApp;
		break;
	default:
		break;
	}
	boardApp->setTexture(boardText);
}

void Board::setTexture(CGFtexture* bt, CGFtexture* pt) {
	this->boardText = bt;
	this->pieceText = pt;
}

void Board::setPlayer(char c) {
	if(c != currentPlayer) {
		isSliding = true; 
		currentPlayer = c; }
}

int Board::getPieceNumber(int row, int col) { 
	if(board[row][col] != NULL)
		return board[row][col]->getNumber();
	else return -1;
}

char Board::getPieceColor(int row, int col) {
	if(board[row][col] != NULL )
		return board[row][col]->getColor();
	else return 'a';
}

void Board::drawBoxPiece() { 
	glPushMatrix();

	glPushMatrix();
	glTranslatef(-3,2.25,size+1);
	glRotatef(90,1,0,0);
	whitePiece->setTexture(pieceText);
	whitePiece->draw(1,1);
	glPopMatrix();

	glTranslatef(-3,2.25,size-1);
	glRotatef(90,1,0,0);

	blackPiece->setTexture(pieceText);
	blackPiece->draw(1,1);

	glPopMatrix();
}

void Board::draw() { 
	glPushMatrix();

	glPushMatrix();
	drawBase();
	drawSolidBase();
	glTranslatef(-2,0.25,size);
	glRotatef(90,0,1,0);
	drawBox();
	glPopMatrix();

	drawBoxPiece();

	glPopMatrix();

	glPushMatrix();
	glScaled(1,2,1.5);
	glTranslated(size*2 + 2,1,size/2);
	drawScore();
	glPopMatrix();

	glPushMatrix();
	for(int row = 0; row < size; row++)
		for(int col = 0; col < size; col++) {
			if(board[row][col] != NULL) {
				glPushMatrix();
				board[row][col]->setTexture(this->pieceText);

				if(board[row][col]->isNew()) {
					if(board[row][col]->getAddingAnimation()->isStopped())
						board[row][col]->setOld();
					else board[row][col]->getAddingAnimation()->draw();
				}
				else if(board[row][col]->isMoving()) {
					if(board[row][col]->getMovingAnimation()->isStopped())
						board[row][col]->setMoving(false);
					else board[row][col]->getMovingAnimation()->draw();
				}
				else { 
					glTranslatef(2*col,0,0);
					glTranslatef(0,0,2*row);
				}

				glTranslatef(1,0.7,1);
				glRotatef(90,1,0,0);

				board[row][col]->draw(1,1);
				glPopMatrix();
			}
		}
		glPopMatrix();
}

void Board::drawSolidBase() {
	Primitive* cube = new Cube();

	glPushMatrix();
	glScaled(size*2,0.5,size*2);
	glTranslatef(0.5,0.45,0.5);

	cube->draw();
	glPopMatrix();
}

void Board::drawBase() {
	char lastCol;

	glPushName(-1);

	Primitive* temp = new Rectangle(0,0,2,2);

	for(int row = 0; row < size; row++) {
		glPushMatrix();
		glLoadName(row);
		for(int col = 0; col < size; col++) {
			glPushMatrix();

			glPushName(col);
			glTranslatef(2*col,0,0);
			glTranslatef(0,0,2*row);

			glTranslatef(0,0.5,2);
			glRotatef(-90,1,0,0);

			if(row%2 == 0) {
				if(col == 0) {
					lastCol = 'b';
				}
				if(lastCol == 'b') {
					this->setTexture('w');
					this->boardApp->apply();
					lastCol = 'w';
				}
				else { 
					this->setTexture('b');
					this->boardApp->apply();
					lastCol = 'b';
				}
			}
			else {
				if(col == 0) {
					lastCol = 'w';
				}

				if(lastCol == 'b') {
					this->setTexture('w');
					this->boardApp->apply();
					lastCol = 'w';
				}
				else { 
					this->setTexture('b');
					this->boardApp->apply();
					lastCol = 'b';
				}
			}

			temp->draw(1,1);

			glPopName();
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopName();
}

void Board::drawBox() {
	Primitive* cube = new Cube();
	glPushMatrix();
	glTranslated(0,0,-1);

	//base
	glPushMatrix();
	glScaled(4,0.5,2);
	cube->draw();
	glPopMatrix();

	//top
	glPushMatrix();

	if(currentPlayer == 'b') {
		if(isSliding) {
			if(slidingBoxWtoB->isStopped()) {
				isSliding = false;
			}
			else {
				slidingBoxWtoB->draw();
			}
		}
		else  glTranslated(-1,0,0);


	}else {
		if(isSliding) {
			if(slidingBoxBtoW->isStopped()) {
				isSliding = false;
			}
			else {
				slidingBoxBtoW->draw();
			}
		}

		else glTranslated(1,0,0);

	}

	glTranslated(0,2,0);
	glScaled(1.6,0.1,1.6);
	//glScaled(10,10,10);

	cube->draw();
	glPopMatrix();

	//sides
	glPushMatrix();
	glTranslated(0,1.25,0);

	//right side
	glPushMatrix();
	glTranslated(0,0,0.9);
	glScaled(4,2,0.2);
	cube->draw();
	glPopMatrix();

	//left side
	glPushMatrix();
	glTranslated(0,0,-0.9);
	glScaled(4,2,0.2);
	cube->draw();
	glPopMatrix();

	glPushMatrix();

	glRotated(90,0,1,0);
	glScaled(1.6,2,0.2);

	//division
	cube->draw();

	//up side
	glPushMatrix();
	glTranslated(0,0,-9.5);
	cube->draw();
	glPopMatrix(); 

	//down side
	glPushMatrix();
	glTranslated(0,0,9.5);
	cube->draw();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}

void Board::boardParser(string answer) {
	//this->board.clear();
	vector<vector<int>> tempBoardN;
	vector<vector<char>> tempBoardC;
	vector<int> rowN;
	vector<char> rowC;

	answer.erase(0,1); // erase first '['
	answer.erase(answer.size()-3,answer.size()-3); // erase last '].\r'

	int posEnd;

	while(answer != "") {
		if(answer[0] == ',')
			answer.erase(0,1);
		if(answer.find("[[") == 0)
			answer.erase(0,1); // erase row '['

		posEnd = answer.find("]");
		if(posEnd != 0) {
			if(posEnd != 1) {
				string cell = answer.substr(1,posEnd-1);

				char color = cell[0];
				int number = (int) atoi(cell.substr(cell.find(",") + 1, cell.size()-2).c_str());

				rowN.push_back(number);
				rowC.push_back(color);
			}
			else {
				rowC.push_back(NULL); //empty cell
				rowN.push_back(NULL); //empty cell
			}
		}
		else { //end of row
			tempBoardN.push_back(rowN);
			tempBoardC.push_back(rowC);
			rowC.clear();
			rowN.clear();
		}
		answer.erase(0,posEnd+1);
	}

	checkBoard(tempBoardN, tempBoardC);
}

void Board::checkBoard(vector<vector<int>> bn, vector<vector<char>> bc) {
	if(bn.size() != this->board.size()) {
		board.clear();

		for(unsigned int i=0; i < bn.size(); i++) {
			vector<Piece*> row;
			for(unsigned int j=0; j < bn[i].size(); j++) {
				if(bc[i][j] == NULL) row.push_back(NULL);
				else row.push_back(new Piece(bn[i][j],bc[i][j]));
			}
			board.push_back(row);
		}
		size = board.size();
	}
	else  {
		for(unsigned int i=0; i < bn.size(); i++)
			for(unsigned int j=0; j < bn[i].size(); j++)
				if(board[i][j] == NULL || board[i][j]->getColor() != bc[i][j] || board[i][j]->getNumber() != bn[i][j]) {
					if(bc[i][j] == NULL) board[i][j] = NULL;
					else board[i][j] = new Piece(bn[i][j], bc[i][j]);
				}
	}
}

string Board::toString() {
	string b = "[";

	for(unsigned int i = 0; i < this->board.size(); i++) {
		b.append("[");
		for(unsigned int j = 0; j < this->board[i].size(); j++) {
			if(board[i][j] == NULL)
				b.append("[]");
			else {
				b.append("[");
				b+=board[i][j]->getColor();
				b.append(",");
				b.append(to_string(board[i][j]->getNumber()));
				b.append("]");
			}

			if(j < board[i].size()-1)
				b.append(",");
		}
		b.append("]");

		if(i < board.size()-1)
			b.append(",");
	}
	b.append("]");

	return b;
}

bool Board::operator== (const Board& b) {
	if(board.size() != b.board.size()) {
		printf("board size\n");
		return false;
	}

	for(unsigned int i=0; i < board.size(); i++) {
		if(board[i].size() != b.board[i].size())
			return false;

		for(unsigned int j=0; j < board.size(); j++) {
			if(board[i][j] == NULL && b.board[i][j] == NULL)
				continue;

			if(board[i][j] != NULL && b.board[i][j] == NULL)
				return false;

			if(board[i][j] == NULL && b.board[i][j] != NULL)
				return false;

			if(*(board[i][j]) != *(b.board[i][j]))
				return false;
		}
	}

	return true;
}

void Board::drawScore() {
	int centenasB,dezenasB,unidadesB;
	int centenasW,dezenasW,unidadesW;

	centenasB = scoreB / 100;
	dezenasB = (scoreB % 100) / 10;
	unidadesB = (scoreB % 10);
	centenasW = scoreW / 100;
	dezenasW = (scoreW % 100) / 10;
	unidadesW = (scoreW % 10);

	glPushMatrix();
	glScaled(0.1,1.0,1.0);

	double zT = 0;
	if(centenasB) {
		glPushMatrix();
		glTranslated(0,0,zT++);
		Piece::getNumberText(centenasB)->apply();
		score->draw(1,1);
		glPopMatrix();
	}
	if(dezenasB) {
		glPushMatrix();
		glTranslated(0,0,zT++);
		Piece::getNumberText(dezenasB)->apply();
		score->draw(1,1);
		glPopMatrix();
	}

	//unidades b
	glPushMatrix();
	glTranslated(0,0,zT++);
	Piece::getNumberText(unidadesB)->apply();
	score->draw(1,1);
	glPopMatrix();

	glPushMatrix();
	setTexture('b');
	this->boardApp->apply();
	glScaled(1,1.1,(zT+0.1));
	glTranslated(0.1,0,0.5*((zT-1)/(zT+0.1)));
	score->draw(1,1);
	glPopMatrix();

	glTranslated(0,0,zT+0.5);

	zT = 0;

	if(centenasW) {
		glPushMatrix();
		glTranslated(0,0,zT++);
		Piece::getNumberText(centenasW)->apply();
		score->draw(1,1);
		glPopMatrix();
	}
	if(dezenasW) {
		glPushMatrix();
		glTranslated(0,0,zT++);
		Piece::getNumberText(dezenasW)->apply();
		score->draw(1,1);
		glPopMatrix();
	}
	//unidades w
	glPushMatrix();
	glTranslated(0,0,zT++);
	Piece::getNumberText(unidadesW)->apply();
	score->draw(1,1);
	glPopMatrix();

	glPushMatrix();
	setTexture('w');
	this->boardApp->apply();
	glScaled(1,1.1,(zT+0.1));
	glTranslated(0.1,0,0.5*((zT-1)/(zT+0.1)));
	score->draw(1,1);
	glPopMatrix();

	glPopMatrix();
}

void Board::setScore(int b, int w) {
	this->scoreB = b;
	this->scoreW = w;
}

