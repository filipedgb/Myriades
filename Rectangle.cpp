#include "Rectangle.h"



Rectangle::Rectangle(float x1, float y1, float x2, float y2){
  this->x1 = x1; 
  this->x2 = x2;
  this->y1 = y1; 
  this->y2 = y2;
 }
  
void Rectangle::draw(float text_s, float text_l) {
	glNormal3d(0,0,1);
	glBegin(GL_QUADS);
  	glTexCoord2d(0,0);
    glVertex3d(x1,y1,0);

	glTexCoord2d(abs(x2-x1)/text_s,0);
    glVertex3d(x2,y1,0);

	glTexCoord2d(abs(x2-x1)/text_s,abs(y2-y1)/text_l); 
    glVertex3d(x2,y2,0);

	glTexCoord2d(0,abs(y2-y1)/text_l);
    glVertex3d(x1,y2,0);
	glEnd();
}