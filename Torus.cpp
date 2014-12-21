#include "Torus.h"

Torus::Torus(float inner, float outer, float slices, float loops) {
	this->inner = inner;
	this->outer = outer;
	this->slices = slices;
	this->loops = loops;

	calculateCoordinates();
}

void Torus::calculateCoordinates() {
	std::vector<float> vert(3);
	std::vector<float> vNormal(3);
	std::vector<float> text(2);
	float majorStep = 2.0f * pi / slices;   
	float minorStep = 2.0f * pi / loops;   

	for (unsigned int i=0; i<slices; ++i) {   
		float a0 = i * majorStep;   
		float a1 = a0 + majorStep;   
		float x0 = cos(a0);   
		float y0 = sin(a0);   
		float x1 = cos(a1);   
		float y1 = sin(a1);   

		for (unsigned int j=0; j<=loops; ++j)  {   
			float b = j * minorStep;   
			float c = cos(b);   
			float r = inner * c + outer;   
			float z = inner * sin(b);   

			text[0] = (float) i/slices;
			text[1] = (float) j/loops;
			textCoords.push_back(text);
			vNormal[0] = x0*c;   
			vNormal[1] = y0*c;   
			vNormal[2] = z/inner;   
			normalsCoords.push_back(vNormal);  
			vert[0] = x0*r;
			vert[1] = y0*r;
			vert[2] = z;
			vertexCoords.push_back(vert);

			text[0] = (float) (i+1)/slices;
			text[1] = (float) j/loops;
			textCoords.push_back(text);
			vNormal[0] = x1*c;   
			vNormal[1] = y1*c;   
			vNormal[2] = z/inner;   
			normalsCoords.push_back(vNormal);
			vert[0] = x1*r;
			vert[1] = y1*r;
			vert[2] = z;
			vertexCoords.push_back(vert);
		}
	}
}

void Torus::draw(float text_s, float text_l) {	
	glBegin(GL_TRIANGLE_STRIP);
	for(unsigned int i=0; i<vertexCoords.size();i++) {
		glTexCoord2f(textCoords[i][0]/text_s, textCoords[i][1]/text_l);
		glNormal3f(normalsCoords[i][0], normalsCoords[i][1], normalsCoords[i][2]);
		glVertex3f(vertexCoords[i][0], vertexCoords[i][1], vertexCoords[i][2]);
	}
	glEnd();
}