#include "Texture.h"
#include "CGFtexture.h"

Texture::Texture(char*id, char* file, float texlength_s, float texlength_t) : CGFtexture(file) {
	this->id=id;
	this->file = file;
	this->texlength_s = texlength_s;
	this->texlength_t = texlength_t;

	setCoords();
}

void Texture::setCoords() {
	this->texHeight = texlength_t;
	this->texWidth = texlength_s;
}