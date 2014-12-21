#ifndef CYLINDER_H
#define CYLINDER_H

#include "Primitive.h"

class Cylinder: public Primitive {
private:
	float  base, top, height, slices, stacks;
	std::vector<std::vector<float>> base1Text;
	std::vector<std::vector<float>> base1vert;
	std::vector<std::vector<float>> base2Text;
	std::vector<std::vector<float>> base2vert;

public:
	Cylinder(float base,float top,float height,float slices,float stacks);
	void draw(float text_s, float text_l);

	void calculateBase(std::vector<std::vector<float>>& vecV, std::vector<std::vector<float>>& vecT, float radius, float height);
	void calculateBase();
	void drawBase1();
	void drawBase2();

};


#endif