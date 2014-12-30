#include "Ortho.h"
#include "CGFapplication.h"

Ortho::Ortho(char* id, float near, float far, char* direction, float left, float right, float top, float bottom): Camera(id,near,far) {
	this->direction = direction;
	this->left = left;
	this->right = right;
	this->top = top;
	this->bottom = bottom;
}

void Ortho::updateProjectionMatrix(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(left, right, bottom, top, near1, far1);
	glMatrixMode(GL_MODELVIEW);
}

void Ortho::applyView()
{
	CGFcamera::applyView();
		
	if(!strcmp("x",direction)) glRotatef(-90,0,1,0);
	else if (!strcmp("y",direction)) glRotatef(90,1,0,0);
	
}
