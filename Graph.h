#ifndef GRAFO_H_
#define GRAFO_H_

#include "Node.h"
#include "Variables.h"

using namespace std;

class Grafo {
	char* rootId;
	std::vector<Node> nodes;
	Variables variables;
	std::vector<Appearance> appearances;
	std::vector<Animation*> animations;
public:
	void addNode(Node objIn) { 
		nodes.push_back(objIn);
	}

	void addAppearance(Appearance a) {
		appearances.push_back(a);
	}

	void addAnimation(Animation* a) {
		animations.push_back(a);
	}

	vector<Node> getNodes() const {
		return nodes;
	}

	vector<Appearance> getAppearances() const {
		return appearances;
	}

	vector<Animation*> getAnimation() const {
		return animations;
	}

	char* getRoot() {
		return rootId;
	}

	void setRoot(char* rootId) {
		this->rootId = rootId;
	}

	int numNodes() const;
	int numAppearances() const { return appearances.size();}
	int numAnimations() const { return animations.size();}

	Node* searchNode(char* id);

	Appearance* searchAppearance(char* id);
	Animation* searchAnimation(char* id);

	Variables getVariables() const {return variables;}

	void setAppearances();
	void setDescendantsAppearances(Node* n, Appearance* a);
	
	void setMode(char* m);
	void setShading(char* s);
	void setBackground(float r, float g, float b, float a);
	void setCulling(char* face, char* order);
	void setDoublesided(bool d);
	void setLocal(bool l);
	void setEnabled(bool e);
	void setAmbient(float r, float g, float b, float a);
};





#endif /* GRAPH_H_ */