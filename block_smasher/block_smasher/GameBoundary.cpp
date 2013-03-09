#include "GameBoundary.hpp"
#include "SDL_opengl.h"

void GameBoundary::addToWorld(b2World &world){

	//Make Boundary chain shape along screen edge
	b2BodyDef boundaryBodyDef;
	body = world.CreateBody(&boundaryBodyDef);
	
	b2Vec2 vs[4];

	vs[0] = screenToWorld(topLeft);
	vs[1] = screenToWorld(topRight);
	vs[2] = screenToWorld(bottomRight);;
	vs[3] = screenToWorld(bottomLeft);;

	b2ChainShape chain;
	chain.CreateLoop(vs, 4);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &chain;
	fixtureDef.density = 0.0f;
	fixtureDef.restitution = 0.7f;
	fixtureDef.friction = 0.0f;

	body->CreateFixture(&fixtureDef);

	//Make sensor at the bottom for fail condition
	b2PolygonShape groundSensorShape;
	groundSensorShape.SetAsBox(vs[2].x-vs[3].x, 0.3f,b2Vec2((vs[2].x-vs[3].x)/2,vs[2].y),0.0f);

	b2FixtureDef fd;
	fd.shape = &groundSensorShape;
	fd.isSensor = true;

	body->CreateFixture(&fd);

}

void GameBoundary::drawObject() {

	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);

	glVertex2f(topLeft.x, topLeft.y);
	glVertex2f(topRight.x, topRight.y);
	glVertex2f(bottomRight.x, bottomRight.y);
	glVertex2f(bottomLeft.x, bottomLeft.y);
	
	glEnd();

	glColor3f(0.5,0.5,0.5);
	glBegin(GL_LINE_LOOP);

	glVertex2f(topLeft.x - 3, topLeft.y - 3);
	glVertex2f(topRight.x + 3, topRight.y - 3);
	glVertex2f(bottomRight.x + 3, bottomRight.y + 3);
	glVertex2f(bottomLeft.x - 3, bottomLeft.y + 3);
	
	glEnd();

}

void GameBoundary::updateObject(){}