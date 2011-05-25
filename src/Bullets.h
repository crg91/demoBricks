#ifndef BULLETS_H
#define BULLETS_H
#include "Bricks.h"
enum bulletType{BOTH, RIGHT, LEFT, NONE};
class Bullets
{
public:
	Bullets(float xPos1, float yPos1, float xPos2, float yPos2)
	{
		position1[0]= xPos1;
		position1[1]= yPos1;
		position2[0]= xPos2;
		position2[1]= yPos2;
		type= BOTH;
	}

	void drawBullets();
	void checkCollision(Bricks&);
	bool move(Bricks&); //return value 1 indicates the object can be destroyed
	void setPosition(float, float, float, float);
//private:
	float position1[2];
	float position2[2];
	bulletType type;
};
#endif