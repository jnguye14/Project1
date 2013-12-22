#pragma once

#ifndef SNIPER_H
#define SNIPER_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "Main.h"

class Sniper
{
public:
	float posX;
	float posY;
	float health;
	float movement;
	float attackDamage;
	float attackRange;
	
	Sniper(){
		posX = 500;
		posY = 500;		
		health = 500;
		movement = 500;
		attackDamage = 500;
		attackRange = 500;
	}
	~Sniper(){}
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
		printf("%s \n","This is the sniper");
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
