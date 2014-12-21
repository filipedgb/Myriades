#include "Variables.h"

void Variables::setMode(char* m) {
	mode = string(m);
}

void Variables::setShading(char* s) {
	shading = string(s);
}

void Variables::setBackground(float r, float g, float b, float a) {
	backgroundR = r;
	backgroundG = g;
	backgroundB = b;
	backgroundA = a;

	background[0] = r;
	background[1] = g;
	background[2] = b;
	background[3] = a;
}

void Variables::setCulling(char* face, char* order) {
	cullFace = string(face);
	cullOrder = string(order);
}

void Variables::setDoublesided(bool d) {
	doublesided = d;
}

void Variables::setLocal(bool l) {
	local = l;
}

void Variables::setEnabled(bool e) {
	enabled = e;
}

void Variables::setAmbient(float r, float g, float b, float a) {
	ambientR = r;
	ambientG = g;
	ambientB = b;
	ambientA = a;

	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;
}
