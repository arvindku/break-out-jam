#ifndef _PADDLE_HPP_
#define _PADDLE_HPP_

#include <Box2D\Box2D.h>
#include "GameObject.hpp"

class Paddle : public GameObject {

public:

	// CONSTRUCTOR, DESTRUCTOR
	Paddle(){}
	Paddle(b2Vec2 &pos, float l, float h){	
		halfLength = l/2;
		halfHeight = h/2;
		position = pos;
		color = b2Color(0.0f,0.0f,0.0f);
		//body->SetUserData(this);
	}
	~Paddle(){
		body->GetWorld()->DestroyBody(body);
	}

	//METHODS
	void addToWorld(b2World &world);
	void drawObject();
	void updateObject();
	b2Vec2 getPos() { return position; };

private:

	b2Vec2 position; //center
	float	halfLength, halfHeight;
	b2Color color;

};

#endif
