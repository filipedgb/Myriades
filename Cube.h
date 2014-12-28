#ifndef CUBE_H
#define CUBE_H

#include "Rectangle.h"

class Cube: public Primitive {
public:
	Cube();
	void draw(float text_s, float text_t);
};

#endif