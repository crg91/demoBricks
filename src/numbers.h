#ifndef NUMBERS_H
#define NUMBERS_H
#include<GL/glut.h>

void drawZero(GLfloat, GLfloat, GLfloat=0.0, GLfloat=1.0);
void drawOne(GLfloat, GLfloat, GLfloat= 0.0, GLfloat=1.0);
void drawTwo(GLfloat, GLfloat, GLfloat= 0.0, GLfloat=1.0);
void drawThree(GLfloat, GLfloat, GLfloat= 0.0, GLfloat=1.0);
void drawFour(GLfloat, GLfloat, GLfloat= 0.0, GLfloat=1.0);
void drawFive(GLfloat, GLfloat, GLfloat= 0.0, GLfloat=1.0);
void drawSix(GLfloat, GLfloat, GLfloat= 0.0, GLfloat=1.0);
void drawSeven(GLfloat, GLfloat, GLfloat= 0.0, GLfloat=1.0);
void drawEight(GLfloat, GLfloat, GLfloat= 0.0, GLfloat=1.0);
void drawNine(GLfloat, GLfloat, GLfloat= 0.0, GLfloat=1.0);

void drawStrip(GLfloat l=1.0)
{
   l=12*l/13;
   GLfloat w=l/10;
   glBegin(GL_POLYGON);
      glVertex2f(-l/2, 0.0);
      glVertex2f(-l/2+ w/2, -w/2);
      glVertex2f(l/2- w/2, -w/2);
      glVertex2f(l/2, 0.0);
      glVertex2f(l/2- w/2, w/2);
      glVertex2f(-l/2+ w/2, w/2); 
   glEnd();
}

void drawZero(GLfloat x, GLfloat y, GLfloat z, GLfloat length)
{
   glPushMatrix(); //save initial settings
   drawSeven(x, y, z, length);
   glTranslatef(x, y, z); //translate part of seven other than one
   glPushMatrix();
   glTranslatef(0.0, -length, 0.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(-length/2, length/2, 0.0);
   glRotatef(90, 0.0, 0.0, 1.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(-length/2, -length/2, 0.0);
   glRotatef(90, 0.0, 0.0, 1.0);
   drawStrip(length);
   glPopMatrix();
   glPopMatrix(); //load initial settings
}
void drawOne(GLfloat x, GLfloat y, GLfloat z, GLfloat length)
{
   glPushMatrix(); //so that the initial modelling or view settings in the calling program don't get changed
   glTranslatef(x, y, z); //for the translation of whole figure created below at origin to x, y, z number would be in xy plane
   GLfloat width=length/10;
   glPushMatrix();
   glTranslatef(length/2-width/2, length/2, 0.0);
   glRotatef(90, 0, 0, 1);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(length/2-width/2, -length/2, 0.0);
   glRotatef(90, 0, 0, 1);
   drawStrip(length);
   glPopMatrix();
   glPopMatrix(); //to load the previous settings
}

void drawTwo(GLfloat x, GLfloat y, GLfloat z, GLfloat length)
{
   glPushMatrix(); //save initial settings
   glTranslatef(x, y, z); //translation of whole figure
   GLfloat width=length/10;
   glPushMatrix();
   glTranslatef(0.0, length, 0.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0.0, -length, 0.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(length/2-width/2, length/2, 0.0);
   glRotatef(90, 0.0, 0.0, 1.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(-length/2+width/2, -length/2, 0.0);
   glRotatef(90, 0.0, 0.0, 1.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   drawStrip(length);
   glPopMatrix();
   glPopMatrix(); //load basic settings
}
void drawSeven(GLfloat x, GLfloat y, GLfloat z, GLfloat length)
{
   glPushMatrix(); //save initial settings
   drawOne(x, y, z, length);
   glTranslatef(x, y, z); //translate part of seven other than one
   glPushMatrix();
   glTranslatef(0.0, length, 0.0);
   drawStrip(length);
   glPopMatrix();
   glPopMatrix(); //load initial settings
}

void drawThree(GLfloat x, GLfloat y, GLfloat z, GLfloat length)
{
   glPushMatrix(); //save initial settings
   drawSeven(x, y, z, length);
   glTranslatef(x, y, z); //translate part of three other than seven
   glPushMatrix();
   glTranslatef(0.0, -length, 0.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   drawStrip(length);
   glPopMatrix();
   glPopMatrix(); //load initial settings
}

void drawFour(GLfloat x, GLfloat y, GLfloat z, GLfloat length)
{
   glPushMatrix(); //save initial settings
   GLfloat width= length/10;
   drawOne(x, y, z, length);
   glTranslatef(x, y, z); //translate part of four other than one
   glPushMatrix();
   glTranslatef(-length/2+width/2, length/2, 0.0);
   glRotatef(90, 0.0, 0.0, 1.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   drawStrip(length);
   glPopMatrix();
   glPopMatrix();
}

void drawFive(GLfloat x, GLfloat y, GLfloat z, GLfloat length)
{
   glPushMatrix(); //save initial settings
   glTranslatef(x, y, z); //move the number to desired coordinates
   GLfloat width = length/10;
   glPushMatrix();
   glTranslatef(0.0, length, 0.0);
   glRotatef(180, 0.0, 0.0, 1.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(-length/2+width/2, length/2, 0.0);
   glRotatef(90, 0.0, 0.0, 1.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(length/2-width/2, -length/2, 0.0);
   glRotatef(90, 0.0, 0.0, 1.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   glTranslatef(0.0, -length, 0.0);
   drawStrip(length);
   glPopMatrix();
   glPushMatrix();
   drawStrip(length);
   glPopMatrix();
   glPopMatrix(); //load initial settings
}

void drawSix(GLfloat x, GLfloat y, GLfloat z, GLfloat length)
{
   glPushMatrix(); //save initial settings
   GLfloat width = length/10;
   drawFive(x, y, z, length);
   glTranslatef(x, y, z); //translate six other than five portion
   glPushMatrix();
   glTranslatef(-length/2+width/2, -length/2, 0.0);
   glRotatef(90, 0.0, 0.0, 1.0);
   drawStrip(length);
   glPopMatrix();
   glPopMatrix(); //load initial settings
}

void drawNine(GLfloat x, GLfloat y, GLfloat z, GLfloat length)
{
   glPushMatrix(); //save initial settings
   GLfloat width= length/10;
   drawThree(x, y, z, length);
   glTranslatef(x, y, z); //translate rest of nine other than three
   glPushMatrix();
   glTranslatef(-length/2+width/2, length/2, 0.0);
   glRotatef(90, 0.0, 0.0, 1.0);
   drawStrip(length);
   glPopMatrix();
   glPopMatrix(); //load initial settings
}

void drawEight(GLfloat x, GLfloat y, GLfloat z, GLfloat length)
{
   glPushMatrix(); //save initial settings
   GLfloat width= length/10;
   drawNine(x, y, z, length);
   glTranslatef(x, y, z); //translate rest of eight other than nine
   glPushMatrix();
   glTranslatef(-length/2+width/2, -length/2, 0.0);
   glRotatef(90, 0.0, 0.0, 1.0);
   drawStrip(length);
   glPopMatrix();
   glPopMatrix(); //load initial settings
}
#endif
