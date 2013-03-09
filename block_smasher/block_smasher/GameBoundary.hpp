#ifndef _GAMEBOUNDARY_HPP_
#define _GAMEBOUNDARY_HPP_

#include <Box2D\Box2D.h>
#include "GameObject.hpp"

class GameBoundary : public GameObject {

public:

	// CONSTRUCTOR, DESTRUCTOR
	GameBoundary(){}
	GameBoundary(b2Vec2 &tl, b2Vec2 &tr, b2Vec2 &br, b2Vec2 &bl){
		topLeft = tl;
		topRight = tr;
		bottomRight = br;
		bottomLeft = bl;
	}
	~GameBoundary(){}

	//METHODS
	void addToWorld(b2World &world);
	void drawObject();
	void updateObject();

private:
	b2Vec2 topLeft, topRight, bottomRight, bottomLeft;

};

#endif