#pragma once

#ifndef SOLDIER_H
#define SOLDIER_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "Main.h"

class Soldier : public MasterPiece
{
public:
	Soldier(int player){
		if(player == 1)
		{
			posX = 0.0f;
			posY = 0.5f;
		}
		else
		{
			posX = -0.0f;
			posY = -0.5f;
		}
		health = 600;
		movement = 600;
		attackDamage = 600;
		attackRange = 600;
		selected = false;
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
		text = "This is the Soldier\n";
		return text;
	}
	void moveR()
	{
		setPosX(getPosX()-0.01);
	}
	void moveD()
	{
		setPosY(getPosY()+0.01);
	}
	void moveL()
	{
		setPosX(getPosX()+0.01);
	}
	void moveU()
	{
		setPosY(getPosY()-0.01);
	}
	void drawPiece()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();


		glBegin(GL_TRIANGLES);
		glTexCoord2f(4.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, -posY-0.1f);
		glTexCoord2f(5.0f / 6.0f, 1.0f);
		glVertex2f(-posX+0.1f, -posY-0.1f);
		glTexCoord2f(5.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, -posY+0.1f);

		glTexCoord2f(4.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, -posY-0.1f);
		glTexCoord2f(5.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, -posY+0.1f);
		glTexCoord2f(4.0f / 6.0f, 0.0f);
		glVertex2f(-posX-0.1f, -posY+0.1f);
		glEnd();
		

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		drawOutline();
	}
};

#endif
