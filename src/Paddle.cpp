#include "Paddle.h"



void Paddle::moveLeft()
{
	position[0]= position[0]- DELTA_X;
	
	if(position[0]<= length/2)
	{
		position[0]= length/2;
	}
}

void Paddle::moveRight()
{
	position[0]= position[0]+ DELTA_X;

	
	if(position[0]>= 30.0- length/2)
	{
		position[0]= 30.0- length/2;
	}
}

void Paddle::draw()
{
	glColor3f(1.0, 1.0, 0.0);
	glPushMatrix();
	glBegin(GL_QUADS);
		glVertex2f(position[0]- length/2, position[1]- width/2);
		glVertex2f(position[0]+ length/2, position[1]- width/2);
		glVertex2f(position[0]+ length/2, position[1]+ width/2);
		glVertex2f(position[0]- length/2, position[1]+ width/2);
	glEnd();
	glPopMatrix();
}

void Paddle::enlarge()
{
	if(status==SIMPLE)
	{
		length *=1.5;
		status= ENLARGED;
	}

	if(status==SHORT)
	{
		length *=1.5;
		status= SIMPLE;
	}
}

void Paddle::shorten()
{
	if(status==SIMPLE)
	{
		length *= (1/(1.5));
		status= SHORT;
	}


	if(status== ENLARGED)
	{
		length *= (1/(1.5));
		status= SIMPLE;
	}
}

void Paddle::makeShooter()
{
	//change the appearance of the paddle
	shoot= 1;
}

void Paddle::setPosition()
{
		length= 4.0;
		width= 0.4;
		position[0]= 15.0;
		position[1]= -10.0+ width/2;
		status= SIMPLE;
		shoot= 0;
}

void Paddle::makeNonShooter()
{
	shoot= 0;
}
/*
void Paddle::shootTheBullets(BulletList& bulletList)
{
	Bullets* bullet= new Bullets(position[0]- length/2, position[1]+ width/2, position[0]+ length/2, position[1]+ width/2);

	bulletList.addElement(bullet);
}*/