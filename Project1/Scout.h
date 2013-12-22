#pragma once

#ifndef SCOUT_H
#define SCOUT_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "Main.h"

class Scout
{
public:
	float posX;
	float posY;
	float health;
	float movement;
	float attackDamage;
	float attackRange;
	
	Scout(){
		posX = 400;
		posY = 400;
		health = 400;
		movement = 400;
		attackDamage = 400;
		attackRange = 400;
	}
	~Scout(){}
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
		printf("%s \n","This is the scout");
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
