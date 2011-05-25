#ifndef BULLETLIST_H
#define BULLETLIST_H
#include "Bullets.h"
#include "Paddle.h"

class node
{
public:
	node()
	{
		next= NULL;
		bullet= NULL;
	}
	node* next;
	node* prev;
	Bullets* bullet;
};

class BulletList
{
private:
	node* head1;
	node* head2;
	node* tail;
	int activeElements;
	int nonActiveElements;
public:
	BulletList()
	{
		head1= NULL;
		head2= NULL;
		tail= NULL;
		activeElements= 0;
		nonActiveElements= 0;
	}

	void addNonActiveElement();
	//void addActiveElement(Bullets*);
	void makeActive(Paddle&);
	void checkForCollision(Bricks&);
	void moveBullets(Bricks&);
	void drawBullets();
	void makeNonActive(Bricks&);
	void resetEverything();
};
#endif