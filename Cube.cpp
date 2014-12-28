#include "Cube.h"

Cube::Cube() {}

void Cube::draw(float text_s, float text_t) {
	
	Rectangle* rect = new Rectangle(0,0,1,1);

	float tra1[16] = {
		1.0,0.0,0.0,0.0,
		0.0,1.0,0.0,0.0,
		0.0,0.0,1.0,0.0,
		-0.5,-0.5,0.5,1
	};

	float rotx[16] = {
		1,0,0,0,
		0,cos(pi/2),sin(pi/2),0,
		0,-sin(pi/2),cos(pi/2),0,
		0,0,0,1
	};

	float roty[16] = {
		cos(pi/2),0,sin(pi/2),0,
		0,1,0,0,
		-sin(pi/2),0,cos(pi/2),0,
		0,0,0,1
	};

	// face +z
	glPushMatrix() ;
	glMultMatrixf(tra1); 
	rect->draw(text_s,text_t);
	glNormal3f(0.0,0.0,1.0); // light
	glPopMatrix();

	// face -y
	glPushMatrix() ;
	glMultMatrixf(rotx); 
	glMultMatrixf(tra1); 
	glNormal3f(0.0,0.0,1.0); //light 
	rect->draw(text_s,text_t);
	glPopMatrix() ;

	// face -z
	glPushMatrix() ;
	glMultMatrixf(rotx); 
	glMultMatrixf(rotx); 
	glMultMatrixf(tra1); 
	glNormal3f(0.0,0.0,1.0); //light 
	rect->draw(text_s,text_t);
	glPopMatrix();

	// face +y
	glPushMatrix() ;
	glMultMatrixf(rotx); 
	glMultMatrixf(rotx); 
	glMultMatrixf(rotx); 
	glMultMatrixf(tra1); 
	glNormal3f(0.0,0.0,1.0);
	rect->draw(text_s,text_t);
	glPopMatrix();

	// face -x
	glPushMatrix() ;
	glMultMatrixf(roty);
	glMultMatrixf(tra1); 
	glNormal3f(0.0,0.0,1.0);
	rect->draw(text_s,text_t);
	glPopMatrix();

	// face +x
	glPushMatrix() ;
	glMultMatrixf(roty);
	glMultMatrixf(roty);
	glMultMatrixf(roty);
	glMultMatrixf(tra1); 
	glNormal3f(0.0,0.0,1.0);
	rect->draw(text_s,text_t);
	glPopMatrix();
}
