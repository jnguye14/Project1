#pragma once

#ifndef MASTERPIECE_H
#define MASTERPIECE_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "Main.h"

class MasterPiece
{
public:
	float posX;
	float posY;

	MasterPiece(){
<<<<<<< HEAD
		posX=200;
		posY=100;
=======
		posX = 200;
		posY = 100;
>>>>>>> 2da49cc49dc7b69818fd2364a5c1ca7967441f54
	}
	~MasterPiece(){}

	void toString()
	{
<<<<<<< HEAD
			printf("%f \n %f",posX,posY);
	}
	void drawPiece()
	{	

			glColor3f(1.0,0.0,0.0);
			glPushMatrix();
			glBegin(GL_POLYGON);
			glVertex2f(-0.1,-0.1);
			glVertex2f(0.1,-0.1);
			glVertex2f(0.1,0.1);
			glVertex2f(-0.1,0.1);
			glEnd();
			glPopMatrix();		
=======
		printf("%f \n %f", posX, posY);
	}
	void drawPiece()
	{

		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glBegin(GL_POLYGON);
		glVertex2f(-0.1, -0.1);
		glVertex2f(0.1, -0.1);
		glVertex2f(0.1, 0.1);
		glVertex2f(-0.1, 0.1);
		glEnd();
		glPopMatrix();
>>>>>>> 2da49cc49dc7b69818fd2364a5c1ca7967441f54
	}
};

#endif
