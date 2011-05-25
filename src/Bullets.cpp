#include "Bullets.h"

void Bullets::checkCollision(Bricks& bricks)
{
	if(position1[1]>= bricks.yMin)
	{
	float xModified1= bricks.modifiedX(position1[0]);
	float xModified2= bricks.modifiedX(position2[0]);
	float yModified1= bricks.modifiedY(position1[1]);
	float yModified2= bricks.modifiedY(position2[1]);

	int xint1= (int)(xModified1);
	int xint2= (int)(xModified2);
	int yint1= (int)(yModified1);
	int yint2= (int)(yModified2);

	if(type== BOTH && xint1== xint2 && yint1== yint2 && bricks.arrayOfBricks[xint1][yint1]==1)
	{
		type= NONE;
		bricks.arrayOfBricks[xint1][yint1]= 0;
		bricks.noOfBricks--;
	}

	if((type== BOTH || type== LEFT) && bricks.arrayOfBricks[xint1][yint1]==1)
	{
		bricks.arrayOfBricks[xint1][yint1]= 0;
		bricks.noOfBricks--;

		if(type== BOTH)
		{
			type= RIGHT;
		}

		else if(type== LEFT)
		{
			type= NONE;
		}
	}

	if((type== BOTH || type== RIGHT )&& bricks.arrayOfBricks[xint2][yint2]==1)
	{
		bricks.arrayOfBricks[xint2][yint2]= 0;
		bricks.noOfBricks--;

		if(type== BOTH)
		{
			type= LEFT;
		}

		else if(type== RIGHT)
		{
			type= NONE;
		}
	}
	}
}

void Bullets::drawBullets()
{
	//cout<<position1[0]<<"  "<<position1[1]<<endl;
	glPushMatrix();
	glPointSize(4);
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POINTS);
		if(type== BOTH || type==LEFT)
			glVertex3f(position1[0], position1[1], 0.0);
		if(type== BOTH || type==RIGHT)
			glVertex3f(position2[0], position2[1], 0.0);
	glEnd();
	glPopMatrix();
}

bool Bullets::move(Bricks& bricks)
{
	position1[1] += 0.2;
	position2[1] += 0.2;

	if(position1[1]>= bricks.yMax)
		return 1;
	else
		return 0;
}

void Bullets::setPosition(float xPos1, float yPos1, float xPos2, float yPos2)
{
	position1[0]= xPos1;
	position1[1]= yPos1;
	position2[0]= xPos2;
	position2[1]= yPos2;
}