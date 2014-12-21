#include "Node.h"

Node::Node() {
	inherits = false;
	animationIndex = 0;
	dlCreated = false;
}

void Node::setId(char* idIn) {
	this->id = idIn;
}

int Node::getIndex() const {
	return animationIndex;
}

int Node::getDisplayListId() const {
	return displayListId;
}

void Node::setDisplayListId(int in) {
	displayListId = in;
}

void Node::incIndex() {
	animationIndex++;
}

void Node::addAnimation(Animation* animationIn) {
	animation.push_back(animationIn);
}

void Node::setMatrix(float matrixIn[16]) {
	for(unsigned int i = 0; i < 16; i++) {
		transfMatrix[i] = matrixIn[i];
	}
}

void Node::setAppearance(Appearance* appearanceIn) {
	this->appearance = appearanceIn;
}

void Node::addDesc(Node* idIn) { 
	descendants.push_back(idIn);
}

void Node::addPrimitive(Primitive* in) { 
	primitives.push_back(in);
}


void Node::toggleInherit() { 
	inherits = !inherits;
}
