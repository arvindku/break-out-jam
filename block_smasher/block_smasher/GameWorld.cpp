#include "GameWorld.hpp"

#define PI 3.14159265f
#define PADDLE_LENGTH 50.0f
#define PADDLE_HEIGHT 12.0f
#define MIN_BALL_ANGLE 40.0f //minimum angle of ball with horizontal allowed in game, should be less than 45

void GameWorld::populateGameWorld(){
	//Make boundary
	boundary = GameBoundary(b2Vec2(10.0f,10.0f), b2Vec2(screenWidth-10.0f,10.0f), b2Vec2(screenWidth-10.0f,screenHeight-10.0f), b2Vec2(10.0f,screenHeight - 10.0f));
	boundary.addToWorld(*world);

	setGameState(START);
}

void GameWorld::drawGameObjects( float screenWidth, float screenHeight){
	//Loop through all game objects and draw them
	if(ball)
		ball->drawObject();
	if(paddle)
		paddle->drawObject();
	boundary.drawObject();
	layout->drawObject();
}

void GameWorld::takeTimeStep(){
	world->Step(timeStep, velocityIterations, positionIterations);
	if(ball)
		ball->updateObject();
	if(paddle)
		paddle->updateObject();
	layout->updateObject();

	if(currentState == PLAY)
	{
		//Make sure ball direction is not too steep
		b2Vec2 currentVel = ball->getBody()->GetLinearVelocity();

		//Make sure ball speed is constant
		if(currentVel.Length() < ball->getSpeed() - 0.15f || currentVel.Length() > ball->getSpeed() + 0.15f)
		{
			float currentSpeed = currentVel.Normalize();
			float velChange = ball->getSpeed() - currentSpeed;
			float impulse = ball->getBody()->GetMass() * velChange;
			currentVel *= impulse;
			ball->getBody()->ApplyLinearImpulse(currentVel, ball->getBody()->GetPosition());
		}
		//Make sure ball is not too flat
		b2Vec2 ballVel = ball->getBody()->GetLinearVelocity();
		double theta = std::atan2(ballVel.y,ballVel.x)*180 / PI;
		if((theta<MIN_BALL_ANGLE && theta>-MIN_BALL_ANGLE) || (theta>180-MIN_BALL_ANGLE) || (theta<-(180 - MIN_BALL_ANGLE)))
			if(ball->getBody()->GetLinearVelocity().y>0.0f)
				ball->getBody()->ApplyLinearImpulse(b2Vec2(0.0f,10.0f), ball->getBody()->GetPosition());
			else ball->getBody()->ApplyLinearImpulse(b2Vec2(0.0f,-10.0f), ball->getBody()->GetPosition());

		//Check for win
		if(layout->getRemainingBricks() == 0 )
		{
			setGameState(WIN);
			return;
		}
	}
	if(currentState == FAIL)
		ball->getBody()->ApplyForceToCenter(b2Vec2(0.0f, 80.0f));
}

void GameWorld::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)	
{

	if(currentState == PLAY)
	{	

		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		//do nothing if ball collides with boundary
		if(fixtureA->GetBody() == boundary.getBody() || fixtureA->GetBody() == boundary.getBody()) return;	
		if(fixtureA->GetBody() == paddle->getBody() || fixtureB->GetBody() == paddle->getBody()) return;

		//If complier reaches here, collision is with brick
		if ( fixtureA->GetBody() == ball->getBody() ){
			void* bodyUserData = fixtureB->GetBody()->GetUserData();
			reinterpret_cast<Brick*>( bodyUserData )->setState(DESTROYED);
			//play sound
			return;
		} else if ( fixtureB->GetBody() == ball->getBody() ){
			void* bodyUserData = fixtureA->GetBody()->GetUserData();
			reinterpret_cast<Brick*>( bodyUserData )->setState(DESTROYED);
			//play sound - note
			return;
		}
	}
}

