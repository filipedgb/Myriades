#ifndef PLANE
#define PLANE

#include "Primitive.h"

class Plane: public Primitive {
	int parts;

public:
	Plane(void);
	Plane(int);
	~Plane(void);

	void draw(float text_s, float text_t);

	void setPoints();
	void changeTextCoords(float s, float t);

	void initGrid(float text_s, float text_t);
};

#endif