#ifndef _LAYOUT_H_
#define _LAYOUT_H_

#include "Brick.hpp"
#include "GameObject.hpp"

//The layout of the bricks -> rows/columns must correspond to layout.txt file data
#define LAYOUT_ROWS 7
#define LAYOUT_COLUMNS 7

#define VERTICAL_GAP 20.0f
#define HORIZONTAL_GAP 45.0f

#define FIRST_BRICK_X 65.0f
#define FIRST_BRICK_Y 50.0f

class Layout : public GameObject
{
public:
	Layout(){
	activeBricks = LAYOUT_ROWS*LAYOUT_COLUMNS;
	bricksArray = NULL;
	file = NULL;
	};
	~Layout(){
	int totalSize =  LAYOUT_ROWS*LAYOUT_COLUMNS;
	for(int i = 0; i< totalSize; i++)
		if(bricksArray[i])
			delete bricksArray[i];
	delete [] bricksArray;
	};

	//Parsing functions
	void parseLayoutFile(const char* filename);
	int getToken(char *token);

	//World functions
	void addToWorld(b2World &world);
	void drawObject();
	void updateObject();

	int getRemainingBricks() { return activeBricks; };

private:

	int activeBricks;
	Brick **bricksArray;
	FILE *file;

};

#endif