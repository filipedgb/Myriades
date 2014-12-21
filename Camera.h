#ifndef CAMERA
#define CAMERA

#include "CGFcamera.h"

class Camera : public CGFcamera {
protected:
	char* id;
	float near,far;
public:
	Camera(char* id, float near, float far) {
		this->id = id;
		this->near = near;
		this->far = far;
	}

	char* getId() {
		return id;
	}
};

#endif