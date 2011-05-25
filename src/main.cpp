

//for sound
#include<string>
#include <irrKlang.h>
#pragma comment(lib,"irrKlang.lib")

#if defined(WIN32)
#include<conio.h>
#else
#include "../common/conio.h"
#endif

using namespace irrklang;
ISoundEngine* engineMain= createIrrKlangDevice();
//sound ends
#include "Bricks.h"
#include "Ball.h"
#include "Paddle.h"
#include "Power.h"
#include "Bullets.h"
#include "bulletList.h"
#include "PowerQueue.h"
#include <stdio.h>
#include<cstring>
//const int vertiBricks=10,horiBricks=10;
#include "rijndael.h"
#include "gandiCoding.h"
const int dimension= 20;
#define KEYBITS 256

#define FULL_UNROLL
#include "encrypt.h"
#include "decrypt.h"
#include "numbers.h"

#define WIDTH 1200*0.8
#define HEIGHT 800*0.8
int storeTime= clock();
int storeTimeShooter= clock();
enum stats{STARTING, MENU, STARTNEW, EXITBOX, OPTIONBOX, CREDITBOX, LEVELBOX, PAUSEDBOX, GAMEOVERBOX, EXITGAMEBOX};
stats game;
int menuPointer= 0;
int optionPointer= 0;
bool exitYes= 1;
bool exitGameYes= 1;
bool continueIndication= 0;
int levelNo= 1;
int keyStatus1= 0;
int keyStatus2= 0;
int xInitial;
int yInitial;
int frame= 0;
int timebase= 0;
int time1;
bool fullScreen= 0;
bool ifPower= 1;
//bool ifLevelChange= 0;
int ballOnly= 0;
GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
/*float width= 30;
float height= 10;
const int rowBricks= 10;
const int columnBricks= 10;
float brickWidth= width/rowBricks;
float brickHeight= height/columnBricks;
int array[rowBricks][columnBricks]= {};
float xInitial= 0.0;
float yInitial= 0.0;*/
//Ball b1(0.0, -1.7, 0.2, 0.2);
int decryptedArrayInt[20][20];
//string password= "1234";
Bricks bricks(0.0, 0.0, 30.0, 10.0);
Paddle p1;
Ball b1(p1);
//Bullets bt1(21.0, -5.0, 22.0, -5.0);
//Power pp1(5.0, 5.0, SHOOT);
//Power* power;
BulletList bl1;
PowerQueue pq1;
int a= 0;
float menuWidth= 3.0;
float menuLength= 10.0;
//Bricks bricks(
 unsigned char texture[256 * 256 * 3];

 void createDisplayList();
