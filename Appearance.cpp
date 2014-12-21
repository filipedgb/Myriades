#include "Appearance.h"

Appearance::Appearance(char* ID, float s, char* textref, float* amb, float* diff, float* spec) : CGFappearance(amb,diff,spec,s) {
	id = ID;
	textureref = textref;
}