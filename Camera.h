#ifndef CAMERA_H
#define CAMERA_H

#include "CGFcamera.h"

class Camera : public CGFcamera {
protected:
	char* id;
	float near1,far1;
public:
	Camera(char* id, float near1, float far1) {
		this->id = id;
		this->near1 = near1;
		this->far1 = far1;
	}

	char* getId() {
		return id;
	}

	virtual void applyView() {
		//do nothing
	}
};

#endif