void setUpTextures()
{
	 //This is the array that will contain the image color information.
        // 3 represents red, green and blue color info.
        // 512 is the height and width of texture.
   
        // This opens your image file.
    FILE* f = fopen("textures/newGame.raw", "r");
    fread(texture, 256 * 256 * 3, 1, f);
    fclose(f);
    glEnable(GL_TEXTURE_2D);
    //Here 1 is the texture id
        //The texture id is different for each texture (duh?)
    glBindTexture(GL_TEXTURE_2D, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //In this line you only supply the last argument which is your color info array,
        //and the dimensions of the texture (512)
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	f= fopen("textures/continue.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	f= fopen("textures/credits.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 4);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	f= fopen("textures/exit.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);


	f= fopen("textures/sureToExit.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 9);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	f= fopen("textures/arrow.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 10);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	f= fopen("textures/yes.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 11);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	f= fopen("textures/no.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 12);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	f= fopen("textures/demoBricks.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 13);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	f= fopen("textures/level.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 14);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	
	f= fopen("textures/credits1.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 16);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);


	f= fopen("textures/shoot.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 17);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	f= fopen("textures/glue.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 18);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	f= fopen("textures/expand.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 19);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);

	f= fopen("textures/1up.raw", "r");
	fread(texture, 256*256*3, 1, f);
	fclose(f);
	glBindTexture(GL_TEXTURE_2D, 20);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);


    glDisable(GL_TEXTURE_2D);
}

void init()
{
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	setUpTextures();
		createDisplayList();
	game= STARTING;
}


void initialize()
{
	b1.lives= 3;
	b1.gameStatus= START;
	b1.resetPosition(p1);
	engineMain->stopAllSounds();
	engineMain->play2D("media/back1.ogg",true);
	if(continueIndication)
	{
	float levelFloat= 0;
	decrypt("userProfile", decryptedArrayInt, "userProfile.jek");

	for(int i=0; i<20; i++)
	{
		levelFloat+= decryptedArrayInt[0][i]*(double)pow((double)2, (double)i);
	}
	levelNo= levelFloat;
	levelNo= 2; 
	}

	else
	{
			//changing userProfile
		int arrayToEncryptInt[20][20];
		levelNo= 1;
		int tempLevelNo=levelNo,count=0;
		int tempArray[20];
		while(tempLevelNo>0)
		{
			if((tempLevelNo%2)==0)
			{
				tempArray[count]=0;
				count++;
			}
			else
			{
				tempArray[count]=1;
				count++;
			}
			tempLevelNo/=2;
		}
		//int intArray[20];
		/*for(int i=0;i<count;i++)
		{
			intArray[i]=tempArray[count-1-i];
			//cout<<intArray[i]<<'\t';
		}*/
		//cout<<"stop\n";
		//cout<<"count "<<count;
		for(int i=count;i<20;i++)
		{
			tempArray[i]=0;
		}
		//int arrayToEncrypt[20][20];
		//cout<<"\nfirst row of array to encrypt int \n";
		for(int i=0;i<20;i++)
		{
			arrayToEncryptInt[0][i]=tempArray[i];
			//cout<<arrayToEncryptInt[0][i];
		}
		//cout<<"bas";
		for(int i=1;i<20;i++)
		{
			for(int j=0;j<20;j++)
			{
				arrayToEncryptInt[i][j]=0;
			}
		}
		encrypt("userProfile",arrayToEncryptInt,"userProfile.jek");
	}
	//levelNo= 1;
	string password=" ";
	//int levelNo=1;
	int decimal,unit;
	decimal=levelNo/10;
	unit=levelNo%10;
    string c="  ";
    c[0]=char(decimal+48);
	c[1]=char(unit+48);
	password=c;
    c.append(".jek");
	cout<<" c "<<c;

	// decryptedArrayInt[20][20];
	decrypt(&password[0],decryptedArrayInt,&c[0]);

	for(int i=0; i< rowBricks; i++)
	{
		for(int j=0; j<columnBricks; j++)
		{
			
			bricks.arrayOfBricks[i][j]= decryptedArrayInt[19- j][i];
			//bricks.arrayOfBricks[i][j]= 1;
			//bricks.arrayOfPowers[i][j]= 1;
		}

		//bricks.arrayOfBricks[7][1]= 1;
		//bricks.arrayOfBricks[6][2]= 1;
		//bricks.arrayOfBricks[7][2]= 1;
		//bricks.arrayOfPowers[0][0]= EXPAND;

	}

	//bricks.arrayOfPowers[8][1]= 4;
	//bricks.arrayOfBricks[10][0]=1;
	//bricks.arrayOfBricks[20][0]=1;
	//bricks.arrayOfPowers[10][0]=4;

	bricks.setNumber();
	p1.status= SIMPLE;
	//p1.shootTheBullets(bl1);

	//five non active objects are created
	bl1.addNonActiveElement();
	bl1.addNonActiveElement();
	bl1.addNonActiveElement();
	bl1.addNonActiveElement();
	bl1.addNonActiveElement();
	
	//pq1.addPower(15.0, 0.0, SHOOT);
	//pq1.addPower(20.0, 15.0, GLUE);

	if(levelNo== 1)
	{
		bricks.arrayOfPowers[6][4]= 1;
		bricks.arrayOfPowers[14][4]= 2;
		bricks.arrayOfPowers[10][8]= 3;
		bricks.arrayOfPowers[11][7]= 4;
		/*bricks.arrayOfPowers[1][1]= 4;
		bricks.arrayOfPowers[2][1]= 6;
		bricks.arrayOfPowers[3][1]= 1;
		bricks.arrayOfPowers[4][1]= 2;
		bricks.arrayOfPowers[5][1]= 3;
		bricks.arrayOfPowers[6][1]= 5;
		bricks.arrayOfPowers[7][1]= 7;*/
	}

	else if(levelNo== 2)
	{
		bricks.arrayOfPowers[2][4]= 1;
		bricks.arrayOfPowers[10][4]= 2;
		bricks.arrayOfPowers[14][4]= 7;
		bricks.arrayOfPowers[13][5]= 4;
		bricks.arrayOfPowers[15][5]= 6;
		
	}
}

void changeLevel()
{
	b1.gameStatus= START;
	game= LEVELBOX;
	b1.resetPosition(p1);
	levelNo++;
	bl1.resetEverything();

	//changing userProfile
	int arrayToEncryptInt[20][20];
	//levelNo=3;
	int tempLevelNo=levelNo,count=0;
	int tempArray[20];
	while(tempLevelNo>0)
	{
		if((tempLevelNo%2)==0)
		{
			tempArray[count]=0;
			count++;
		}
		else
		{
			tempArray[count]=1;
			count++;
		}
		tempLevelNo/=2;
	}
	
	for(int i=count;i<20;i++)
	{
		tempArray[i]=0;
	}

	for(int i=0;i<20;i++)
	{
		arrayToEncryptInt[0][i]=tempArray[i];
	}
	
	for(int i=1;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			arrayToEncryptInt[i][j]=0;
		}
	}
	encrypt("userProfile",arrayToEncryptInt,"userProfile.jek");


	string password=" ";
	int decimal,unit;
	decimal=levelNo/10;
	unit=levelNo%10;
    string c="  ";
    c[0]=char(decimal+48);
	c[1]=char(unit+48);
	password=c;
    c.append(".jek");
	cout<<" c "<<c;
	decrypt(&password[0],decryptedArrayInt,&c[0]);
	for(int i=0;i<20;i++)
		{
			for(int j=0;j<20;j++)
			{
				bricks.arrayOfBricks[i][j]= decryptedArrayInt[19-j][i];
			}
		}

	if(levelNo== 2)
	{
		bricks.arrayOfPowers[2][4]= 1;
		bricks.arrayOfPowers[10][4]= 2;
		bricks.arrayOfPowers[14][4]= 7;
		bricks.arrayOfPowers[13][5]= 4;
	}


	bricks.setNumber();
	glutPostRedisplay();

}

void drawShootPower()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 17);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(-0.5, -0.5);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(0.5, -0.5);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(0.5, 0.5);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void drawNoShootPower()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 17);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(-0.5, -0.5);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(0.5, -0.5);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(0.5, 0.5);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawGluePower()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 18);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(-0.5, -0.5);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(0.5, -0.5);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(0.5, 0.5);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


