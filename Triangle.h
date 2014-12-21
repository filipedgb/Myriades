#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Primitive.h"
#include "vector3d.h"

class Triangle: public Primitive {
private:
	float x1,y1,z1, x2,y2,z2, x3,y3,z3;
	float a,b,c, cosB, sinB;
	vector3d normal;

public:
	Triangle(float x1,float y1,float z1,float x2,float y2,float z2, float x3,float y3,float z3);
	void draw(float text_s, float text_l);

};


#endif