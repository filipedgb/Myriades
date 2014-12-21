#include "Sphere.h"


Sphere::Sphere(float radius, float slices, float stacks) {
	this->radius = radius;
	this->slices = slices;
	this->stacks = stacks;
}

void Sphere::draw(float text_s, float text_l) {
	GLUquadricObj *quadObj = gluNewQuadric();

	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricTexture(quadObj, GLU_TRUE); 
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluSphere(quadObj,radius,slices,stacks);
}