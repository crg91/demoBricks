#include "bulletList.h"

void BulletList::addNonActiveElement()
{
	if(head2== NULL)
	{
		head2= new node;
		head2->bullet= new Bullets(0.0, 0.0, 0.0, 0.0);
		head2->next= NULL;
		head2->prev= NULL;
		tail = head2;
	}

	else
	{
		node* temp= new node;
		temp->bullet= new Bullets(0.0, 0.0, 0.0, 0.0);
		temp->next= tail;
		tail->prev= temp;
		temp->prev= NULL;
		tail= temp;
	}

	nonActiveElements++;
	//cout<<"activeElements= "<<activeElements<<endl;
	//cout<<"nonActiveElemetns= "<<nonActiveElements<<endl;
}

void BulletList::makeActive(Paddle& paddle)
{
	if(nonActiveElements> 0)
	{
	if(head1== NULL)
	{
		head1= head2;
		head1->bullet->setPosition(paddle.position[0]- paddle.length/2, paddle.position[1]+ paddle.width/2, paddle.position[0]+ paddle.length/2, paddle.position[1]+ paddle.width/2);
		head2= head2->prev;
		activeElements++;
		nonActiveElements--;
		//cout<<"activeElements= "<<activeElements<<endl;
		//cout<<"nonActiveElemetns= "<<nonActiveElements<<endl;
	}

	else if(head2!= NULL)//when there are some active elements
	{
		activeElements++;
		nonActiveElements--;
		head2->bullet->setPosition(paddle.position[0]- paddle.length/2, paddle.position[1]+ paddle.width/2, paddle.position[0]+ paddle.length/2, paddle.position[1]+ paddle.width/2);
		head2= head2->prev;
		//cout<<"activeElements= "<<activeElements<<endl;
		//cout<<"nonActiveElemetns= "<<nonActiveElements<<endl;
	}
	}
}

/*void BulletList::addElement(Bullets* bullet)
{
	node* temp= new node;
	temp->bullet= bullet;
	temp->next= NULL;

	if(head==NULL)
	{
		head= temp;
	}

	else
	{
		node* temp2= head;

		for(; temp2->next!= NULL; temp2= temp2->next)
		{
		}

		temp2->next= temp;
	}

	numberOfNodes++;
}

void BulletList::deleteElement(Bullets* bullet)
{
	if(head==NULL)
		;//no element to delete

	else if(head->next== NULL)
	{
		head= NULL;
	}
	else
	{
		node* temp= head;

		for(; temp->next->bullet!= bullet && temp->next!= NULL; temp= temp->next)
		{
		}

		if(temp->next!= NULL)
		{
			node* temp1= temp->next;
			temp->next= temp->next->next;
			delete temp1;
			numberOfNodes--;
		}
	}
}*/

void BulletList::checkForCollision(Bricks& bricks)
{
	node* temp= head1;

	for(;temp!= NULL;) 
	{
		temp->bullet->checkCollision(bricks);
		if(temp->prev== head2) //head2 is the pointer where non active bullets start
			break;
		else
			temp= temp->prev;
	}
}

void BulletList::moveBullets(Bricks& bricks)
{
	node* temp= head1;

	for(;temp!= NULL;)
	{
		temp->bullet->move(bricks);
		{
		//	node* temp2= temp;
		//	delete temp2; // delete the bullet when it leaves the screen
		//	if(temp->next== NULL)
		//		break;
		}
		if(temp->prev== head2)
			break;
		else
			temp= temp->prev;
	}
}

void BulletList::drawBullets()
{
	node* temp= head1;

	for(;temp!= NULL;)
	{
		temp->bullet->drawBullets();
		if(temp->prev== head2)
			break;
		else
			temp= temp->prev;
	}
}

void BulletList::makeNonActive(Bricks& bricks)
{
	if(head1!= NULL)
	{
	if(head1->bullet->position1[1]>= bricks.yMax) //i.e. it has reached the top
	{
		//cout<<"made\n";
		head1->bullet->type= BOTH;
		tail->prev= head1;
		tail->prev->next= tail;
		tail= head1;
		head1= head1->prev;
		if(head1== head2)
		{
			head1= NULL;
		}

		if(head2==NULL) //when all were active
		{
			head2= tail;
		}

		activeElements--;
		nonActiveElements++;
		//cout<<"activeElements= "<<activeElements<<endl;
		//cout<<"nonActiveElemetns= "<<nonActiveElements<<endl;
	}
	}
}

void BulletList::resetEverything()
{
	while(activeElements!=0)
	{
	if(head1!= NULL)
	{
		head1->bullet->type= BOTH;
		tail->prev= head1;
		tail->prev->next= tail;
		tail= head1;
		head1= head1->prev;
		if(head1== head2)
		{
			head1= NULL;
		}

		if(head2== NULL)
		{
			head2= tail;
		}
		activeElements--;
		nonActiveElements++;
	}
	}
}