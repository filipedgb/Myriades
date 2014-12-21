#ifndef PATCH
#define PATCH

#include "Primitive.h"

class Patch: public Primitive {
	std::vector<std::vector<GLfloat>> controlPoints;

	int order;
	int partsU, partsV;

	std::string compute;

	//control points
	GLfloat cP1[4][3];
	GLfloat cP2[9][3];
	GLfloat cP3[16][3];

public:
	Patch(int o, int pU, int pV, char* c);

	void draw(float text_s, float text_l);

	void setPoints();
	void addControlPoint(GLfloat x, GLfloat y, GLfloat z);

	void initGrid(float text_s, float text_t);
	void changeTextCoords(float s, float t);
};

#endif