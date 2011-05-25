#include "Ball.h"
float width1= 30.0;
float height1= 10.0;
float brickWidth1= 3.0;
float brickHeight1= 1.0;
#define PI 3.14159265358979323846
//Status gameStatus=CONTINUE;
#include<cmath>

//for sound

#include <irrKlang.h>
#pragma comment(lib,"irrKlang.lib")

#if defined(WIN32)
#include<conio.h>
#else
#include "../common/conio.h"
#endif
using namespace irrklang;
ISoundEngine* engine = createIrrKlangDevice();
//sound over


void Ball::draw()
{
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(position[0], position[1], 0.0);
	//glutSolidSphere(radius, 20, 20);
	glCallList(2);
	glPopMatrix();
}

void Ball::move()
{
	//if(clock()- 20>= storeTime)
	//{
	if(!isStatic)
	{
		position[0]= position[0]+ velocity[0];
		position[1]= position[1]+ velocity[1];

		if(position[0]> width1- radius) //i.e. it collides with right wall
		{
			engine->play2D("media/wall.wav");
			position[0]= width1- radius;
			velocity[0]= -velocity[0];
		}

		if(position[0]<= radius) //i.e. it collides with left brick
		{
			engine->play2D("media/wall.wav");
			position[0]= radius;
			velocity[0]= -velocity[0];
		}

		if(position[1]>= height1- radius)
		{
			engine->play2D("media/wall.wav");
			position[1]= height1- radius;
			velocity[1]= -velocity[1];
		}
		/*if(position[1]<= -height1+ radius)
		{
			position[1]= -height1+ radius;
			velocity[1]= -velocity[1];
		}*/
	}
		//storeTime= clock();
		//glutPostRedisplay();
	//}
}

