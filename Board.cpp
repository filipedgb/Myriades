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
	setAppearance();
}

Board::Board(int s) {
	this->size = s;
	setAppearance();

	whiteApp = new CGFappearance(ambW,white,specW,120);
	blackApp =  new CGFappearance(ambB,black,specB,120);

	woodTex = new CGFtexture("woodBoard.jpg");

}

Board::Board(vector<vector<Piece*>> boardIn) {
	board = boardIn;
	size = boardIn.size();
	setAppearance();
}

void Board::setAppearance(CGFappearance* a) {
	this->boardApp = a;
}

void Board::setTexture(char c) {
switch (c) {
	case 'w':
		boardApp = whiteApp;
		boardApp->setTexture(woodTex) ;
		break;
	case 'b':
		boardApp = blackApp;
		boardApp->setTexture(woodTex) ;
		break;
	default:
		break;
	}
}

void Board::setAppearance() {
	setAppearance(new CGFappearance("woodBoard.jpg",1,1));
}

int Board::getPieceNumber(int row, int col) { 
	if(board[row][col] != NULL) { 
	return board[row][col]->getNumber();
	} 
	else { 
		return -1;
	}
}

char Board::getPieceColor(int row, int col) {
	if(board[row][col] != NULL ) { 
		return board[row][col]->getColor();
	} 
	else { 
		return 'a';
	}

}


void Board::draw() { 
	glPushMatrix();

	drawBase();
	setAppearance();

	drawSolidBase();
	
	
	glTranslatef(0,0,-2);
	drawBox();
	glPopMatrix();

	for(int row = 0; row < size; row++) {
		for(int col = 0; col < size; col++) {
			//printf("size: %d row: %d, col: %d\n",row,col,size);

			glPushMatrix();
			glTranslatef(2*col,0,0);
			glTranslatef(0,0,2*row);

			glTranslatef(1,0.7,1);
			glRotatef(90,1,0,0);

			if(board[row][col] != NULL) {
				glPushMatrix();
				board[row][col]->draw(1,1);

				glRasterPos3f(row-0.5, col-0.5, -2);

				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0'+getPieceNumber(row,col));

				glPopMatrix();
			}
			glPopMatrix();
		}
	}
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
	char lastRow ;
	char lastCol;

	glPushName(-1);

	for(int row = 0; row < size; row++) {
		glPushMatrix();
		glLoadName(row);
		for(int col = 0; col < size; col++) {
			//printf("size: %d row: %d, col: %d\n",row,col,size);

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
			
			Primitive* temp = new Rectangle(0,0,2,2);
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
	glPushMatrix();
	cube->draw();
	glPopMatrix();

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
	this->board.clear();
	vector<Piece*> row;

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

				row.push_back(new Piece(number, color));
			}
			else row.push_back(NULL); //empty cell
		}
		else { //end of row
			board.push_back(row);
			row.clear();
		}
		answer.erase(0,posEnd+1);
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