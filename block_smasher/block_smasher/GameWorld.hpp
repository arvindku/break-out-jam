#ifndef _GAMEWORLD_HPP_
#define _GAMEWORLD_HPP_
#include <Box2D\Box2D.h>
#include "Ball.hpp"
#include "GameBoundary.hpp"
#include "Paddle.hpp"
#include "Layout.hpp"

#define TOTAL_NUM_LIVES 3

enum direction{ LEFT, RIGHT, NONE };

enum gameState{ START, PLAY, FAIL, RESET, RESTART, GAMEOVER, WIN};

class GameWorld : public b2ContactListener  {

public:

	GameWorld( float sw, float sh) {

		screenWidth = sw;
		screenHeight = sh;
		
		//Make world with zero gravity
		world = new b2World(b2Vec2(0.0f,0.0f));
		
		//set world timestep options
		timeStep = 1.0f / 60.0f;
		velocityIterations = 6;
		positionIterations = 2;
		
		//set this as contact listener for world to allow callbacks
		world->SetContactListener(this);
		
		//Initialize pointers
		layout = NULL;
		ball = NULL;
		paddle = NULL;

		//set lives
		lives = TOTAL_NUM_LIVES;
	}

	~GameWorld(){
		delete world;
	}

	//SETUP GAME WORLD OBJECTS
	void populateGameWorld();

	//LOGICS 
	//-change game state
	void setGameState(gameState state);
	gameState getGameState(){ return currentState; };
	// - timestep
	void takeTimeStep();
	// - move paddle
	void movePaddle(const direction dir_e);
	// - respond to collision (b2contactListener callback function)
	void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)	;
	// - respond to sensor at bottom to triggert fail state (b2contactListener callback function)
	void BeginContact(b2Contact* contact);

	//RENDER
	void drawGameObjects(float screenWidth, float screenHeight);

private:

	//Box2D members
	b2World *world;
	float timeStep;
	int velocityIterations;
	int positionIterations;

	float screenWidth;
	float screenHeight;

	//Logic members
	gameState currentState;
	int lives;

	//Game Objects 
	Paddle *paddle;
	Ball *ball;
	GameBoundary boundary;
	Layout *layout;
	
};

#endif