bool Ball::checkCollision(Bricks &bricks)
{

	if(position[1]< bricks.yMin- radius)// case when it is below bricks rectangle
		return false;

int xBlast,yBlast, xyBlast; //to be reset to 0 just after collision

float xModified= bricks.modifiedX(position[0]);
float yModified= bricks.modifiedY(position[1]);

int xBrickX, xBrickY, yBrickX, yBrickY, xyBrickX, xyBrickY;

int T,R; // array in txt file, top right

	xBlast= yBlast= xyBlast= -1;

	if(velocity[1]>0)
		T= 1;
	else
		T= -1;
	if(velocity[0]>0)
		R= 1;
	else
		R= -1;

	//R= -1;
	//T= 1;


	xBrickX= (int)(xModified) +R; //it will give x value from 0 to 10
	xBrickY= (int)(yModified); //y value is already between 0 to 10x

	yBrickX= (int)(xModified);
	yBrickY= (int)(yModified)+ T;

	xyBrickX= (int)(xModified)+ R;
	xyBrickY= (int)(yModified)+ T;

	/*cout<<"xBrickX= "<<xBrickX<<endl;
	cout<<"xBrickY= "<<xBrickY<<endl;
	cout<<"yBrickX= "<<yBrickX<<endl;
	cout<<"yBrickY= "<<yBrickY<<endl;
	cout<<"xyBrickX= "<<xyBrickX<<endl;
	cout<<"xyBrickY= "<<xyBrickY<<endl;*/

	//check for xBrick
	if(xBrickX>= rowBricks || xBrickX< 0)
	{
		xBlast= 0;
		xyBlast= 0;
	}
	//check for yBrick
	if(yBrickY>= columnBricks || yBrickY< 0)
	{
		//cout<<"why\n";
		yBlast= 0;
		xyBlast= 0;
	}
	//no need to check for xyBrick

	if(position[1]<= bricks.yMin)//doubtfull
	{
		xBlast= 0;
		yBrickY= 0;
		xyBrickY= 0;
	}

	int p= 1;


	if(xBlast!=0)
	{
		
		if(bricks.arrayOfBricks[xBrickX][xBrickY]!=0)
		{
			//cout<<"sahi1\n";
			p= 0;
		}
	}

	if(yBlast!=0)
	{
		//cout<<"sahi\n";
		if(bricks.arrayOfBricks[yBrickX][yBrickY]!=0)
		{
			//cout<<"sahi\n";
			p= 0;
		}
	}

	if(xyBlast!= 0)
	{
		//cout<<xyBrickX<<"   "<<xyBrickY<<endl;
		//cout<<"array value"<<bricks.arrayOfBricks[xyBrickX][xyBrickY]<<endl;
		//cout<<"true\n";
		if(bricks.arrayOfBricks[xyBrickX][xyBrickY]!=0)
		{
			//cout<<"it must\n";
			p= 0;
		}
	}

	if(p==1)
	{
		//cout<<"false\n";
		return false;
	}

	//cout<<yBlast<<endl;



	if(xBlast!= 0) //to make sure that excluded indices do not come again
	{
		if(bricks.arrayOfBricks[xBrickX][xBrickY]!=0)
		{
			//cout<<"cool\n";
			if((position[0]+ radius*R)*R>= (bricks.realX(xBrickX+ 0.5- R*0.5))*R)
			{
				//cout<<"cool\n";
				xBlast= 1;
			}
		}
	}

	if(yBlast!= 0) //to make sure that excluded indices do not come again
	{
		if(bricks.arrayOfBricks[yBrickX][yBrickY]!=0)
		{
			//cout<<"right\n";
			if((position[1]+ radius*T)*T>= (bricks.realY(yBrickY+ 0.5- T*0.5))*T)
			{
			//	cout<<"yeah\n";
				yBlast= 1;
			}
		}
	}

	if(xBlast==1&& yBlast==1)
	{
		engine->play2D("media/ding.ogg");
		bricks.arrayOfBricks[xBrickX][xBrickY]= 0;
		bricks.arrayOfBricks[yBrickX][yBrickY]= 0;
		bricks.noOfBricks-=2;


		velocity[0]*= -1;
		velocity[1]*= -1;

		xBlast= 0;
		yBlast= 0;
		//cout<<"is it\n";
		return true;
	}
	//cout<<"?"<<endl;
	if(xBlast!= 1 || yBlast!= 1)
	{
		//cout<<"bas\n";
		if(xyBlast!= 0)
		{
			if(bricks.arrayOfBricks[xyBrickX][xyBrickY]!= 0)
			{
			
				if(xBlast!= 1 && yBlast!= 1)
				{
		
					if((position[0]+ radius*R)*R>= (bricks.realX(xBrickX+ 0.5- R*0.5))*R && (position[1]+ radius*T)*T>= (bricks.realY(yBrickY+ 0.5- T*0.5))*T)
					{
						xyBlast=1;
						engine->play2D("media/ding.ogg");
						bricks.arrayOfBricks[xyBrickX][xyBrickY]--;
						bricks.noOfBricks--;
						velocity[0] *= -1;
						velocity[1] *= -1;
						position[0] = bricks.realX(xyBrickX+ 0.5- 0.5*R)- R*radius;
						position[1] = bricks.realY(xyBrickY+ 0.5- 0.5*T)- T*radius;
						xyBlast= 0;
						return true;
					}
				}

					if(xBlast==1)
					{
						if((position[1]+ radius*T)*T>= (bricks.realY(yBrickY+ 0.5- T*0.5))*T)
						{
							engine->play2D("media/ding.ogg");
							bricks.arrayOfBricks[xBrickX][xBrickY]--;
							bricks.arrayOfBricks[xyBrickX][xyBrickY]--;
							bricks.noOfBricks-=2;

							velocity[0]*= -1;
							position[0] =bricks.realX(xyBrickX+ 0.5- 0.5*R)- R*radius;
							xBlast= 0;
							xyBlast= 0;
							return true;
						}
					}

					if(yBlast==1)
					{
						if((position[0]+ radius*R)*R>= (bricks.realX(xBrickX+ 0.5- R*0.5))*R)
						{
							engine->play2D("media/ding.ogg");
							//bricks.arrayOfBricks[yBrickX][yBrickY]= 0;
							//bricks.arrayOfBricks[xyBrickX][xyBrickY]= 0;
							bricks.arrayOfBricks[yBrickX][yBrickY]--;
							bricks.arrayOfBricks[xyBrickX][xyBrickY]--;
							bricks.noOfBricks-=2;

							velocity[1]*= -1;
							position[1] =bricks.realY(xyBrickY+ 0.5- 0.5*T)- T*radius;
							yBlast= 0;
							xyBlast= 0;
							//cout<<"Done\n";
							return true;
						}
					}
				
			}
		}
	}

	if(xBlast==1)
	{
		position[0] =bricks.realX(xyBrickX+ 0.5- 0.5*R)- R*radius;
		velocity[0]*= -1;
		xBlast= 0;
		engine->play2D("media/ding.ogg");
		//bricks.arrayOfBricks[xBrickX][xBrickY]=0;
		bricks.arrayOfBricks[xBrickX][xBrickY]--;
		bricks.noOfBricks--;
		return true;
	}

	if(yBlast==1)
	{
		//cout<<"how\n";
		position[1]= bricks.realY(xyBrickY+ 0.5- 0.5*T)- T*radius;
		velocity[1]*= -1;
		yBlast= 0;
		engine->play2D("media/ding.ogg");
		//bricks.arrayOfBricks[yBrickX][yBrickY]= 0;
		bricks.arrayOfBricks[yBrickX][yBrickY]--;
		bricks.noOfBricks--;
		return true;
	}
}

