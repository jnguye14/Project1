#pragma once

#ifndef MASTERPIECE_H
#define MASTERPIECE_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "Main.h"

class MasterPiece
{
protected:
	float posX;
	float posY;
	float health;
	float movement;
	float attackDamage;
	float attackRange;
public:
	
	MasterPiece(){
	}
	~MasterPiece(){}

	virtual void toString()-
	{
		
	}
	virtual void drawPiece()
	{

	}
	virtual void setHealth()
	{
	}

};

#endif
