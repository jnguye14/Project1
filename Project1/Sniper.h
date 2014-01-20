#pragma once

#ifndef SNIPER_H
#define SNIPER_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "Main.h"

class Sniper : public MasterPiece
{
public:
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
	void setPosX(float newPosX)
	{
		posX = newPosX;
	}
	void setPosY(float newPosY)
	{
		posY = newPosY;
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
	string toString()
	{
		text = "This is the Sniper\n";
		return text;
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
