#include "Power.h"
#include <irrKlang.h>
#pragma comment(lib,"irrKlang.lib")
using namespace irrklang;
#if defined(WIN32)
#include<conio.h>
#else
#include "../common/conio.h"
#endif
ISoundEngine* engine1 = createIrrKlangDevice();


void Power::draw()
{
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(position[0], position[1], 0.0);
	//glutSolidCube(1.0);
	switch(type)
	{
	case 0:
		glCallList(15);
		break;
	case 1:
		glCallList(16);
		break;
	case 2:
		glCallList(13);
		break;
	case 3:
		glCallList(11);
		break;
	case 4:
		glCallList(14);
		break;
	case 5:
		glCallList(12);
		break;
	case 6:
		glCallList(17);
		break;
	}
	
	glPopMatrix();
}

void Power::moveDown()
{
	position[1] -= DELTA_Y;
}

bool Power::collisionWithPaddle(Paddle& paddle, Ball &ball, Bricks &bricks)
{
	if(ball.gameStatus== CONTINUE)
	{	
		if(position[1]- width/2<= paddle.position[1]+ paddle.width/2)
		{
			if(position[0]+ length/2>= paddle.position[0]- paddle.length/2 && position[0]- length/2<= paddle.position[0]+ paddle.length/2)
			{
				if(type== EXPAND)
				{
					
					engine1->play2D("media/powerGood.wav");
					paddle.enlarge();
					return true;
				}

				else if(type== SHORTEN)
				{engine1->play2D("media/powerBad.wav");
					paddle.shorten();
					return true;
				}

				else if(type== GLUE)
				{engine1->play2D("media/powerGood.wav");
					ball.isGlue= 1;
					return true;
				}

				else if(type== SHOOT)
				{engine1->play2D("media/powerGood.wav");
					paddle.shoot= 1;
					return true;
				}

				else if(type== UNGLUE)
				{engine1->play2D("media/powerBad.wav");
					ball.isGlue= 0;
					return true;
				}

				else if(type== NOSHOOT)
				{engine1->play2D("media/powerBad.wav");
					paddle.shoot= 0;
					return true;
				}

				else if(type== ONEUP)
				{engine1->play2D("media/powerGood.wav");
					ball.lives++;
					return true;
				}
			}
		}
	}
	return false;
}