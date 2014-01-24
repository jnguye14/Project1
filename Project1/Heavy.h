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
		text = "This is the Heavy\n";
		return text;
	}
	void drawPiece()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();

		glBegin(GL_TRIANGLES);
		glTexCoord2f(1.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, -posY-0.1f);
		glTexCoord2f(2.0f / 6.0f, 1.0f);
		glVertex2f(-posX+0.1f, -posY-0.1f);
		glTexCoord2f(2.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, -posY+0.1f);

		glTexCoord2f(1.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, -posY-0.1f);
		glTexCoord2f(2.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, -posY+0.1f);
		glTexCoord2f(1.0f / 6.0f, 0.0f);
		glVertex2f(-posX-0.1f, -posY+0.1f);
		glEnd();
		
		

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
};

#endif
