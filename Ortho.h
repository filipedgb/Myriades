#ifndef ORTHO
#define ORTHO

#include "Camera.h"

class Ortho : public Camera {
	char* direction; //axis x =0, y=1, z=2
	float left, right, top, bottom;
public:
	Ortho(char* id, float near, float far,char* direction, float left, float right, float top, float bottom);
	void updateProjectionMatrix(int width, int height);
	void applyView();

};

#endif