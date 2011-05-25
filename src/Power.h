#ifndef POWER_H
#define POWER_H
#include "Paddle.h"
#include "Ball.h"
//#include<GL/glut.h>
#define DELTA_Y 0.10
enum powerType{EXPAND, SHORTEN, GLUE, SHOOT, UNGLUE, NOSHOOT, ONEUP};
class Power
{
public:
	float position[2];
	float length;
	float width;
	powerType type;
//public:
	Power(float xPos, float yPos, powerType typeOfPower)
	{
		position[0]= xPos;
		position[1]= yPos;
		length= 1.0;
		width= 1.0;
		type= typeOfPower;
	}

	void draw();
	void moveDown();
	bool collisionWithPaddle(Paddle&, Ball&, Bricks&);
};
#endif