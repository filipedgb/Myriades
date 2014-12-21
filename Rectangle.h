#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Primitive.h"

class Rectangle: public Primitive {
private:
	float x1,y1,x2,y2;

public:
	Rectangle(float x1, float y1, float x2, float y2);
	void draw(float text_s, float text_l);
};


#endif