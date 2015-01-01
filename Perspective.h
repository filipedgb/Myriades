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

	bool side;

	std::vector<vector3d> points;

	bool rotative; //if activated camera will rotate 

public:
	Perspective(char* id, float near1, float far1,float angle, float* pos, float* target);
	float* getPos() {return &pos[0];}
	float* getTarget() {return &target[0];}

	void updateProjectionMatrix(int width, int height);
	void applyView();
	void calculateUpVector();

	void setRotative() {
		rotative = true;
	}

	void toggleSide() {
		side = !side;
	}

	void calculatePoints();
	std::vector<vector3d> getPoints();
};

#endif