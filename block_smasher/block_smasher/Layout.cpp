#include "Layout.hpp"

void Layout::addToWorld(b2World &world)
{
	int totalSize =  LAYOUT_ROWS*LAYOUT_COLUMNS;
	for(int i = 0; i< totalSize; i++)
		bricksArray[i]->addToWorld(world);
}

void Layout::drawObject()
{
	int totalSize =  LAYOUT_ROWS*LAYOUT_COLUMNS;
	for(int i = 0; i< totalSize; i++)
			bricksArray[i]->drawObject();
}

void Layout::parseLayoutFile(const char* filename)
{
	bricksArray = new Brick*[LAYOUT_ROWS*LAYOUT_COLUMNS];
	char note[2] = "X";
	b2Vec2 pos(FIRST_BRICK_X, FIRST_BRICK_Y);

	// open the file
  assert(filename != NULL);
  const char *ext = &filename[strlen(filename)-4];
  assert(!strcmp(ext,".txt"));
  file = fopen(filename,"r");
  assert (file != NULL);

	//read file
	for(int j = 0; j < LAYOUT_COLUMNS; j++)
		for(int i = 0; i < LAYOUT_ROWS; i++)
		{
			//set new position value
			pos = b2Vec2(FIRST_BRICK_X + HORIZONTAL_GAP*i, FIRST_BRICK_Y + VERTICAL_GAP*j);
			
			//get note value
			getToken(note);
			bricksArray[j*LAYOUT_ROWS + i] = new Brick(pos, note); 
			if(!strcmp(note,"X")) 
			{
				//decrease total nuber of bricks
				--activeBricks;
				bricksArray[j*LAYOUT_ROWS + i]->setState(DEACTIVE);
			}	
		}
}

int Layout::getToken(char token[2]) {
  // for simplicity, tokens must be separated by whitespace
  assert (file != NULL);
  int success = fscanf_s(file,"%s ",token);
  if (success == EOF) {
    token[0] = '\0';
    return 0;
  }
  return 1;
}

void Layout::updateObject(){
	int totalSize =  LAYOUT_ROWS*LAYOUT_COLUMNS;
	for(int i = 0; i< totalSize; i++)
	{
		if(bricksArray[i]->getState() == DESTROYED)
			--activeBricks;
		bricksArray[i]->updateObject();
	}
		
}
