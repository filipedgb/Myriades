

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Math.h"
#include <iostream>

/* Esta classe tem como objectivo facilitar a representação do espaço tri-dimensional, servindo tanto para representar pontos como vectores.
Contém também um conjunto de overloads adequados para operações vectoriais
*/


class vector3d {
	float x,y,z; 

public: 
	vector3d(float a, float b, float c) {
		x = a;
		y = b;
		z = c;
	}

	vector3d() {};

	void setX(float a){ x = a ; } 
	void setY(float a) { y = a ; }
	void setZ(float a) { z = a ; }

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }

	vector3d operator+(const vector3d & v) const {
		float a = this->x + v.x;
		float b = this->y + v.y;
		float c = this->z + v.z;

		vector3d res(a,b,c);
		return res;
	}

	vector3d operator-(const vector3d & v) const {
		float a = this->x - v.x;
		float b = this->y - v.y;
		float c = this->z - v.z;

		vector3d res(a,b,c);
		return res;
	}

	vector3d operator*(const vector3d & v) const {
		float nx = y * v.z - z * v.y;
		float ny = z * v.x - x * v.z;
		float nz = x * v.y - y * v.x;

		vector3d vec(nx,ny,nz);
		return vec;
	}

	vector3d operator*(const float k) const {
		vector3d vec(k*x,k*y,k*z);
		return vec;
	}

	float vecSize() const {
		return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
	}

	vector3d interpolate(const vector3d & v) const {
		float a = (this->x + v.x)/2.0;
		float b = (this->y + v.y)/2.0;
		float c = (this->z + v.z)/2.0;

		vector3d res(a,b,c);
		return res;
	}

	vector3d interpolate(const vector3d & v, float k) const {
		float k1= k;
		float k2= 1-k;

		float a = (k1*this->x + k2*v.x);
		float b = (k1*this->y + k2*v.y);
		float c = (k1*this->z + k2*v.z);

		vector3d res(a,b,c);
		return res;
	}

	vector3d normalize() const {
		float size = vecSize();
		vector3d vec (x/size, y/size, z/size);
		return vec;
	}

	float angleVectors(const vector3d & v) {
		float dot_product = this->getX()*v.getX() + this->getY()*v.getY() + this->getZ()*v.getZ();
		float normals = this->vecSize()*v.vecSize();

		float radians = acos(dot_product/normals); 

		return (float) radians*(180/acos(-1.0));
	}

};


#endif

