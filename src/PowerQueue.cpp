#include "PowerQueue.h"

void PowerQueue::addPower(float xPos, float yPos, powerType type)
{
	if(tail== NULL) //no power yet
	{
		tail= new queueNode;
		tail->next= NULL;
		tail->prev= NULL;
		tail->power= new Power(xPos, yPos, type);
		head= tail;
	}

	else //when tail!= NULL
	{
		queueNode* ptr= new queueNode();
		ptr->power= new Power(xPos, yPos, type);
		ptr->next= tail;
		ptr->prev= NULL;
		tail->prev= ptr;
		tail= ptr;
	}

	elements++;
	//cout<<"elements= "<<elements<<endl;
}

void PowerQueue::deletePower(Paddle& paddle, Ball& ball, Bricks& bricks)
{
	queueNode* ptr= head;
	if(head!= NULL)
	{
	if(head->power->position[1]- head->power->length/2<= -10.0)
	{
		
		head= head->prev;
		if(head!= NULL)
		{
			head->next= NULL;
		}
		if(head==NULL)
		{
			tail= NULL;
		}
		delete ptr;
		elements--;
		//cout<<"elements= "<<elements<<endl;
	}
	}

}

void PowerQueue::drawPowers()
{
	queueNode* ptr= tail;

	for(;ptr!= NULL;)
	{
		if(ptr->ifActive)
		{
			ptr->power->draw();
		}

		if(ptr->next!= NULL)
		{
			ptr= ptr->next;
		}

		else
		{
			break;
		}
	}
}

void PowerQueue::checkCollision(Paddle& paddle, Ball& ball, Bricks& bricks)
{
	queueNode* ptr= tail;

	for(;ptr!= NULL;)
	{
		if(ptr->ifActive)
		{
			if(ptr->power->collisionWithPaddle(paddle, ball, bricks))
			{
				ptr->ifActive= 0;
			}
		}
			
		if(ptr->next!= NULL)
		{
			ptr= ptr->next;
		}

		else
		{
			break;
		}
	}
}

void PowerQueue::movePower()
{
	queueNode* ptr= tail;

	for(;ptr!= NULL;)
	{
		ptr->power->moveDown();

		if(ptr->next!= NULL)
		{
			ptr= ptr->next;
		}
		else
		{
			break;
		}
	}
}

bool PowerQueue::addPowerFromBricks(Bricks& bricks)
{
	for(int i=0; i< rowBricks; i++)
	{
		for(int j=0; j<columnBricks; j++)
		{
			if(bricks.arrayOfBricks[i][j]==0 && bricks.arrayOfPowers[i][j]!=0)
			{
				int a= bricks.arrayOfPowers[i][j];
				switch(a)
				{
				case 1:
					addPower(bricks.realX(i+ 0.5), bricks.realY(j+ 0.5), EXPAND);
					break;
				case 2:
					addPower(bricks.realX(i+ 0.5), bricks.realY(j+ 0.5), SHORTEN);
					break;
				case 3:
					addPower(bricks.realX(i+ 0.5), bricks.realY(j+ 0.5), GLUE);
					break;
				case 4:
					addPower(bricks.realX(i+ 0.5), bricks.realY(j+ 0.5), SHOOT);
					break;
				case 5:
					addPower(bricks.realX(i+ 0.5), bricks.realY(j+ 0.5), UNGLUE);
					break;
				case 6:
					addPower(bricks.realX(i+ 0.5), bricks.realY(j+ 0.5), NOSHOOT);
					break;
				case 7:
					addPower(bricks.realX(i+ 0.5), bricks.realY(j+ 0.5), ONEUP);
				default:
					break;
				}
				bricks.arrayOfPowers[i][j]= 0;
				return true;
			}
		}
	}

	return false;
}