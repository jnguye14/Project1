#pragma once

#ifndef COMMANDER_H
#define COMMANDER_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "Main.h"

class Commander : public MasterPiece
{
public:	
	Commander(){
		posX = 100;
		posY = 100;
		health = 100;
		movement = 100;
		attackDamage = 100;
		attackRange = 100;
	}
	~Commander(){}
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
		text = "This is the Commander\n";
		return text;
	}
	void drawPiece()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();

		glBegin(GL_TRIANGLES);
		glTexCoord2f(5.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, -posY-0.1f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(-posX+0.1f, -posY-0.1f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-posX+0.1f, -posY+0.1f);

		glTexCoord2f(5.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, -posY-0.1f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(-posX+0.1f, -posY+0.1f);
		glTexCoord2f(5.0f / 6.0f, 0.0f);
		glVertex2f(-posX-0.1f, -posY+0.1f);
		glEnd();
		

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
};

#endif
