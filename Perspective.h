#ifndef PERSPECTIVE
#define PERSPECTIVE

#include "Camera.h"
#include "vector3d.h"
#include <vector>

class Perspective : public Camera {
	int index;
	float angle;
	float pos[3];
	float target[3];
	float upVector[3];
	std::vector<vector3d> points;
public:
	Perspective(char* id, float near1, float far1,float angle, float* pos, float* target);
	float* getPos() {return &pos[0];}
	float* getTarget() {return &target[0];}

	void updateProjectionMatrix(int width, int height);
	void applyView(char player);
	void calculateUpVector();

	void calculatePoints();
	std::vector<vector3d> getPoints();

};

#endif