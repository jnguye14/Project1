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
	Medic(int player){
		if(player == 1)
		{
			posX = -0.5f;
			posY = 0.2f;
		}
		else
		{
			posX = 0.5f;
			posY = -0.2f;
		}
		timer=0;
		health = 100;
		movement = 300;
		attackDamage = 10;
		attackRange = 0.2f;
		selected = false;
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
	float healing()
	{
		return 20;
	}
	string toString()
	{
		text = "Medic";
		return text;
	}

	void drawPiece()
	{
		if(timer>0)
		{
			glColor3f(0.0,0.0,1.0);
			timer--;
		}
		else
		{
			glColor3f(1.0,1.0,1.0);
		}
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();

		glBegin(GL_TRIANGLES);
		glTexCoord2f(2.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, -posY-0.1f);
		glTexCoord2f(3.0f / 6.0f, 1.0f);
		glVertex2f(-posX+0.1f, -posY-0.1f);
		glTexCoord2f(3.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, -posY+0.1f);

		glTexCoord2f(2.0f / 6.0f, 1.0f);
		glVertex2f(-posX-0.1f, -posY-0.1f);
		glTexCoord2f(3.0f / 6.0f, 0.0f);
		glVertex2f(-posX+0.1f, -posY+0.1f);
		glTexCoord2f(2.0f / 6.0f, 0.0f);
		glVertex2f(-posX-0.1f, -posY+0.1f);
		glEnd();
		

		glPopMatrix();
		glDisable(GL_TEXTURE_2D);

		//cout << "enter outline" << endl;
		drawOutline();
		//cout << "exit outline" << endl;
	}
};

#endif
