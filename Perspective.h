#ifndef PERSPECTIVE
#define PERSPECTIVE

#include "Camera.h"

class Perspective : public Camera {
	
	float angle;
	float pos[3], target[3];
	float upVector[3];
public:
	Perspective(char* id, float near1, float far1,float angle, float* pos, float* target);
	float* getPos() {return &pos[0];}
	float* getTarget() {return &target[0];}

	void updateProjectionMatrix(int width, int height);
	void applyView();
	void calculateUpVector();
};

#endif