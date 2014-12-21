#include "Triangle.h"

Triangle::Triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3 ) {
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;

	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;

	this->z1 = z1;
	this->z2 = z2;
	this->z3 = z3;

	a = sqrt( pow(x3-x2,2) + pow(y3-y2,2) + pow(z3-z2,2) );
	b = sqrt( pow(x3-x1,2) + pow(y3-y1,2) + pow(z3-z1,2) );
	c = sqrt( pow(x2-x1,2) + pow(y2-y1,2) + pow(z2-z1,2) );

	cosB = (a*a-b*b+c*c)/(2*a*c);
	sinB = sqrt(1-pow(cosB,2));

	vector3d V1(x2-x1,y2-y1,z2-z1);
	vector3d V2(x3-x1,y3-y1,z3-z1);

	normal = (V1*V2).normalize();
}

void Triangle::draw(float text_s, float text_l) {


	glBegin(GL_TRIANGLES);

	glTexCoord2d(0,0);
	glNormal3d(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(x1,y1,z1);

	glTexCoord2d(c/text_s,0);
	glNormal3d(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(x2,y2,z2);

	glTexCoord2d((c-a*cosB)/text_s, a*sinB/text_l);
	glNormal3d(normal.getX(), normal.getY(), normal.getZ());
	glVertex3f(x3,y3,z3);

	glEnd();
}