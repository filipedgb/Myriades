#ifndef APPEARANCE
#define APPEARANCE

#include <CGFappearance.h>
#include <CGFtexture.h>

class Appearance : public CGFappearance {
	char* id;
	char* textureref;

public:
	Appearance(char* ID, float s, char* textref, float* amb, float* diff, float* spec); 

	char* getId() const { return id;}
	char* getTextureRef() const { return textureref;}
	void setTextureRef(char* t) { textureref = t;}

	float* getAmbient() {return &ambient[0];}
	float* getDiffuse() {return &diffuse[0];}
	float* getSpecular() {return &specular[0];}
};

#endif