void drawUngluePower()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 18);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(-0.5, -0.5);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(0.5, -0.5);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(0.5, 0.5);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawExpandPower()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 19);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(-0.5, -0.5);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(0.5, -0.5);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(0.5, 0.5);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawShrinkPower()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 19);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(-0.5, -0.5);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(0.5, -0.5);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(0.5, 0.5);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void draw1UpPower()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 20);
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0);
		glVertex2f(-0.5, -0.5);
		glTexCoord2f(1.0, 1.0);
		glVertex2f(0.5, -0.5);
		glTexCoord2f(1.0, 0.0);
		glVertex2f(0.5, 0.5);
		glTexCoord2f(0.0, 0.0);
		glVertex2f(-0.5, 0.5);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void makeBackground()
{
	glColor3f(1.0, 0.0, 0.0);

	glBegin(GL_QUADS);
		//left wall
		glVertex2f(-1.0, -11.0);
		glVertex2f(0.0, -11.0);
		glVertex2f(0.0, 11.0);
		glVertex2f(-1.0, 11.0);
		//lower wall
		/*glVertex2f(-1.0, -11.0);
		glVertex2f(31.0, -11.0);
		glVertex2f(31.0, -10.0);
		glVertex2f(-1.0, -10.0);*/
		//right wall
		glVertex2f(30.0, -11.0);
		glVertex2f(31.0, -11.0);
		glVertex2f(31.0, 11.0);
		glVertex2f(30.0, 11.0);
		//top wall
		glVertex2f(31.0, 10.0);
		glVertex2f(31.0, 11.0);
		glVertex2f(-1.0, 11.0);
		glVertex2f(-1.0, 10.0);
	glEnd();
}

