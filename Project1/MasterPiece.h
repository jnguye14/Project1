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
public:
	GLuint texture;

	MasterPiece(){
	}
	~MasterPiece(){}

	virtual string toString(){
	return text;} //debugging purposes
	virtual void drawPiece(){}
	virtual void setHealth(){}
	virtual void setPosX(){}
	virtual void setPosY(){}
};

#endif
