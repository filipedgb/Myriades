#ifndef TORUS_H
#define TORUS_H

#include "Primitive.h"


class Torus: public Primitive {
private:
	float inner, outer, slices, loops;

	std::vector<std::vector<float>> textCoords;
	std::vector<std::vector<float>> vertexCoords;
	std::vector<std::vector<float>> normalsCoords;
	public:
		Torus(float inner, float outer, float slices, float loops);
		void draw(float text_s, float text_l);
		void calculateCoordinates();
 };


#endif