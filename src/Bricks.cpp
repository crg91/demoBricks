#include "Bricks.h"

void Bricks::drawBrick(int i, int j)
{
	float xPos= xMin+ (i+ 0.5)*widthOfBrick;
	float yPos= yMin+ (j+ 0.5)*heightOfBrick;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(arrayOfBricks[i][j]==SIMPLE)
		glColor3f(0.0, 1.0, 0.0);
	else if(arrayOfBricks[i][j]==DOUBLE_HIT)
		glColor3f(0.0, 0.0, 1.0);

	
	glPushMatrix();
	glTranslatef(xPos, yPos, 0.0);
	/*glBegin(GL_QUADS);
			glVertex2f(xPos- widthOfBrick/2, yPos- heightOfBrick/2);
			glVertex2f(xPos+ widthOfBrick/2, yPos- heightOfBrick/2);
			glVertex2f(xPos+ widthOfBrick/2, yPos+ heightOfBrick/2);
			glVertex2f(xPos- widthOfBrick/2, yPos+ heightOfBrick/2);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUADS);
			glVertex2f(xPos- widthOfBrick/2, yPos- heightOfBrick/2);
			glVertex2f(xPos+ widthOfBrick/2, yPos- heightOfBrick/2);
			glVertex2f(xPos+ widthOfBrick/2, yPos+ heightOfBrick/2);
			glVertex2f(xPos- widthOfBrick/2, yPos+ heightOfBrick/2);
		glEnd();*/
	glCallList(1);
	glPopMatrix();
}


void Bricks::drawBricks()
{
	for(int i=0; i< rowBricks; i++)
	{
		for(int j=0; j<columnBricks; j++)
		{
			int result= arrayOfBricks[i][j];
			if(result!=NO_BRICK)
			{
				//if(result==SIMPLE)
				//{
					drawBrick(i, j);
			//	}

			//	else if(result==DOUBLE_HIT)
			//	{
			//		drawDoubleHitBrick(i, j);
			//	}
			}
		}
	}
}

float Bricks::modifiedX(float xVal)
{
	return (xVal- xMin)*rowBricks/(xMax- xMin);
}

float Bricks::modifiedY(float yVal)
{
	return (yVal- yMin)*columnBricks/(yMax- yMin);
}

float Bricks::realX(float xVal)
{
	return (xVal*(xMax- xMin)/(rowBricks)+ xMin);
}

float Bricks::realY(float yVal)
{
	return (yVal*(yMax- yMin)/(columnBricks)+ yMin);
}

void Bricks::setNumber()
{	noOfBricks=0;
	for(int i=0;i<columnBricks;i++)
	{
		for(int j=0;j<rowBricks;j++)
		{
			noOfBricks+=arrayOfBricks[j][i];
		}
	}
}
bool Bricks::ifEmpty()
{
	if(noOfBricks==0)
		return true;
	else
		return false;
}