void displayStarting()
{
	glColor3f(1.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 13);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(-1.0, -11.0);
		glTexCoord2d(1, 1);
		glVertex2f(31.0, -11.0);
		glTexCoord2d(1, 0);
		glVertex2f(31.0, 11.0);
		glTexCoord2d(0, 0);
		glVertex2f(-1.0, 11.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void displayMenu()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 1);
	glColor3f(1.0, 1.0, 0.0);

	//start new game
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);glVertex2f(15.0- menuLength/2, 5.5- menuWidth/2);
		glTexCoord2d(1, 1);glVertex2f(15.0+ menuLength/2, 5.5- menuWidth/2);
		glTexCoord2d(1, 0);glVertex2f(15.0+ menuLength/2, 5.5+ menuWidth/2);
		glTexCoord2d(0, 0);glVertex2f(15.0- menuLength/2, 5.5+ menuWidth/2);
	glEnd();
	//exit
	glBindTexture(GL_TEXTURE_2D, 3);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(15.0- menuLength/2, -6.5- menuWidth/2);
		glTexCoord2d(1, 1);
		glVertex2f(15.0+ menuLength/2, -6.5- menuWidth/2);
		glTexCoord2d(1, 0);
		glVertex2f(15.0+ menuLength/2, -6.5+ menuWidth/2);
		glTexCoord2d(0, 0);
		glVertex2f(15.0- menuLength/2, -6.5+ menuWidth/2);
	glEnd();
	//credits
	glBindTexture(GL_TEXTURE_2D, 4);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(15.0- menuLength/2, -2.5- menuWidth/2);
		glTexCoord2d(1, 1);
		glVertex2f(15.0+ menuLength/2, -2.5- menuWidth/2);
		glTexCoord2d(1, 0);
		glVertex2f(15.0+ menuLength/2, -2.5+ menuWidth/2);
		glTexCoord2d(0, 0);
		glVertex2f(15.0- menuLength/2, -2.5+ menuWidth/2);
	glEnd();
	//continue
	glBindTexture(GL_TEXTURE_2D, 2);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);glVertex2f(15.0- menuLength/2, 1.5- menuWidth/2);
		glTexCoord2d(1, 1);glVertex2f(15.0+ menuLength/2, 1.5- menuWidth/2);
		glTexCoord2d(1, 0);glVertex2f(15.0+ menuLength/2, 1.5+ menuWidth/2);
		glTexCoord2d(0, 0);glVertex2f(15.0- menuLength/2, 1.5+ menuWidth/2);
	glEnd();

	

	//menupointer dimenstion of 3x3
	

	glDisable(GL_TEXTURE_2D);
}


void displayMenuPointer()
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 10);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(6.0, 5.5- menuWidth/2- (float)menuPointer*(menuWidth+ 1));
		glTexCoord2d(1, 1);
		glVertex2f(9.0, 5.5- menuWidth/2- (float)menuPointer*(menuWidth+ 1));
		glTexCoord2d(1, 0);
		glVertex2f(9.0, 5.5+ menuWidth/2- (float)menuPointer*(menuWidth+ 1));
		glTexCoord2d(0, 0);
		glVertex2f(6.0, 5.5+ menuWidth/2- (float)menuPointer*(menuWidth+ 1));
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void livesBoard()
{
	int var= b1.lives;
	float xVal= 20.0;
	float yVal= 10.5;

	while(var>0)
	{
		glColor3f(0.0, 0.0, 1.0);
		glPushMatrix();
		glTranslatef(xVal, yVal, 0.0);
		glCallList(2);
		glPopMatrix();
		xVal+=1.0;
		var--;
	}
}

void drawExitBox()
{
	//are you sure to exit?
	glColor3f(1.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 9);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(5.0, 2.0);
		glTexCoord2d(1, 1);
		glVertex2f(25.0, 2.0);
		glTexCoord2d(1, 0);
		glVertex2f(25.0, 8.0);
		glTexCoord2d(0, 0);
		glVertex2f(5.0, 8.0);
	glEnd();

	//yes
	glBindTexture(GL_TEXTURE_2D, 11);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(12.0, -2.0);
		glTexCoord2d(1, 1);
		glVertex2f(16.0, -2.0);
		glTexCoord2d(1, 0);
		glVertex2f(16.0, 0.0);
		glTexCoord2d(0, 0);
		glVertex2f(12.0, 0.0);
	glEnd();
	//no
	glBindTexture(GL_TEXTURE_2D, 12);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(12.0, -5.0);
		glTexCoord2d(1, 1);
		glVertex2f(16.0, -5.0);
		glTexCoord2d(1, 0);
		glVertex2f(16.0, -3.0);
		glTexCoord2d(0, 0);
		glVertex2f(12.0, -3.0);
	glEnd();

	
	glDisable(GL_TEXTURE_2D);
}