bool Ball::checkCollisionWithPaddle(Paddle &paddle)
{
	if(gameStatus== START) //the begining
	{
		position[0]= paddle.position[0];
		position[1]= paddle.position[1]+ paddle.width/2+ radius;
	}


	else if(gameStatus== CONTINUE && position[1]- radius<= paddle.position[1]+ paddle.width/2)
	{
		if(position[0]+ radius>= paddle.position[0]- paddle.length/2 && position[0]- radius<= paddle.position[0]+ paddle.length/2 && position[1]+ radius>= paddle.position[1]- paddle.width/2)
		{
			if(!isStatic)
			{
			if(isGlue)
			{
				isStatic= 1;
			}
			engine->play2D("media/paddle.wav");
			float speed= sqrt(velocity[0]*velocity[0]+ velocity[1]*velocity[1]);
			velocity[0]= speed*cos((160*(paddle.position[0]- position[0])/(paddle.length+ 2*radius)+ 90)*2*PI/360);
			velocity[1]= speed*sin((160*(paddle.position[0]- position[0])/(paddle.length+ 2*radius)+ 90)*2*PI/360);
			position[1]= paddle.position[1]+ paddle.width/2+ radius;
			return true;
			}
		}
		else if(position[1]+ radius< paddle.position[1]- paddle.width/2-1)
		{
			lives--;
			if(lives>=0)
			{	
				engine->play2D("media/marioDies.wav");
				resetPosition(paddle);
			}
			else
			{
				engine->play2D("media/gameOver.ogg");
				gameStatus= OVER;
			}
			return true;
		}
	}
}

int Ball::giveStatus()
{
	return gameStatus;
}

void Ball::startTheGame()
{
	if(gameStatus== START)
	{
		gameStatus=CONTINUE;
		velocity[0]= 0.01;
		velocity[1]= 0.15;
		move();
	}
}

void Ball::makeDynamic()
{
	isStatic= 0;
}

void Ball::moveLeft(Bricks& bricks, Paddle& paddle)
{
	if(isStatic && paddle.position[0]> bricks.xMin+ paddle.length/2)
	{
		position[0] -= DELTA_X;
	}
}

void Ball::moveRight(Bricks& bricks, Paddle& paddle)
{
	if(isStatic && paddle.position[0]< bricks.xMax- paddle.length/2)
	{
		position[0] += DELTA_X;
	}
}

void Ball::resetPosition(Paddle& paddle)
{
	gameStatus= START;
	paddle.setPosition();
	position[0]= paddle.position[0];
	position[1]= paddle.position[1]+ paddle.width/2+ radius;
	ifFast= 0;
	ifSlow= 0;
	isGlue= 0;
	isStatic= 0;
}
