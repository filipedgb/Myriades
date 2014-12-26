#ifndef ANIMATION_H
#define ANIMATION_H

#include <iostream>

class Animation {
	
protected:
	char* id;
	float span; //tempo que dura a animacao (seg)

	unsigned long startTime;
	unsigned char doReset;
	bool stop;

public:
	Animation(char* id, float s) {this->id = id; this->span = s; stop = false; startTime = 0;}
	char* getId() {return id;}
	float getSpan() const {return span;}

	bool isStopped() const { return stop;}
	
	virtual void init(unsigned long t)=0;
	virtual void update(unsigned long t)=0;
	virtual void draw()=0;
	virtual void reset()=0;
};

#endif