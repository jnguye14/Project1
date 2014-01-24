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
		text = "This is the Medic\n";
		return text;
	}
	void drawPiece()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();


		glBegin(GL_TRIANGLES);
		glTexCoord2f(2.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, posY-0.1f);
		glTexCoord2f(3.0f / 6.0f, 1.0f);
		glVertex2f(-posX+0.1f, posY-0.1f);
		glTexCoord2f(3.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, posY+0.1f);

		glTexCoord2f(2.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, posY-0.1f);
		glTexCoord2f(3.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, posY+0.1f);
		glTexCoord2f(2.0f / 6.0f, 0.0f);
		glVertex2f(-posX-0.1f, posY+0.1f);
		glEnd();
		

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
};

#endif
