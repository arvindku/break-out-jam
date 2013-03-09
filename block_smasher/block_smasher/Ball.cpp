#include "Ball.hpp"
#include "SDL_opengl.h"

//ADD BALL TO BOX2D PHYSICS WORLD
void Ball::addToWorld(b2World &world)
{
	//Convert screen coordinates to world coordinates
	b2Vec2 worldPosition = screenToWorld(position);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//bodyDef.fixedRotation = true;
	//bodyDef.angularDamping = 100.0f;
	bodyDef.position.Set(worldPosition.x, worldPosition.y);
	bodyDef.bullet = true;
	body = world.CreateBody(&bodyDef);

	// Define a circle shape for our dynamic body.
	b2CircleShape circle;
	circle.m_radius = radius/SCALING_FACTOR;

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.restitution = 1.0f;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.0f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	body->SetUserData(this);
}

//UPDATE BALL POSITION
void Ball::updateObject()
{
	position = body->GetPosition();
	position = worldToScreen(position);
}

void Ball::setSpeed(float spd)
{
	speed = spd;
	b2Vec2 velocity(speed*sqrt(2.0f),speed*sqrt(2.0f));
	body->SetLinearVelocity(screenToWorld(velocity));
}
//DRAW BALL IN OPENGL
void Ball::drawObject()
{
	const float32 k_segments = 16.0f;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;

	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINE_LOOP);

	for (int32 i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = position + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertex2f(v.x, v.y);
		theta += k_increment;
	}

	glEnd();
}

