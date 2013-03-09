#ifndef _BRICK_H_
#define _BRICK_H_

#include "GameObject.hpp"
#include <Box2D\Box2D.h>

enum brickState{ACTIVE, DEACTIVE, DESTROYED};

#define BRICK_HEIGHT 15.0f
#define BRICK_WIDTH 40.0f

class Brick : public GameObject {

public:
	
	// CONSTRUCTOR, DESTRUCTOR
	Brick(){}
	Brick(b2Vec2 &pos, char n[2]){	
		position = pos;
		strcpy_s(note, n);
		state = ACTIVE;
		body = NULL;
	}
	~Brick(){
		if(body)
			body->GetWorld()->DestroyBody(body);
	}

	void addToWorld(b2World &world);
	void drawObject();
	void updateObject();
	void setState(brickState st) {state = st;}; 
	brickState getState() {return state;};
	b2Vec2 getPos() { return position; };

private:

	char note[2];
	b2Vec2 position;
	brickState state;

};

#endif