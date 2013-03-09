#include "SDL.h"
#include "SDL_opengl.h"
#include <Box2D\Box2D.h>
#include "GameWorld.hpp"
#include "SoundManager.h"

#define SCREEN_HEIGHT 500
#define SCREEN_WIDTH 400

int main( int argc, char* args[] )
{
    SDL_Init(SDL_INIT_EVERYTHING);
   
		//set openGL memory usage attributes
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

		//Set window Title
		SDL_WM_SetCaption("OPenGL Window",NULL);

		//Set SDL video mode - for fullscreen add SDL_FULLSCREEN
		SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,SDL_OPENGL);

		//refresh screen at new frame
		glClearColor(1,1,1,1);
		
		//set display area 
		glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

		//Gradient coloring
		glShadeModel(GL_SMOOTH);

		//Set 2D drawing mode
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Disable stuff used in 3D
		glDisable(GL_DEPTH_TEST);

		//SDL_Delay(1);

		bool isRunning = TRUE;
		SDL_Event event; 

		GameWorld gameWorld(SCREEN_WIDTH,SCREEN_HEIGHT);
		//populate game with objects, set state
		gameWorld.populateGameWorld();
		//ENUM for paddle direction
		direction dir_e = NONE;

		// ************** MAIN LOOP ************** //
		while(isRunning)
		{
			//INPUT
			while(SDL_PollEvent(&event))
			{
				//If window is closed
				if(event.type == SDL_QUIT)
				{
					isRunning = FALSE;
				}

				//If esc key is released
				if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				{
					isRunning = FALSE;
				}

				if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_r)
				{
					glClearColor(1,0,0,1);
				}

				
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
				{
					if(gameWorld.getGameState() == START)
						gameWorld.setGameState(PLAY);
					if(gameWorld.getGameState() == FAIL)
						gameWorld.setGameState(RESET);
					if(gameWorld.getGameState() == GAMEOVER || gameWorld.getGameState() == WIN)
						gameWorld.setGameState(RESTART);
				}
				
				if(event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_LEFT)
					{
						dir_e = LEFT;
					} 
					else if (event.key.keysym.sym == SDLK_RIGHT)
					{
						dir_e = RIGHT;
					}
				} 
				else if(event.type == SDL_KEYUP)
					if (event.key.keysym.sym == SDLK_LEFT)
					{
						if(dir_e == LEFT) dir_e = NONE;
					}
					else if (event.key.keysym.sym == SDLK_RIGHT)
					{
						if(dir_e == RIGHT) dir_e = NONE;
					}
			}

			//LOGIC
			gameWorld.takeTimeStep();
			gameWorld.movePaddle(dir_e);

			//RENDERING
			glClear(GL_COLOR_BUFFER_BIT);
			glPushMatrix();
			glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,-1,1);
			glColor3ui(0,0,255);

			//draw game objects
			gameWorld.drawGameObjects(SCREEN_WIDTH,SCREEN_HEIGHT);
			glPopMatrix();
			
			SDL_GL_SwapBuffers();

		}

		// ************** CLOSE WINDOW ************** //

		//Quit SDL
    SDL_Quit();
    
    return 0;    
}
