#ifndef _BALL_HPP_
#define _BALL_HPP_

#include <Box2D\Box2D.h>
#include "GameObject.hpp"

class Ball : public GameObject {

public:

	// CONSTRUCTOR, DESTRUCTOR
	Ball(){}
	Ball(float rad, b2Vec2 &pos){	
		radius = rad;
		position = pos;
		speed = 0.0f;
		color = b2Color(1.0f,0.0f,0.0f);
	}
	~Ball(){
		body->GetWorld()->DestroyBody(body);
	}

	//METHODS
	void addToWorld(b2World &world);
	void drawObject();
	void updateObject();
	void setSpeed(float spd);
	float getSpeed(){return speed;};
	b2Vec2 getPos() { return position; }

private:

	float radius;
	b2Vec2 position; //of center
	float speed;
	b2Color color;

};

#endif
