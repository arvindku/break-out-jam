#include "Paddle.hpp"
#include "SDL_opengl.h"

void Paddle::addToWorld(b2World &world)
{
	b2Vec2 worldPosition = screenToWorld(position);

	b2BodyDef paddleBodyDef;
	
	paddleBodyDef.fixedRotation = true;
	paddleBodyDef.type = b2_dynamicBody;
	paddleBodyDef.linearDamping = 50.0f;
	paddleBodyDef.position.Set(worldPosition.x, worldPosition.y);
	body = world.CreateBody(&paddleBodyDef);

	b2PolygonShape paddleBox;
	paddleBox.SetAsBox(halfLength/SCALING_FACTOR, halfHeight/SCALING_FACTOR);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &paddleBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixtureDef.restitution = 0.7f;

	body->CreateFixture(&fixtureDef);

	// Restrict paddle along the x axis by creating a prismatic joint
	b2BodyDef bd;
	bd.position.Set(0.0f, 0.0f);
	b2Body* bodyNew = world.CreateBody(&bd);
	
	b2PrismaticJointDef jointDef;
	b2Vec2 worldAxis(1.0f, 0.0f);
	jointDef.collideConnected = true;

	jointDef.Initialize(body, bodyNew, b2Vec2(0.0f,0.0f), worldAxis);
	world.CreateJoint(&jointDef);
	
	body->SetUserData(this);
}

void Paddle::drawObject()
{
			glBegin(GL_QUADS);

			glColor3f(color.r,color.g,color.b);
			glVertex2f(position.x-halfLength,position.y-halfHeight);
			glVertex2f(position.x+halfLength,position.y-halfHeight);
			glVertex2f(position.x+halfLength,position.y+halfHeight);
			glVertex2f(position.x-halfLength,position.y+halfHeight);

			glEnd();
}
	
void Paddle::updateObject()
{
	position = body->GetPosition();
	position = worldToScreen(position);
}