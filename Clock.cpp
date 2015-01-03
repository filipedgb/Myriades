#include "Clock.h"

Clock::Clock() { 
	base = new Cylinder(1,1,0.1,30,30);

	pointer = new Triangle(0.1,0,0,0,0.9,0,-0.1,0,0);

	clockApp = new CGFappearance();
	clockApp->setTexture("clock.jpg");

	pointerApp = new CGFappearance();
	pointerApp->setTexture("nonumber.jpg");

	timeLimit = 30;
}

void Clock::update(float segundos) { 
	angle = (segundos*360)/timeLimit;
}


void Clock::draw() {  
	glPushMatrix();

	pointerApp->apply();

	glTranslated(0,0,0.15);
	glRotated(-angle,0,0,1);
	pointer->draw(1,1);
	glPopMatrix();

	clockApp->apply();
	base->draw(1,1);
}
