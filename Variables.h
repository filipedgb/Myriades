#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include <string>

using namespace std;

class Variables {
	/*--------GLOBALS-----------*/
	/*----DRAWING----*/
	//mode: fill, line, point
	string mode;
	//shading: flat, gouraud
	string shading;
	//background
	float backgroundR, backgroundG, backgroundB, backgroundA;
	float background[4];

	/*----CULLING----*/
	//face: none, back, front, both
	string cullFace;
	//order: ccw, cw
	string cullOrder;

	/*----LIGHTING----*/
	bool doublesided;
	bool local;
	bool enabled;
	float ambientR, ambientG, ambientB, ambientA;
	float ambient[4];

public:
	Variables() {};

	//GETTERS
	string getMode() const {
		return mode;
	}
	string getShading() const {
		return shading;
	}
	float getBackgroundR() const {
		return backgroundR;
	}
	float getBackgroundG() const {
		return backgroundG;
	}
	float getBackgroundB() const {
		return backgroundB;
	}
	float getBackgroundA() const {
		return backgroundA;
	}
	float* getBackground() {
		return background;
	}
	string getCullFace() const {
		return cullFace;
	}
	string getCullOrder() const {
		return cullOrder;
	}
	bool getDoublesided() const {
		return doublesided;
	}
	bool getLocal() const {
		return local;
	}
	bool getEnabled() const {
		return enabled;
	}
	float getAmbientR() const {
		return ambientR;
	}
	float getAmbientG() const {
		return ambientG;
	}
	float getAmbientB() const {
		return ambientB;
	}
	float getAmbientA() const {
		return ambientA;
	}

	float* getAmbient() {
		return ambient;
	}

	//SETTERS
	void setMode(char* m);
	void setShading(char* s);
	void setBackground(float r, float g, float b, float a);
	void setCulling(char* face, char* order);
	void setDoublesided(bool d);
	void setLocal(bool l);
	void setEnabled(bool e);
	void setAmbient(float r, float g, float b, float a);
};

#endif