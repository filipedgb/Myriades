#ifndef CIRCULAR
#define CIRCULAR

#include "Animation.h"

#include <vector>
#include "CGFApplication.h"
#include <stdio.h>


class Circular: public Animation {
	float center[3];
	float radius;
	float startang, rotang, sum_angle;
public:
	Circular(char* id, float span, float cx,float cy,float cz,float radius, float rang,float sang);
	void init(unsigned long t);
	void update(unsigned long t);
	void draw();
	void reset();


};


#endif