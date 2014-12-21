#ifndef LINEAR
#define LINEAR

#include "Animation.h"
#include <vector>
#include "CGFApplication.h"
#include <stdio.h>
#include "vector3d.h"

class Linear: public Animation {
	std::vector<vector3d> controlPoints;
	unsigned int index, last_index;
	float temp, cp_x,cp_y,cp_z;
	float dx, dy, dz, span_per_segment, direction;
	int inc_counter;

public:
	Linear(char* id, float span);

	void addControlPoint(float x,float y, float z);
	void init(unsigned long t);
	void update(unsigned long t);
	void draw();
	void reset();
};

#endif