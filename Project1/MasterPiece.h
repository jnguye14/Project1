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
			glBegin(GL_LINE_LOOP);
			glColor3f(1.0,0.0,0.0);
			glVertex2f(-posX-0.1f, -posY-0.1f);
			glVertex2f(-posX+0.1f, -posY-0.1f);
			glVertex2f(-posX+0.1f, -posY+0.1f);
			glVertex2f(-posX-0.1f, -posY+0.1f);
			glEnd();
			glColor3f(1.0,1.0,1.0);
		}
	}
	virtual string toString(){
	return text;} //debugging purposes
	virtual void drawPiece(){}
	virtual void setHealth(){}
	virtual void setPosX(float newPosX){
		posX=newPosX;
	}
	virtual void setPosY(float newPosY){
		posY=newPosY;
	}
	virtual float getPosX(){return posX;}
	virtual float getPosY(){return posY;}
	virtual void moveU(){};
	virtual void moveD(){};
	virtual void moveR(){};
	virtual void moveL(){};
};

#endif
