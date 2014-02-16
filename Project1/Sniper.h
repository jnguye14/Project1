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
	Sniper(int player){
		if(player == 1)
		{
			posX = 0.5f;
			posY = 0.5f;
		}
		else
		{
			posX = -0.5f;
			posY = -0.5f;
		}	
		timer=0;
		health = 100;
		movement = 500;
		attackDamage = 10;
		attackRange = 0.3f;
		selected = false;
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
		text = "Sniper";
		return text;
	}
	
	void drawPiece()
	{
		MasterPiece::drawPiece();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();

		glBegin(GL_TRIANGLES);
		glTexCoord2f(3.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, -posY-0.1f);
		glTexCoord2f(4.0f / 6.0f, 1.0f);
		glVertex2f(-posX+0.1f, -posY-0.1f);
		glTexCoord2f(4.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, -posY+0.1f);

		glTexCoord2f(3.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, -posY-0.1f);
		glTexCoord2f(4.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, -posY+0.1f);
		glTexCoord2f(3.0f / 6.0f, 0.0f);
		glVertex2f(-posX-0.1f, -posY+0.1f);
		glEnd();
		

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
};

#endif