void drawExitPointer()
{
	glEnable(GL_TEXTURE_2D);

	//pointer draw
	glBindTexture(GL_TEXTURE_2D, 10);
	glBegin(GL_QUADS);
		if(exitYes)
		{
			glTexCoord2d(0, 1);
			glVertex2f(9.0, -2.0);
			glTexCoord2d(1, 1);
			glVertex2f(11.0, -2.0);
			glTexCoord2d(1, 0);
			glVertex2f(11.0, 0.0);
			glTexCoord2d(0, 0);
			glVertex2f(9.0, 0.0);
		}
	//no
		else
		{
			glTexCoord2d(0, 1);
			glVertex2f(9.0, -5.0);
			glTexCoord2d(1, 1);
			glVertex2f(11.0, -5.0);
			glTexCoord2d(1, 0);
			glVertex2f(11.0, -3.0);
			glTexCoord2d(0, 0);
			glVertex2f(9.0, -3.0);
		}

	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawCreditBox()
{
	glColor3f(1.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 16);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(-1.0, -11.0);
		glTexCoord2d(1, 1);
		glVertex2f(31.0, -11.0);
		glTexCoord2d(1, 0);
		glVertex2f(31.0, 11.0);
		glTexCoord2d(0, 0);
		glVertex2f(-1.0, 11.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void drawLevelBox()
{
	glColor3f(1.0, 1.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 14);
	//level
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(10.0, 1.0);
		glTexCoord2d(1, 1);
		glVertex2f(20.0, 1.0);
		glTexCoord2d(1, 0);
		glVertex2f(20.0, 5.0);
		glTexCoord2d(0, 0);
		glVertex2f(10.0, 5.0);
	glEnd();
	
}

void drawLevelNumber()
{
	glColor3f(0.0, 0.0, 0.0);
	switch(levelNo)
	{
	case 1:
		drawOne(15.0, -4.0, 0.0, 3.0);
		break;
	case 2:
		drawTwo(15.0, -4.0, 0.0, 3.0);
		break;
	case 3:
		drawThree(15.0, -4.0, 0.0, 2.0);
		break;
	case 4:
		drawFour(15.0, -4.0, 0.0, 2.0);
		break;
	default:
		break;
	}
}

void drawGameOverBox()
{
}

void drawExitGameBox()
{
	
	//are you sure to exit?
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, 9);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(5.0, 2.0);
		glTexCoord2d(1, 1);
		glVertex2f(25.0, 2.0);
		glTexCoord2d(1, 0);
		glVertex2f(25.0, 8.0);
		glTexCoord2d(0, 0);
		glVertex2f(5.0, 8.0);
	glEnd();

	//yes
	glBindTexture(GL_TEXTURE_2D, 11);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(12.0, -2.0);
		glTexCoord2d(1, 1);
		glVertex2f(16.0, -2.0);
		glTexCoord2d(1, 0);
		glVertex2f(16.0, 0.0);
		glTexCoord2d(0, 0);
		glVertex2f(12.0, 0.0);
	glEnd();
	//no
	glBindTexture(GL_TEXTURE_2D, 12);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 1);
		glVertex2f(12.0, -5.0);
		glTexCoord2d(1, 1);
		glVertex2f(16.0, -5.0);
		glTexCoord2d(1, 0);
		glVertex2f(16.0, -3.0);
		glTexCoord2d(0, 0);
		glVertex2f(12.0, -3.0);
	glEnd();

	

	glDisable(GL_TEXTURE_2D);
}

void drawExitGameBoxPointer()
{
	glEnable(GL_TEXTURE_2D);

	//pointer draw
	glBindTexture(GL_TEXTURE_2D, 10);
	if(exitGameYes)
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0, 1);
			glVertex2f(9.0, -2.0);
			glTexCoord2d(1, 1);
			glVertex2f(11.0, -2.0);
			glTexCoord2d(1, 0);
			glVertex2f(11.0, 0.0);
			glTexCoord2d(0, 0);
			glVertex2f(9.0, 0.0);
		glEnd();
	}
	//no
	else
	{
		glBegin(GL_QUADS);
			glTexCoord2d(0, 1);
			glVertex2f(9.0, -5.0);
			glTexCoord2d(1, 1);
			glVertex2f(11.0, -5.0);
			glTexCoord2d(1, 0);
			glVertex2f(11.0, -3.0);
			glTexCoord2d(0, 0);
			glVertex2f(9.0, -3.0);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}


