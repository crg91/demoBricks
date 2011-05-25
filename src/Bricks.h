#ifndef BRICKS_H
#define BRICKS_H
#include<iostream>
using namespace std;
#include<GL/glut.h>

#define rowBricks 20
#define columnBricks 20


class Bricks
{
public:
	float xMin;
	float yMin;
	float xMax;
	float yMax;
	float widthOfBrick;
	float heightOfBrick;
	int noOfBricks;
//public:
	enum
	{
		NO_BRICK,
		SIMPLE,
		DOUBLE_HIT
	};

	int arrayOfBricks[rowBricks][columnBricks]; //pulic so that values can be modified later
	int arrayOfPowers[rowBricks][columnBricks];
	Bricks(float xMinValue, float yMinValue, float xMaxValue, float yMaxValue)
	{
		for(int i=0; i<rowBricks; i++)
		{
			for(int j=0; j<columnBricks; j++)
			{
				arrayOfBricks[i][j]= NO_BRICK;
				arrayOfPowers[i][j]= 0;
			}
		}

		xMin= xMinValue;
		yMin= yMinValue;
		xMax= xMaxValue;
		yMax= yMaxValue;
		widthOfBrick= (xMax- xMin)/rowBricks;
		heightOfBrick= (yMax- yMin)/columnBricks;
	}
	void drawBricks();
	//void checkCollision(Ball&);
	void drawBrick(int, int);
	//friend Ball::checkCollision(Brick&);
	float modifiedX(float);
	float modifiedY(float);
	float realX(float);
	float realY(float);
	void setNumber();
	bool ifEmpty();
};
#endif