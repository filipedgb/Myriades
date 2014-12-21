#ifndef TEXTURE_H
#define TEXTURE_H

#include "CGFtexture.h"

class Texture : public CGFtexture {
private:
	char* id, *file;
	float texlength_s;
	float texlength_t;

public:
	Texture(char*id, char* file, float texlength_s, float texlength_t);
	
	char* getId() { 
		return id;
	}

	char* getFile() {
		return file;
	}

	float getLengthS() {
		return texlength_s;
	}

	float getLengthT() {
		return texlength_t;
	}

	void setCoords();


};


#endif


