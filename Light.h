#ifndef LIGHT
#define LIGHT

#include <CGFappearance.h>
#include <CGFlight.h>

class Light : public CGFlight {

	static int ID;

	char* idName;
	char* type;
	bool marker;
	float exponent;

public:
	Light(char* id, char* type, bool enabled, bool marker, float coords[3], float ambient[4], float diffuse[4],float specular[4]);
	Light(char* id, char* type, bool enabled, bool marker, float coords[3], float ambient[4], float diffuse[4],float specular[4],float angle,float exponent,float target[3]);
	void initLight(char* id, char* type, bool enabled, bool marker, float coords[3], float ambient[4], float diffuse[4],float specular[4]);

	~Light();
	char* getId() const { return idName;}

	float* getAmbient() {return &ambient[0];}
	float* getDiffuse() {return &diffuse[0];}
	float* getSpecular() {return &specular[0];}

	void display();

	bool getEnabled() const {return enabled;}
};

#endif