#include "Plane.h"

Plane::Plane(void) {
	parts = 1;
}

Plane::Plane(int n) {
	parts = n;
}

void Plane::changeTextCoords(float s, float t) {
	GLfloat textpoints[4][2] = {
        {0.0, 0.0}, {0.0, 1.0/t}, 
        {1.0/s, 0.0}, {1.0/s, 1.0/t}};

	glMap2f(GL_MAP2_TEXTURE_COORD_2,  0, 1, 2, 2,  
		0, 1, 4, 2, &textpoints[0][0]);
}

void Plane::initGrid(float text_s, float text_t) {
	GLfloat controlpoints[4][3] = {
        {-0.5, 0.0, 0.5}, {-0.5, 0.0 ,-0.5}, 
        {0.5, 0.0, 0.5}, {0.5, 0.0, -0.5}};

	GLfloat normalpoints[4][3] = {
	{0,1,0}, {0,1,0}, 
	{0,1,0}, {0,1,0} };

	
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 2,
           0, 1, 6, 2, &controlpoints[0][0]);
	glMap2f(GL_MAP2_NORMAL, 0, 1, 3, 2,
		   0, 1, 6, 2, &normalpoints[0][0]);
	
	changeTextCoords(text_s,text_t);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMapGrid2f(parts, 0.0, 1.0, parts, 0.0, 1.0);
}

Plane::~Plane(void) {}

void Plane::draw(float text_s, float text_t) {
	glPushMatrix();
	initGrid(text_s,text_t);
	glEvalMesh2(GL_FILL, 0, parts, 0, parts);
	glPopMatrix();
}
