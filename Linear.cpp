#include "Linear.h"
#include "Triangle.h"

Linear::Linear(char* id, float span): Animation(id,span) {
	dx = 0; dy = 0; dz = 0;
	index = 1; last_index = 0;
	temp = 0;
	startTime = 0;
	inc_counter = 0;
	span_per_segment = span/controlPoints.size()-1;
}


void Linear::addControlPoint(float x, float y, float z) {
	vector3d v = vector3d(x,y,z);
	controlPoints.push_back(v);
}

void Linear::init(unsigned long t) {
	startTime=t;
	doReset=false;
}

void Linear::reset() {
	startTime = 0;
	index = 0;
	stop = false;
	dx = 0; dy = 0; dz = 0;
	index = 1; last_index = 0;
}

void Linear::update(unsigned long t) {
	if(startTime == 0) startTime = t;
	float animT = (t - startTime)/1000.0;

	if(animT/span_per_segment > index) {
		dx = 0; dy = 0; dz = 0;
		last_index = index;
		index++;
	}

	if(index > controlPoints.size()-1) {
		stop = true;
		return;
	}

	span_per_segment =  span/(controlPoints.size()-1);

	float time_in_segment = animT - span_per_segment*last_index;

	cp_x = controlPoints[last_index].getX();
	cp_y = controlPoints[last_index].getY();
	cp_z = controlPoints[last_index].getZ();

	vector3d delta = controlPoints[index]-controlPoints[last_index];

	direction = delta.angleVectors(vector3d(0,0,1));

	vector3d temp = vector3d(0,0,1)*delta;

	if(temp.getY() < 0) {
		direction = 360-direction;
	}

	dx = (delta.getX()*time_in_segment)/span_per_segment;
	dy = (delta.getY()*time_in_segment)/span_per_segment;
	dz = (delta.getZ()*time_in_segment)/span_per_segment;
}

void Linear::draw() {
	glTranslated(dx+cp_x,cp_y+dy,cp_z+dz);
	glRotated(direction,0,1,0);
}
