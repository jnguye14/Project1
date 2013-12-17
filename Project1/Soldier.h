#pragma once

#ifndef SOLDIER_H
#define SOLDIER_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "Main.h"

class Soldier
{
public:
	float posX;
	float posY;
	float health;
	float movement;
	float attackDamage;
	float attackRange;

	Soldier(){
		posX = 200;
		posY = 100;
	}
	~Soldier(){}

	void toString()
	{
		printf("%s \n","This is the soldier");
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
	}
};

#endif
