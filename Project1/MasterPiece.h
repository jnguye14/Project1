#pragma once

#ifndef MASTERPIECE_H
#define MASTERPIECE_H

#include <sapi.h>
#include <iostream>
#include <string>

#include "glut.h"
#include "Main.h"
//Allen Hsia: Todo 1/19/2014.fix the posX and posY for the location to draw
class MasterPiece
{
protected:
	float posX;
	float posY;
	float health;
	float movement;
	float attackDamage;
	float attackRange;
	string text;
	bool selected;
	int timer;
	bool isBlue;
public:
	GLuint texture;
	MasterPiece(){
	}
	~MasterPiece(){}
	void drawOutline()
	{
		if(selected)
		{
			glLineWidth(10);
			
			// circle
			float PI, theta, radius = 0.1f;
			PI = acos((float) (-1));
			glBegin(GL_LINE_LOOP);
			glColor3f(1.0, 0.0, 0.0);
			for (theta = 0; theta<2 * PI; theta += (2.0f * PI) / 360.0f)
			{
				glVertex2f(-posX + cos(theta)*radius, -posY + sin(theta)*radius);
			}
			glEnd();

			/* // square
			glBegin(GL_LINE_LOOP);
			glColor3f(1.0,0.0,0.0);
			glVertex2f(-posX-0.1f, -posY-0.1f);
			glVertex2f(-posX+0.1f, -posY-0.1f);
			glVertex2f(-posX+0.1f, -posY+0.1f);
			glVertex2f(-posX-0.1f, -posY+0.1f);
			glEnd();
			//*/

			glColor3f(1.0,1.0,1.0);
		}
	}
	virtual void moveR()
	{
		setPosX(getPosX()-0.1);
	}
	virtual void moveD()
	{
		setPosY(getPosY()+0.1);
	}
	virtual void moveL()
	{
		setPosX(getPosX()+0.1);
	}
	virtual void moveU()
	{
		setPosY(getPosY()-0.1);
	}
	void select()
	{
		selected = true;
	}

	void unselect()
	{
		selected = false;
	}

	bool isMouseOver(int x, int y)
	{
		//they were all 500 before hand. i tried 223,273,682,654
		int xmin = 500 * ((-posX - 0.1f + 1.0f)/2.0f); // why negative?
		int xmax = 500 * ((-posX + 0.1f + 1.0f)/2.0f); // why negative?
		int ymin = 500 * ((posY - 0.1f + 1.0f)/2.0f);
		int ymax = 700 * ((posY + 0.1f + 1.0f)/2.0f);
		if ((x > xmin) && (x < xmax) && (y > ymin) && (y < ymax))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	virtual string toString(){
	return text;} //debugging purposes
	virtual void drawPiece()
	{
		drawOutline();
		//timer = 1000;
		if (timer>0)
		{
			if (isBlue)
			{
				glColor3f(0.0, 1.0, 0.0);
			}
			else
			{
				glColor3f(1.0, 0.0, 0.0);
			}
			timer--;
		}
		else
		{
			glColor3f(1.0, 1.0, 1.0);
		}
	}
	virtual void setHealth(float newHealth)
	{
		health = newHealth;
	}
	virtual float getHealth()
	{
		return health;
	}
	virtual void setPosX(float newPosX){
		posX=newPosX;
	}
	virtual void setPosY(float newPosY){
		posY=newPosY;
	}
	virtual float getPosX(){return posX;}
	virtual float getPosY(){return posY;}
	virtual float getAttackDamage()
	{
		return attackDamage;
	}
	virtual	float getAttackRange()
	{
		return attackRange;
	}
	virtual void isAttacked(float damageAmount)
	{
		setHealth( getHealth() -damageAmount );
		timer = 1000;
		isBlue = false;
	}
	virtual void healed()
	{
		timer=1000;
		isBlue = true;
	}
};

#endif
