
#include "Graph.h"


int Grafo::numNodes() const {
	return nodes.size();
}

Node* Grafo::searchNode(char* id) {
	for(int i = 0; i < numNodes(); i++) {
		if(strcmp(id, nodes[i].getId())==0) {
			return &nodes[i];
		}
	}

	return nullptr;
}

Appearance* Grafo::searchAppearance(char* id) {
	for(int i = 0; i < numAppearances(); i++) {
		if(strcmp(id, appearances[i].getId())==0) {
			return &appearances[i];
		}
	}

	return nullptr;
}

Animation* Grafo::searchAnimation(char* id) {
	for(int i = 0; i < numAnimations(); i++) {
		if(strcmp(id, animations[i]->getId())==0) {
			return animations[i];
		}
	}

	return nullptr;
}

void Grafo::setAppearances() {
	setDescendantsAppearances(searchNode(getRoot()),nullptr);
}

void Grafo::setDescendantsAppearances(Node* n, Appearance* a) {
	if(n->getInherits()) 
		n->setAppearance(a);
	else a = n->getAppearance();

	for(unsigned int i=0; i< n->getDescendants().size();i++)
		setDescendantsAppearances(n->getDescendants()[i],a);
}


void Grafo::setMode(char* m) {
	this->variables.setMode(m);
}

void Grafo::setShading(char* s) {
	this->variables.setShading(s);
}

void Grafo::setBackground(float r, float g, float b, float a) {
	this->variables.setBackground(r,g,b,a);
}

void Grafo::setCulling(char* face, char* order) {
	this->variables.setCulling(face,order);
}

void Grafo::setDoublesided(bool d) {
	this->variables.setDoublesided(d);
}

void Grafo::setLocal(bool l) {
	this->variables.setLocal(l);
}

void Grafo::setEnabled(bool e) {
	this->variables.setEnabled(e);
}

void Grafo::setAmbient(float r, float g, float b, float a) {
	this->variables.setAmbient(r,g,b,a);
}