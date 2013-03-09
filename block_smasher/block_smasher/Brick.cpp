#include "Brick.hpp"
#include "SDL_opengl.h"

void Brick::addToWorld(b2World &world)
{
	if(state == ACTIVE)
	{
		b2Vec2 worldPosition = screenToWorld(position);

		b2BodyDef brickBodyDef;
		brickBodyDef.position.Set(worldPosition.x, worldPosition.y);
		body = world.CreateBody(&brickBodyDef);

		b2PolygonShape brickBox;
		brickBox.SetAsBox(BRICK_WIDTH/(2*SCALING_FACTOR), BRICK_HEIGHT/(2*SCALING_FACTOR));

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &brickBox;
		fixtureDef.density = 0.0f;
		fixtureDef.friction = 0.0f;
		fixtureDef.restitution = 1.0f;

		body->CreateFixture(&fixtureDef);
		body->SetUserData(this);
	}
}

void Brick::drawObject()
{
	if(state == ACTIVE)
	{
			glBegin(GL_QUADS);

			glColor3f(0.0f,0.0f,1.0f);
			glVertex2f(position.x-(BRICK_WIDTH/2),position.y-(BRICK_HEIGHT/2));
			glVertex2f(position.x+(BRICK_WIDTH/2),position.y-(BRICK_HEIGHT/2));
			glVertex2f(position.x+(BRICK_WIDTH/2),position.y+(BRICK_HEIGHT/2));
			glVertex2f(position.x-(BRICK_WIDTH/2),position.y+(BRICK_HEIGHT/2));

			glEnd();
	}
}
	
void Brick::updateObject() { 
	if(state == DESTROYED)
	{
		body->GetWorld()->DestroyBody(body);
		body = NULL;
		state = DEACTIVE;
	}
}