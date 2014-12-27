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

	drawBase();

	for(unsigned int row = 0; row < size; row++) {
		for(unsigned int col = 0; col < size; col++) {

			printf("size: %d row: %d, col: %d\n",row,col,size);

			glPushMatrix();

			glTranslatef(4*col,0,0) ;
			glTranslatef(0,0,4*row) ;

			glTranslatef(1,1,1) ;
			glRotatef(90,1,0,0) ;

			if(	board[row][col] != NULL) {
				glPushMatrix();

				printf("Esta null\n");
				board[row][col]->draw(1,1);

				glPopMatrix();
			}
			glPopMatrix();
		}

	}

}

void Board::drawBase() {
	glPushMatrix();

	glTranslatef(0,0,4*size) ;
	glRotatef(-90,1,0,0) ;

	Primitive* temp = new Rectangle(0,0,4*size,4*size);
	boardTex->apply();
	boardApp->apply();
	temp->draw(1,1);

	glPopMatrix();
}

void Board::boardParser(string answer) {
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
