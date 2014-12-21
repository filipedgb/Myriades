#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <vector>
#include <GL/glut.h>

#define pi acos(-1.0)
#define deg2rad pi/180.0

class Primitive {	
public:
	virtual void draw()  {
		draw(1,1);
	}

	virtual void draw(float text_s, float text_t)= 0;
};

#endif