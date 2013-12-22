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
		posX = 600;
		posY = 600;
		health = 600;
		movement = 600;
		attackDamage = 600;
		attackRange = 600;
	}
	~Soldier(){}
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
