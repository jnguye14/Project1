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
		posX=200;
		posY=100;
	}
	~MasterPiece(){}

	void toString()
	{
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
	}
};

#endif
