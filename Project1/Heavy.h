#pragma once

#ifndef HEAVY_H
#define HEAVY_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "MasterPiece.h"

class Heavy : public MasterPiece
{
public:

	
	Heavy(){
		posX = 200;
		posY = 200;
		health = 200;
		movement = 200;
		attackDamage = 200;
		attackRange = 200;
	}
	~Heavy(){}
	
	float getPosX()
	{
		return posX;
	}
	float getPosY()
	{
		return posY;
	}
	float getHealth()
	{
		return health;
	}
	void setHealth(float newHealth)
	{
		health=newHealth;
	}
	float getMovement()
	{
		return movement;
	}
	float getAttackDamage()
	{
		return attackDamage;
	}
	float getAttackRange()
	{
		return attackRange;
	}
	void toString()
	{
		printf("%s \n","This is the Heavy");
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
