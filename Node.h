#ifndef NODE_H
#define NODE_H

#include <vector>
#include "Primitive.h"
#include "Appearance.h"
#include "Animation.h"

using namespace std;

class Node {

private:
	char* id;
	bool inherits;
	bool displayList;
	bool dlCreated;

	float transfMatrix[16];
	int animationIndex, displayListId;
	Appearance* appearance;
	vector<Node*> descendants;
	vector<Primitive*> primitives;
	vector<Animation*> animation;
public:
	Node();

	char* getId() { 
		return id;
	}

	bool getInherits() const {return inherits;}

	bool getCreated() const {return dlCreated;}
	void setCreated() {dlCreated = true;}

	bool getDisplayList() const {return displayList;}
	void setDisplayList(bool d) {displayList = d;}

	int getDisplayListId() const;
	int getIndex() const;
	void incIndex();

	void addAnimation(Animation* animationIn);

	void setDisplayListId(int in);
	void setId(char* idIn);
	void setMatrix(float matrixIn[16]);
	void setAppearance(Appearance* appearanceIn);
	void setAnimation(Animation* animationIn);
	void addDesc(Node* idIn);
	void addPrimitive(Primitive* in);

	vector<Node*> getDescendants() {
		return descendants;
	}

	vector<Primitive*> getPrimitives() {
		return primitives;
	}

	Appearance* getAppearance() {
		return appearance;
	}

	vector<Animation*> getAnimation() {
		return animation;
	}

	float* getMatrix() { return &transfMatrix[0]; }

	void toggleInherit();

	friend ostream &operator<<( ostream &output, const Node &o ) { 
		output << "Id : " << o.id << " Inherits : " << o.inherits << "\n";
		for(unsigned int i = 0; i < 16; i++) {
			output << o.transfMatrix[i];
		}
		return output;            
	}

};


#endif