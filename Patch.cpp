#include "Patch.h"

#include <iostream>

Patch::Patch(int o, int pU, int pV, char* c) {
	this->order = o;
	this->partsU = pU;
	this->partsV = pV;
	this->compute = std::string(c);
}

void Patch::addControlPoint(GLfloat x, GLfloat y, GLfloat z) {
	std::vector<GLfloat> temp(3);
	temp[0] = x;
	temp[1] = y;
	temp[2] = z;

	controlPoints.push_back(temp);
	
	if(controlPoints.size() >= (long) pow((double)order+1,2))
		setPoints();
}

void Patch::setPoints() {
	for(int i = 0; i < controlPoints.size(); i++) {
		for(int j = 0; j < controlPoints[i].size(); j++) {
			switch(order) {
			case 1:
				cP1[i][j] = controlPoints[i][j];	
				printf("cp[i][j]: %f\t", cP1[i][j]);
				break;
			case 2:
				cP2[i][j] = controlPoints[i][j];	
				printf("cp[i][j]: %f\t", cP2[i][j]);
				break;
			case 3:
				cP3[i][j] = controlPoints[i][j];	
				printf("cp[i][j]: %f\t", cP3[i][j]);
				break;
			}
		}
		printf("\n");
	}
}

void Patch::initGrid(float text_s, float text_t) {
	switch(order) {
	case 1:
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, order+1,
			0, 1, 3*(order+1), order+1, cP1[0]);
		break;
	case 2:
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, order+1,
			0, 1, 3*(order+1), order+1, cP2[0]);
		break;
	case 3:
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, order+1,
			0, 1, 3*(order+1), order+1, cP3[0]);
		break;
	}

	changeTextCoords(text_s,text_t);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMapGrid2f(partsU, 0.0, 1.0, partsV, 0.0, 1.0);

	//printf("Order : %d\n", order);
	//printf("parts U : %d, V : %d\n", partsU, partsV);
	//printf("Compute : %s\n", compute.c_str());
	//system("pause");
}

void Patch::changeTextCoords(float s, float t) {

	GLfloat tpoint2[4][2] = {
		{0.0, 0.0}, {0.0, 1.0/t},
		{1.0/s, 0.0}, {1.0/s, 1.0/t}};

	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0, 1, 2, 2,  
		0, 1, 4, 2, tpoint2[0]);
}

void Patch::draw(float text_s, float text_t) {
	glPushMatrix();
	initGrid(text_s,text_t);

	glFrontFace(GL_CW);

	if(compute.compare("fill") == 0)
		glEvalMesh2(GL_FILL, 0, partsU, 0, partsV);
	else if(compute.compare("line") == 0)
		glEvalMesh2(GL_LINE, 0, partsU, 0, partsV);
	else glEvalMesh2(GL_POINT, 0, partsU, 0, partsV);

	glFrontFace(GL_CCW);
	glPopMatrix();

	/*
	for (int i = 0; i < controlPoints.size(); i++)	{
		glRasterPos3f(controlPoints[i][0], controlPoints[i][1], controlPoints[i][2]);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0'+i);
	} */
}