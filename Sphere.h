#ifndef SPHERE_H
#define SPHERE_H

#include "Primitive.h"

class Sphere: public Primitive {
private:
	float radius,slices,stacks;

public:
	Sphere(float radius, float slices, float stacks);
	void draw(float text_s, float text_l);

};


#endif