#include "Circular.h"

Circular::Circular(char* id, float span, float cx, float cy, float cz, float radius, float rang, float sang): Animation(id,span) {
	this->center[0] = cx;
	this->center[1] = cy;
	this->center[2] = cz;

	this->radius = radius;
	this->startang = sang;
	this->rotang = rang + startang;

	startTime = 0;
	sum_angle = 0;
}


void Circular::init(unsigned long t)
{
	startTime=t;
	doReset=false;
}

void Circular::reset()
{
	stop = false;
	startTime = 0;
	sum_angle = 0;
}


void Circular::update(unsigned long t)
{
	if(startTime == 0 || startang+sum_angle >= rotang) {
		startTime = t;
	}

	if(startang+sum_angle >= rotang) {
		stop = true;
		return;
	}

	float time_animation = (t-startTime)/1000.0;

	if(time_animation > span) {
		stop = true;
		return;
	}
	
	sum_angle = (time_animation*(rotang-startang))/span;
	
}

void Circular::draw()
{
	glPushMatrix();
	 glRotated(sum_angle,0,1,0);
	 glRotated(startang,0,1,0);
 
	 glTranslated(radius,0,0);
	glRotated(180,0,1,0); //a frente do  objecto deve estar orientada para +z
}
