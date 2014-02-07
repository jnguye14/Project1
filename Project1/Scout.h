#pragma once

#ifndef SCOUT_H
#define SCOUT_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "Main.h"

class Scout : public MasterPiece
{
public:
	Scout(int player){
		if(player == 1)
		{
			posX = -0.5f;
			posY = -0.5f;
		}
		else
		{
			posX = 0.5f;
			posY = 0.5f;
		}
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
		text = "This is the Scout\n";
		return text;
	}
	void drawPiece()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();

		glBegin(GL_TRIANGLES);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-posX-0.1f, posY-0.1f);
		glTexCoord2f(1.0f / 6.0f, 1.0f);
		glVertex2f(-posX+0.1f, posY-0.1f);
		glTexCoord2f(1.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, posY+0.1f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(-posX-0.1f, posY-0.1f);
		glTexCoord2f(1.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, posY+0.1f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(-posX-0.1f, posY+0.1f);
		glEnd();
		

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
};

#endif
