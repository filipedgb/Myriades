#ifndef CLOCK
#define CLOCK

#include "Cylinder.h"
#include "Triangle.h"
#include "CGFappearance.h"

class Clock {
	float seconds;
	float angle;

	CGFappearance* clockApp;
	CGFappearance* pointerApp;

	Cylinder* base;
	Triangle* pointer;
	float timeLimit;

public:
	Clock();
	void draw();
	void update(float seconds);
	void setTimeLimit(float t) { timeLimit = t;}
	float getTimeLimit() {return timeLimit; }
};

#endif
