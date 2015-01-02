#include "Perspective.h"
#include "CGFapplication.h"

Perspective::Perspective(char* id, float near, float far, float angle, float* pos, float* target): Camera(id,near,far) {
	this->angle = angle;

	this->pos[0] = pos[0];
	this->pos[1] = pos[1];
	this->pos[2] = pos[2];

	this->target[0] = target[0];
	this->target[1] = target[1];
	this->target[2] = target[2];

	this->index = 0;
	this->rotative = false;

	calculateUpVector();
}

void Perspective::updateProjectionMatrix(int width, int height)
{
	float aspect= (float) width / (float) height;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle,aspect,near1,far1);
	glMatrixMode(GL_MODELVIEW);
}

void Perspective::calculateUpVector() {
	float dir[3] = {target[0]-pos[0], target[1]-pos[1], target[2]-pos[2]};
	float dirLength = sqrt(pow(dir[0],2) + pow(dir[1],2) + pow(dir[2],2));

	if(((int) (dir[0]/dirLength) == 0) &&  (((int) (dir[1]/dirLength) == 1) || ((int) (dir[1]/dirLength) == -1)) && ((int) (dir[2]/dirLength) == 0)) {
		upVector[0] = - dir[1]/dirLength;
		upVector[1] = dir[0]/dirLength;
		upVector[2] = dir[2]/dirLength;
	}
	else {
		upVector[0] = 0;
		upVector[1] = 1;
		upVector[2] = 0;
	}
}


void Perspective::calculatePoints() { 
	float numPoints = 100;
	float incAngle = 180/numPoints;
	float angulo = 90;
	float x,  y,  z;
	float raio = 1;

	while(angulo <= 270+incAngle){
		x = target[0] + raio*cos(angulo*(acos(-1.0)/180));
		y = 1;
		z = target[2] + raio*sin(angulo*(acos(-1.0)/180));

		vector3d ponto = vector3d(x,y,z);

		points.push_back(ponto);

		angulo+= incAngle;
	}

}

vector<vector3d> Perspective::getPoints() { 
	return points;
}


void Perspective::applyView()
{
	CGFcamera::applyView();

	if(rotative) { 

		if(!side) {
			gluLookAt(points[index].getX(),points[index].getY(),points[index].getZ(),10,0,10,0,1,0);

			if(index < points.size()-1)
				index++;
		}

		else {
			gluLookAt(points[index].getX(),points[index].getY(),points[index].getZ(),10,0,10,0,1,0);

			if(index != 0) 
				index--;

		}

	}
	else gluLookAt(pos[0],pos[1],pos[2],target[0],target[1],target[2],0,1,0);
}

