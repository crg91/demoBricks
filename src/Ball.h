#ifndef BALL_H
#define BALL_H
#include<iostream>
using namespace std;
#include<GL/glut.h>
#include "Bricks.h"
#include "Paddle.h"
#include<ctime>

enum Status{START, CONTINUE, OVER, PAUSED};
class Ball
{
//private:
public:
	float radius;
	float velocity[2];
	float position[2];
	int  storeTime;
	Status gameStatus;
	bool isGlue;
	bool isStatic;
	int lives;
	bool ifFast;
	bool ifSlow;
//public:

	Ball(Paddle& paddle)
	{
		radius= 0.25;
		position[0]= paddle.position[0];
		position[1]= paddle.position[1]+ paddle.width/2+ radius;
		gameStatus= START;
		isGlue= 0;
		isStatic= 0; //when it is glued with paddle it will be one
		lives= 0;
		ifFast= 0;
		ifSlow= 0;
	}
	Ball(float xPosition, float yPosition, float xVelocity, float yVelocity)
	{
		radius= 0.25;
		position[0]= xPosition;
		position[1]= yPosition;
		velocity[0]= xVelocity;
		velocity[1]= yVelocity;
		storeTime= clock();
		gameStatus= START;
		lives= 3;
		ifFast= 0;
		ifSlow= 0;
		isGlue= 0;
		isStatic= 0;
	}

	void draw();
	void move();
	//bool collisionPaddle(Paddle&);
	bool checkCollision(Bricks&);
	bool checkCollisionWithPaddle(Paddle&);
	int giveStatus();
	void startTheGame();
	void makeDynamic();
	void moveLeft(Bricks&, Paddle&);
	void moveRight(Bricks&, Paddle&);
	void resetPosition(Paddle&);
	//void speedUp();
	//void slowDown();
};
#endif