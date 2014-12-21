#include <stdio.h>
#include "math.h"
#include "Cylinder.h"


Cylinder::Cylinder(float base, float top, float height, float slices, float stacks) {
	this->base = base;
	this->top = top;
	this->height = height;
	this->slices = slices;
	this->stacks = stacks;

	calculateBase();
}

void Cylinder::draw(float text_s, float text_l) {
	GLUquadricObj *quadObj = gluNewQuadric();

	gluQuadricDrawStyle(quadObj, GLU_FILL);
	gluQuadricTexture(quadObj, GLU_TRUE); 
	gluQuadricNormals(quadObj, GLU_SMOOTH);
	gluCylinder(quadObj, base, top, height, slices, stacks);

	glPushMatrix();
	glScalef(-1,1,1);
	drawBase1();
	glPopMatrix();

	drawBase2();
}

void Cylinder::drawBase1() {
	glBegin(GL_POLYGON);
	glNormal3d(0,0,-1);
	for(unsigned int i=0; i< base1vert.size(); i++) {
		glTexCoord2f(base1Text[i][0], base1Text[i][1]);
		glVertex3d(base1vert[i][0], base1vert[i][1], base1vert[i][2]);
	}
	glEnd();
}

void Cylinder::drawBase2() {
	glBegin(GL_POLYGON);
	glNormal3d(0,0,1);
	for(unsigned int i=0; i< base2vert.size(); i++) {
		glTexCoord2f(base2Text[i][0], base2Text[i][1]);
		glVertex3d(base2vert[i][0], base2vert[i][1], base2vert[i][2]);
	}
	glEnd();
}

void Cylinder::calculateBase() {
	calculateBase(base1vert,base1Text,base,0);
	calculateBase(base2vert,base2Text,top,height);
}

void Cylinder::calculateBase(std::vector<std::vector<float>>& vecV, std::vector<std::vector<float>>& vecT, float radius, float height) {
	float ang=360.0/slices, ang1=0;
	float x,y;
	float tx,ty;
	std::vector<float> v(3);
	std::vector<float> t(2);

	while (ang1<=360) {
		x = radius * cos(ang1 * deg2rad);
		y = radius * sin(ang1 * deg2rad);
		tx = cos(ang1 * deg2rad) * 0.5 + 0.5;
		ty = sin(ang1 * deg2rad) * 0.5 + 0.5;

		v[0] = x;
		v[1] = y;
		v[2] = height;

		t[0] = tx;
		t[1] = ty;

		vecV.push_back(v);
		vecT.push_back(t);

		ang1+=ang;
	}
}