#include "Board.h"

Board::Board() {
	this->size = 5;
	setAppearance();
}

Board::Board(int s) {
	this->size = s;
	setAppearance();
}

Board::Board(vector<vector<Piece*>> boardIn) {
	board = boardIn;
	size = boardIn.size();
	setAppearance();
}

void Board::setAppearance(Appearance* a) {
	this->boardApp = a;
}

void Board::setAppearance() {
	GLfloat diff[4] = {0.8,0.8,0.8,1};
	GLfloat spec[4] = {0.8,0.8,0.8,1};
	GLfloat amb[4] = {0.8,0.8,0.8,1};

	this->boardApp = new Appearance("boardApp",120,"woodBoard",amb,diff,spec);
}

void Board::setTexture(Texture* t) {
	this->boardTex = t;
}

void Board::draw() { 

	glPushMatrix();
	this->boardTex->apply();
	drawBase();
	glPopMatrix();

	for(int row = 0; row < size; row++) {
		glPushMatrix();
		for(int col = 0; col < size; col++) {
			//printf("size: %d row: %d, col: %d\n",row,col,size);

			glPushMatrix();
			glTranslatef(2.5*col,0,0);
			glTranslatef(0,0,2.5*row);

			glTranslatef(1,1,1);
			glRotatef(90,1,0,0);

			if(board[row][col] != NULL) {
				glPushMatrix();
				board[row][col]->draw(1,1);
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
}

void Board::drawBase() {
	glPushName(-1);

	for(int row = 0; row < size; row++) {
		glPushMatrix();
		glLoadName(row);
		for(int col = 0; col < size; col++) {
			//printf("size: %d row: %d, col: %d\n",row,col,size);

			glPushMatrix();

			glPushName(col);
			glTranslatef(2.5*col,0,0);
			glTranslatef(0,0,2.5*row);

			glTranslatef(0,0,2);

			glRotatef(-90,1,0,0);

			Primitive* temp = new Rectangle(0,0,2,2);
			temp->draw(1,1);

			glPopName();
			glPopMatrix();
		}

		glPopMatrix();
	}
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