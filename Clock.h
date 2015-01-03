#ifndef CLOCK
#define CLOCK

#include "Cylinder.h"
#include "Triangle.h"
#include "CGFappearance.h"


class Clock {
	float seconds;
	float angle;

	float timeLimit;

	CGFappearance* clockApp;
	CGFappearance* pointerApp;

	Cylinder* base;
	Triangle* pointer;


public:
	Clock();
	void draw();
	void update(float seconds);


};




#endif