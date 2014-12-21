#include "Light.h"

int Light::ID = 1;

Light::Light(char* id, char* type, bool enabled, bool marker, float coords[3], float ambient[4], float diffuse[4],float specular[4]): CGFlight(GL_LIGHT0 + this->ID++,coords) {
	initLight(id,type, enabled, marker, coords , ambient, diffuse, specular);
}


Light::Light(char* id, char* type, bool enabled, bool marker, float coords[3], float ambient[4], float diffuse[4],float specular[4],float angle,float exponent,float target[3]): CGFlight(GL_LIGHT0 + this->ID++,coords) {

	initLight(id, type, enabled, marker, coords, ambient, diffuse,specular);

	this->angle = angle;
	this->exponent = exponent;

	this->direction[0] = target[0] - position[0];
	this->direction[1] = target[1] - position[1];
	this->direction[2] = target[2] - position[2];

	this->setAngle(angle);


	glLightf(ID-1, GL_SPOT_EXPONENT, exponent);
}

void Light::initLight(char* id, char* type, bool enabled, bool marker, float coords[3], float ambient[4], float diffuse[4],float specular[4]) {
	this->idName = id;
	this->type = type;
	this->enabled = enabled;
	this->marker = marker;

	this->position[0] = coords[0];this->position[1] = coords[1];this->position[2] = coords[2];this->position[3] = 1.0;
	this->ambient[0] = ambient[0];this->ambient[1] = ambient[1];this->ambient[2] = ambient[2];
	this->diffuse[0] = diffuse[0];this->diffuse[1] = diffuse[1];this->diffuse[2] = diffuse[2];
	this->specular[0] = specular[0];this->specular[1] = specular[1];this->specular[2] = specular[2];

	this->setAmbient(this->ambient);
	this->setDiffuse(this->diffuse);
	this->setSpecular(this->specular);
}

void Light::display() {
	if(this->marker)
		this->draw();

	this->update();
}

Light::~Light(){
}