void GameWorld::BeginContact(b2Contact* contact)
{
	if(currentState == PLAY)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if((fixtureA->GetBody() == paddle->getBody() && fixtureB->GetBody() == ball->getBody() ) || (fixtureB->GetBody() == paddle->getBody() && fixtureB->GetBody() == ball->getBody()))
		{
			//play sound - chord
			//New ball paddle collision rules!
			b2Vec2 posBall = ball->getPos();
			b2Vec2 posPaddle = paddle->getPos();

			float posDiff = posBall.x - posPaddle.x;

			//Check where the ball hit on paddle and give appropriate velocity

			float halfLength = PADDLE_LENGTH/2; 
			b2Vec2 newVel(0.0f, 0.0f); 
			
			// Cases:
			// |****|*****|**|*****|****|
			//    1    2    3   4    5
			
			if(posDiff>0.6f*halfLength) //Case 1
			{
				newVel = ball->getSpeed()*b2Vec2(cos(45.0f*PI/180.0f), -cos(45.0f*PI/180.0f));
				ball->getBody()->SetLinearVelocity(newVel);
			}
			else if(0.6f*halfLength>posDiff && posDiff>0.1f*halfLength) //Case 2
			{
				newVel = ball->getSpeed()*b2Vec2(cos(65.0f*PI/180.0f), -cos(25.0f*PI/180.0f));
				ball->getBody()->SetLinearVelocity(newVel);
			}
			else if(0.1f*halfLength>posDiff && posDiff>-0.1f*halfLength) //Case 3
			{
				newVel = ball->getSpeed()*b2Vec2(cos(90.0f*PI/180.0f), -cos(0.0f*PI/180.0f));
				ball->getBody()->SetLinearVelocity(newVel);
			}
			else if(-0.1f*halfLength>posDiff && posDiff>-0.6f*halfLength) //Case 4
			{
				newVel = ball->getSpeed()*b2Vec2(cos(115.0f*PI/180.0f), -cos(25.0f*PI/180.0f));
				ball->getBody()->SetLinearVelocity(newVel);
			}
			else if(-0.6f*halfLength>posDiff) //Case 5
			{
				newVel = ball->getSpeed()*b2Vec2(cos(135.0f*PI/180.0f), -cos(45.0f*PI/180.0f));
				ball->getBody()->SetLinearVelocity(newVel);
			}
			return;
		}

		if(fixtureA->GetBody() != ball->getBody() && !fixtureA->IsSensor())
		 return;
		if(fixtureB->GetBody() != ball->getBody() && !fixtureB->IsSensor())
		 return;

		//If compiler reaches here, collision is with ground sensor
		//Check for lives remaining
		lives--;
		if(lives == 0)
			setGameState(GAMEOVER);
		else
			setGameState(FAIL);
	}
}

void GameWorld::movePaddle(const direction dir_e)
{
	if(paddle)
	{
		if(dir_e == RIGHT)
			paddle->getBody()->ApplyLinearImpulse(b2Vec2(800.0f,0.0f), paddle->getBody()->GetWorldCenter());
		else if(dir_e == LEFT)
			paddle->getBody()->ApplyLinearImpulse(b2Vec2(-800.0f,0.0f), paddle->getBody()->GetWorldCenter());
	}
}

void GameWorld::setGameState(gameState s)
{
	currentState = s;
	switch(currentState) {
		case START:
		{
			//Make Paddle
			paddle = new Paddle(b2Vec2(screenWidth/2, screenHeight-20.0f), PADDLE_LENGTH, PADDLE_HEIGHT);
			paddle->addToWorld(*world);

			//Make ball
			ball = new Ball(5.0f, b2Vec2(screenWidth/2+10, screenHeight-30.0f));
			ball->addToWorld(*world);
			
			//Make ball, join paddle and ball with a joint, draw start screen
			b2WeldJointDef jointDef;
			jointDef.collideConnected = false;
			jointDef.Initialize(ball->getBody(), paddle->getBody(), ball->getBody()->GetWorldCenter());
			jointDef.userData = "ballPaddleJoint";
			world->CreateJoint(&jointDef);
			
			//Make Layout
			if(!layout)
			{
				layout = new Layout();
				layout->parseLayoutFile("layout.txt");
				layout->addToWorld(*world);
			}

			break;
		}
		case PLAY:
		{
			//Break paddle-ball joint and give velocity to the ball
			b2Joint* joint = world->GetJointList();
			//find the joint
			while(joint->GetNext())
			{
				if(joint->GetUserData() == "ballPaddleJoint")
					world->DestroyJoint(joint);
				joint = joint->GetNext();
			}
			joint = NULL;
			ball->setSpeed(40);
			break;
		}
		case FAIL:
			//Reduce life, change ball physics
			ball->getBody()->SetLinearDamping(0.4f);
			ball->getBody()->GetFixtureList()->SetRestitution(0.8f);
			break;
		case RESET:
			delete ball;
			delete paddle;
			setGameState(START);
			break;
		case RESTART:
			delete ball;
			delete paddle;
			delete layout;
			layout = NULL;
			setGameState(START);
			break;
		case GAMEOVER:
			//draw gameover screen, ask for restart
			ball->getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			//reset number of lives
			lives = TOTAL_NUM_LIVES;
			break;
		case WIN:
			//draw win screen, ask for restart
			ball->getBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
			//reset number of lives
			lives = TOTAL_NUM_LIVES;
			break;
	}
}