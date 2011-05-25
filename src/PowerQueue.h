#ifndef POWERQUEUE_H
#define POWERQUEUE_H
#include "Power.h"

class queueNode
{
public:
	queueNode* next;
	queueNode* prev;
	Power* power;
	bool ifActive;
	queueNode()
	{
		next= NULL;
		prev= NULL;
		power= NULL;
		ifActive= 1;
	}
};

class PowerQueue
{
private:
	queueNode* head;
	queueNode* tail;
	int elements;
public:
	PowerQueue()
	{
		head= NULL;
		tail= NULL;
		elements= 0;
	}

	void addPower(float, float, powerType);
	void deletePower(Paddle&, Ball&, Bricks&);
	void drawPowers();
	void checkCollision(Paddle&, Ball&, Bricks&);
	void movePower();
	bool addPowerFromBricks(Bricks&);
};
#endif