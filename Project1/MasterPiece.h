#pragma once

#ifndef MASTERPIECE_H
#define MASTERPIECE_H

#include <sapi.h>
#include <iostream>
#include <string>
#include "glut.h"
#include "Main.h"
#include "Commander.h"
#include "Heavy.h"
#include "Medic.h"
#include "Scout.h"
#include "Sniper.h"
#include "Soldier.h"

class MasterPiece
{
public:
	/*Heavy heavy;
	Commander commander;
	Medic medic;
	Scout scout;
	Sniper sniper;
	Soldier soldier;

	float posX;
	float posY;
	float health;
	float movement;
	float attackDamage;
	float attackRange;*/
	
	MasterPiece(){

	}
	~MasterPiece(){}

	void toString()
	{
		printf("%s \n","This is the masterpiece");
		//printf("%f \n %f", posX, posY);
	}
	void drawPiece()
	{

		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glBegin(GL_POLYGON);
		glVertex2f(-0.1, -0.1);
		glVertex2f(0.1, -0.1);
		glVertex2f(0.1, 0.1);
		glVertex2f(-0.1, 0.1);
		glEnd();
		glPopMatrix();
	}
};

#endif
