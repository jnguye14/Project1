#pragma once

#ifndef MEDIC_H
#define MEDIC_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "Main.h"

class Medic: public MasterPiece
{
public:

	
	Medic(){
		posX = 300;
		posY = 300;
		health = 300;
		movement = 300;
		attackDamage = 300;
		attackRange = 300;
	}
	~Medic(){}
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
		health=2*newHealth;
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
		printf("%s \n","This is the medic");
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
