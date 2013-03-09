#ifndef _GAMEOBJECT_HPP_
#define _GAMEOBJECT_HPP_

#include <Box2D\Box2D.h>

#define SCALING_FACTOR 10.0f

class GameObject {

public:

	virtual void addToWorld(b2World &world) = 0;
	virtual void updateObject() = 0;
	virtual void drawObject() = 0;

	b2Vec2 worldToScreen(b2Vec2 &worldVector){ return b2Vec2(worldVector.x*SCALING_FACTOR,worldVector.y*SCALING_FACTOR); };
	b2Vec2 screenToWorld(b2Vec2 &screenVector){ return b2Vec2(screenVector.x/SCALING_FACTOR,screenVector.y/SCALING_FACTOR); };
	b2Body* getBody(){return body;};

protected:
	b2Body* body;

};

#endif