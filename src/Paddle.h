#ifndef PADDLE_H
#define PADDLE_H
#include<iostream>
//#include "Ball.h"
#include<GL/glut.h>
//#include "BulletList.h"

#define DELTA_X 0.30;

enum statusPaddle{SIMPLE, ENLARGED, SHORT};

class Paddle
{
public:
	float position[2];
	float length;
	float width;
	statusPaddle status;
	bool shoot;
//public:
	Paddle()
	{
		length= 4.0;
		width= 0.4;
		position[0]= 15.0;
		position[1]= -10.0+ width/2;
		status= SIMPLE;
		shoot= 0;
	}

	void moveLeft();
	void moveRight();
	void draw();
	void enlarge();
	void shorten();
	void makeShooter();
	void setPosition();
	void makeNonShooter();
	//void shootTheBullets(BulletList&);
	//void collisionWithBall(Ball&);
};
#endif