void createDisplayList()
{
	glNewList(1, GL_COMPILE);

	glBegin(GL_QUADS);
			glVertex2f( -bricks.widthOfBrick/2, -bricks.heightOfBrick/2);
			glVertex2f(bricks.widthOfBrick/2, -bricks.heightOfBrick/2);
			glVertex2f(bricks.widthOfBrick/2, bricks.heightOfBrick/2);
			glVertex2f(-bricks.widthOfBrick/2, bricks.heightOfBrick/2);
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBegin(GL_QUADS);
			glVertex2f(-bricks.widthOfBrick/2, -bricks.heightOfBrick/2);
			glVertex2f(bricks.widthOfBrick/2, -bricks.heightOfBrick/2);
			glVertex2f(bricks.widthOfBrick/2, bricks.heightOfBrick/2);
			glVertex2f(-bricks.widthOfBrick/2, bricks.heightOfBrick/2);
		glEnd();
	glEndList();

	glNewList(2, GL_COMPILE);

	glutSolidSphere(b1.radius, 20, 20);
	
	glEndList();

	glNewList(3, GL_COMPILE);
	makeBackground();
	glEndList();

	glNewList(4, GL_COMPILE);
	displayStarting();
	glEndList();

	glNewList(5, GL_COMPILE);
	displayMenu();
	glEndList();

	glNewList(6, GL_COMPILE);
	livesBoard();
	glEndList();

	glNewList(7, GL_COMPILE);
	drawExitBox();
	glEndList();

	glNewList(8, GL_COMPILE);
	drawCreditBox();
	glEndList();

	glNewList(9, GL_COMPILE);
	drawLevelBox();
	glEndList();

	glNewList(10, GL_COMPILE);
	drawExitGameBox();
	glEndList();

	glNewList(11, GL_COMPILE);
	drawShootPower();
	glEndList();

	glNewList(12, GL_COMPILE);
	drawNoShootPower();
	glEndList();

	glNewList(13, GL_COMPILE);
	drawGluePower();
	glEndList();

	glNewList(14, GL_COMPILE);
	drawUngluePower();
	glEndList();

	glNewList(15, GL_COMPILE);
	drawExpandPower();
	glEndList();

	glNewList(16, GL_COMPILE);
	drawShrinkPower();
	glEndList();

	glNewList(17, GL_COMPILE);
	draw1UpPower();
	glEndList();

}
void display()
{
	glClearColor(1.0, 1.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if(game== STARTING)
	{
		//displayStarting();
		glCallList(4);
	}
	else if(game== MENU)
	{
		//displayMenu();
		glCallList(5);
		displayMenuPointer();
	}

	else if(game== EXITBOX)
	{
		//drawExitBox();
		glCallList(7);
		drawExitPointer();
	}

	else if(game== CREDITBOX)
	{
		//drawCreditBox();
		glCallList(8);
	}

	else if(game== LEVELBOX)
	{
		//drawLevelBox();
		glCallList(9);
		drawLevelNumber();
	}

	else
	{
	glColor3f(1.0, 0.0, 0.0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	bricks.drawBricks();
	b1.draw();
	p1.draw();
	bl1.drawBullets();
	pq1.drawPowers();

	if(game== EXITGAMEBOX)
	{
		//drawExitGameBox();
		glCallList(10);
		drawExitGameBoxPointer();
	}
	//makeBackground();
	glCallList(3);
	livesBoard();
	glCallList(6);
	
	}
	
	
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0, 31.0, -11.0, 11.0);
	glMatrixMode(GL_MODELVIEW);
}

void updateFunction()
{
	if(game== STARTNEW)
	{
		if(clock()- 20> storeTime)
		{

			if(b1.giveStatus()== START)
			{
				storeTime= clock();
				if(keyStatus1!=0)
				{
					p1.moveLeft();
					b1.moveLeft(bricks, p1);
					b1.checkCollisionWithPaddle(p1);
				}

				else if(keyStatus2!= 0)
				{
					p1.moveRight();
					b1.moveRight(bricks, p1);
					b1.checkCollisionWithPaddle(p1);
				}
				
				glutPostRedisplay();
			}

			else if(b1.giveStatus()== CONTINUE)
			{
				storeTime= clock();
				b1.move();
				b1.checkCollision(bricks);
				pq1.addPowerFromBricks(bricks);
				b1.checkCollisionWithPaddle(p1);
				//cout<<"something\n";
				pq1.movePower();
				pq1.checkCollision(p1, b1, bricks);
				pq1.deletePower(p1, b1, bricks);

				bl1.moveBullets(bricks);
				bl1.checkForCollision(bricks);
				bl1.makeNonActive(bricks);


				if(bricks.ifEmpty())
				{
					//ifLevelChange=1;
					changeLevel();
				}

				if(keyStatus1!=0)
				{
					p1.moveLeft();
					b1.moveLeft(bricks, p1);
					glutPostRedisplay();
				}
				else if(keyStatus2!=0)
				{
					p1.moveRight();
					b1.moveRight(bricks, p1);
					glutPostRedisplay();
				}
	
				//storeTime= clock();
				b1.move();
				b1.checkCollision(bricks);
				pq1.addPowerFromBricks(bricks);
				b1.checkCollisionWithPaddle(p1);
				//cout<<"something\n";
				pq1.movePower();
				pq1.checkCollision(p1, b1, bricks);
				pq1.deletePower(p1, b1, bricks);

				bl1.moveBullets(bricks);
				bl1.checkForCollision(bricks);
				bl1.makeNonActive(bricks);


				if(bricks.ifEmpty())
				{
					//ifLevelChange=1;
					changeLevel();
				}

				if(keyStatus1!=0)
				{
					p1.moveLeft();
					b1.moveLeft(bricks, p1);
					glutPostRedisplay();
				}
				else if(keyStatus2!=0)
				{
					p1.moveRight();
					b1.moveRight(bricks, p1);
					glutPostRedisplay();
				}
				
				glutPostRedisplay();
			}


			else if(b1.giveStatus()== OVER)
			{
				game= GAMEOVERBOX;
				b1.move();
				glutPostRedisplay();
			}
		}
	}

	else if(game== GAMEOVERBOX)
	{
		if(clock()- storeTime> 3000)
		{
			storeTime= clock();
			game= MENU;
			glutPostRedisplay();
		}
	}
}

void keyboard(unsigned char key, int x, int y)
{
	if(game==STARTING)
	{

		if(key== 'f')
		{
			engineMain->play2D("media/fullScreen.wav");
			if(fullScreen)
		{
			
			glutReshapeWindow(WIDTH, HEIGHT);
			glutPositionWindow(100, 100);
			fullScreen= 0;
		}
		else
		{

			glutFullScreen();
			fullScreen= 1;
		}
		}
		else if(key== 27)
		{
			engineMain->stopAllSounds();
			engineMain->play2D("media/gameExit.wav");
			game=EXITBOX;
			glutPostRedisplay();
			
		}
		else
		{
			engineMain->stopAllSounds();
			engineMain->play2D("media/menu.ogg",true);
			game= MENU;
			glutPostRedisplay();
		}
	}
	else if(game== MENU)
	{

		switch(key)
		{
		case 27:
			game= EXITBOX;
			glutPostRedisplay();
			break;
		case 13:
			if(menuPointer==0)
			{
				game= STARTNEW;
				initialize();
				glutPostRedisplay();
			}

			else if(menuPointer== 1)
			{
				continueIndication= 1;
				game= STARTNEW;
				initialize();
				glutPostRedisplay();
			}

			else if(menuPointer== 2)
			{
				engineMain->stopAllSounds();
				engineMain->play2D("media/credits2.ogg",true);
				game= CREDITBOX;
				glutPostRedisplay();
			}
			else if(menuPointer== 3)
			{
				engineMain->stopAllSounds();
				engineMain->play2D("media/gameExit.wav");
				game= EXITBOX;
				glutPostRedisplay();
			}

			menuPointer= 0;
			break;
		case 'f':
			engineMain->play2D("media/fullScreen.wav");
			if(fullScreen)
		{
			glutReshapeWindow(WIDTH, HEIGHT);
			glutPositionWindow(100, 100);
			fullScreen= 0;
			break;
		}
		else
		{
			glutFullScreen();
			fullScreen= 1;
			break;
		}
		default:
			break;
		}
	}

	else if(game== EXITBOX)
	{
		switch(key)
		{
		case 27:
			exit(0);
			break;
		case 13:
			if(exitYes)
			{
				exit(0);
			}

			else
			{
				engineMain->stopAllSounds();
				engineMain->play2D("media/menu.ogg", true);
				game= MENU;
				exitYes= 1;
			}
			break;
		case 'f':
			engineMain->play2D("media/fullScreen.wav");
			if(fullScreen)
		{
			glutReshapeWindow(WIDTH, HEIGHT);
			glutPositionWindow(100, 100);
			fullScreen= 0;
			break;
		}
		else
		{
			glutFullScreen();
			fullScreen= 1;
			break;
		}
		default:
			break;
		}

		glutPostRedisplay();
	}

	else if(game== CREDITBOX)
	{
		if(key== 27)
		{
			engineMain->stopAllSounds();
			engineMain->play2D("media/menu.ogg", true);
			game= MENU;
			glutPostRedisplay();
		}

		if(key== 'f')
		{
			engineMain->play2D("media/fullScreen.wav");
			if(fullScreen)
		{
			glutReshapeWindow(WIDTH, HEIGHT);
			glutPositionWindow(100, 100);
			fullScreen= 0;
		}
		else
		{
			glutFullScreen();
			fullScreen= 1;
		}
		}
	}

	else if(game== LEVELBOX)
	{
		game= STARTNEW;
		glutPostRedisplay();
	}

	else if(game== EXITGAMEBOX)
	{
		switch(key)
		{
		case 27:
			game= STARTNEW;
			glutPostRedisplay();
			break;
		case 13:
			if(exitGameYes)
			{
				game= MENU;
				engineMain->stopAllSounds();
				engineMain->play2D("media/menu.ogg", true);
			}
			else
			{
				game= STARTNEW;
			}
			glutPostRedisplay();
			break;
		case 'f':
			engineMain->play2D("media/fullScreen.wav");
			if(fullScreen)
			{
				glutReshapeWindow(WIDTH, HEIGHT);
				glutPositionWindow(100, 100);
				fullScreen= 0;
				break;
			}
			else
			{
				glutFullScreen();
				fullScreen= 1;
				break;
			}
		}
	}
	else
	{
	switch(key)
	{
	case 27:
		game= EXITGAMEBOX;
		glutPostRedisplay();
		break;
	case 'f':
		engineMain->play2D("media/fullScreen.wav");
		if(fullScreen)
		{
			glutReshapeWindow(WIDTH, HEIGHT);
			glutPositionWindow(100, 100);
			fullScreen= 0;
			break;
		}
		else
		{
			glutFullScreen();
			fullScreen= 1;
			break;
		}
	case 'p':

		engineMain->play2D("media/pause.wav");
		if(game== STARTNEW)
		{
			game= PAUSEDBOX;
		}
		else
		{
			game= STARTNEW;
		}

		glutPostRedisplay();
		break;
	default:
		break;
	}
	}
}

void special(int key, int x, int y)
{
	if(game== STARTING)
	{
		game= MENU;
		glutPostRedisplay();
	}

	else if(game== MENU)
	{
		switch(key)
		{
		case GLUT_KEY_UP:
			if(menuPointer>0)
			{
				menuPointer--;
			}
			break;
		case GLUT_KEY_DOWN:
			if(menuPointer<3)
			{
				menuPointer++;
				break;
			}
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}

	
	else if(game== EXITBOX)
	{
		switch(key)
		{
		case GLUT_KEY_UP:
			if(!exitYes)
				exitYes= 1;
			break;
		case GLUT_KEY_DOWN:
			if(exitYes)
				exitYes= 0;
			break;
		}

		glutPostRedisplay();
	}

	else if(game== LEVELBOX)
	{
		game= STARTNEW;
		glutPostRedisplay();
	}

	else if(game== EXITGAMEBOX)
	{
		
		switch(key)
		{
		case GLUT_KEY_UP:
			if(!exitGameYes)
				exitGameYes= 1;
			break;
		case GLUT_KEY_DOWN:
			if(exitGameYes)
				exitGameYes= 0;
			break;
		}

		glutPostRedisplay();
	}

	else
	{
		glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
		glutIgnoreKeyRepeat(1);

		switch(key)
		{
		case GLUT_KEY_LEFT:
			keyStatus1= 1;
			p1.moveLeft();
			b1.moveLeft(bricks, p1);//in case when ball is glued
			break;
		case GLUT_KEY_RIGHT:
			keyStatus2= 1;
			p1.moveRight();
			b1.moveRight(bricks, p1); //in case when ball is glued
			break;
		case GLUT_KEY_UP:
			b1.startTheGame();
			if(p1.shoot== 1&& clock()-400 >storeTimeShooter)
			{
				engineMain->play2D("media/powerGun.wav");
				storeTimeShooter= clock();
				bl1.makeActive(p1);
			}

			if(b1.isGlue)
			{
				b1.makeDynamic();
			}
			break;
		default:
			break;
		}
		glutPostRedisplay();
	}
}

void specialUp(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_LEFT:
		keyStatus1= 0;
		glutPostRedisplay();
	case GLUT_KEY_RIGHT:
		keyStatus2= 0;
	default:
		break;
	}
}

void detectMousePassive(int x, int y)
{
	//cout<<x<<" "<<y<<endl;
}

int main(int argc, char** argv)
{
	

	glutInit(&argc, argv);
	

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("demoBricks");
	init();


	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	glutSpecialUpFunc(specialUp);
	glutSetCursor(GLUT_CURSOR_NONE); 
	glutIdleFunc(updateFunction);
	glutMainLoop();
	return 0;
}
