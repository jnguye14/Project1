#pragma once

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "glut.h"
#include "MasterPiece.h"
#include "Commander.h"
#include "Heavy.h"
#include "Medic.h"
#include "Scout.h"
#include "Sniper.h"
#include "Soldier.h"
#include "Textures.h"
#include <time.h>
#include <mutex>
#include <sstream>
#include <string>
int currentScene = 0;
int playerWinner = 0;
int playerNumber = 0;
bool isSet = false; 
bool isPlayerOneTurn = true;

vector <MasterPiece*> unitList1;
vector <MasterPiece*> unitList2;
MasterPiece* selectedUnit;

// TODO: implement mutual exclusion for shared global variables
//mutex curSceneLock; // for int currentScene;
//mutex playerTurnLock; // for bool isPlayerOneTurn;
//mutex endGameLock; // for bool endGame;
void hud(int player)
{
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(-0.5,0.9);
	stringstream ss;
	if(isPlayerOneTurn)
	{
		ss<<"Player 1 turn";
		string play = ss.str();
		for(int i =0;i<play.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,play[i]);
		}
	}
	else
	{
		ss<<"Player 2 turn";
		string play = ss.str();
		for(int i =0;i<play.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,play[i]);
		}
	}
	ss.str(string());
	if(selectedUnit){
		glColor3f(1.0,0.0,0.0);
		if (selectedUnit) ss << "Unit: " << selectedUnit->toString();
		float xx=-0.9,yy=0.5;
		string stats = ss.str();
		glRasterPos2f(xx,0.5);
		for(int i =0;i<stats.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,stats[i]);
		}
		ss.str(string());
		if (selectedUnit) ss << "Attack damage: " << selectedUnit->getAttackDamage();
		//yy=-0.01;
		glRasterPos2f(xx,0.4);
		stats = ss.str();
		for(int i =0;i<stats.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,stats[i]);
		}
		ss.str(string());
		if (selectedUnit) ss << "Health: " << selectedUnit->getHealth();
		//yy=-0.01;
		glRasterPos2f(xx,0.3);
		stats = ss.str();
		for(int i =0;i<stats.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,stats[i]);
		}
	}
}
void MouseButton(int button, int state, int x, int y)
{
	// Respond to mouse button presses.
	// If button1 pressed, mark this state so we know in motion function.
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_UP)
		{
			switch (currentScene)
			{
			case 0: // main menu
				if ((x > 325) && (x < 400) && (y>225) && (y < 275))
				{
					exit(0);
				}
				if ((x > 100) && (x < 175) && (y>225) && (y < 275))
				{
					currentScene = 1;
					glutPostRedisplay();
				}
				printf("%s", "pressed button");
				break;
			case 1: // set up
				break;
			case 2: // main game
				if (isPlayerOneTurn)
				{
					for (int i = 0; i<unitList1.size(); i++)
					{
						if (unitList1.at(i)->isMouseOver(x,y))
						{
							if (selectedUnit != NULL)
							{
								selectedUnit->unselect();
							}
							selectedUnit = unitList1.at(i);
							selectedUnit->select();
							break;
						}
					}
				}
				else // player two's turn
				{
					for (int i = 0; i<unitList2.size(); i++)
					{
						if (unitList2.at(i)->isMouseOver(x, y))
						{
							if (selectedUnit != NULL)
							{
								selectedUnit->unselect();
							}
							selectedUnit = unitList2.at(i);
							selectedUnit->select();
							break;
						}
					}
				}
				break;
			case 3: // end game
				// restart button
				if ((x > 225) && (x < 313) && (y>350) && (y < 400))
				{
					isPlayerOneTurn = true;
					isSet = false;
					currentScene = 0;
					glutPostRedisplay();
				}
				break;
			default:
				break;
			}
			
			//printf("(%d, %d)\n",x, y);
		}
	}
}
void movement(unsigned char key, int x, int y)
{

	//find selected unit. store that in a variable
	if(key=='w')
	{
		if(selectedUnit!=NULL)
		{
			selectedUnit->moveU();
		}
	}
	if(key=='a')
	{
		if(selectedUnit!=NULL)
		{
			selectedUnit->moveL();
		}
	}
	if(key=='s')
	{
		if(selectedUnit!=NULL)
		{
			selectedUnit->moveD();
		}
	}
	if(key=='d')
	{
		if(selectedUnit!=NULL)
		{
			selectedUnit->moveR();
		}
	}
}

void speechWait()
{
	glutPostRedisplay();
}

void motion(int x, int y)
{
	printf("(%d, %d)\n", x, y);
}

#pragma mark region Game Screens
void MainMenuDisplay()
{
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-0.6, -0.1);
	glVertex2f(-0.6, 0.1);
	glVertex2f(-0.3, 0.1);
	glVertex2f(-0.3, -0.1);
	glEnd();
	glPopMatrix();

	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(-0.54,-0.03);
	stringstream ss;
	ss<<"PLAY";
	string play = ss.str();
	for(int i =0;i<play.length();i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,play[i]);
	}

	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(0.6, -0.1);
	glVertex2f(0.6, 0.1);
	glVertex2f(0.3, 0.1);
	glVertex2f(0.3, -0.1);
	glEnd();
	glPopMatrix();
	
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(0.35,-0.03);
	stringstream sss;
	sss<<"QUIT";
	string Quit = sss.str();
	for(int i =0;i<Quit.length();i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,Quit[i]);
	}

	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(-0.28,0.5);
	stringstream titleStream;
	titleStream<<"THE EMBLEMS!";
	string title = titleStream.str();
	for(int i =0;i<title.length();i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,title[i]);
	}
}

void UnitSetupDisplay()
{
	//currentScene = 2; // MainGameDisplay()
}

void MainGameDisplay()
{
	// Allen Renders Battle Scene
	for (int i = 0; i<unitList1.size(); i++)
	{
		unitList1.at(i)->drawPiece();
	}

	for(int i=0;i<unitList2.size();i++)
	{
		unitList2.at(i)->drawPiece();
	}
	hud(playerNumber);
}

void EndGameDisplay()
{
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(-0.28,0.5);
	stringstream endStat;
	endStat<<"Player "<<playerWinner<< " is the winner!";
	string endGame = endStat.str();
	for(int i =0;i<endGame.length();i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,endGame[i]);
	}
	endStat.str(string());
	float yy=0.2;
	glColor3f(0.5,0.5,0.5);
	if(unitList1.size()==0)
	{
		endStat<<"Player 1's army is empty!!!! ";
		endStat<<"Player 2's remaining army is : ";
		glRasterPos2f(-0.5,yy);
		endGame = endStat.str();
		for(int i =0;i<endGame.length();i++){
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endGame[i]);
		}
		yy=yy-0.1;
		for (int i =0;i<5;i++)
		{
			endStat.str(string());
			endStat<<unitList2.at(i)->toString();
			glRasterPos2f(-0.5,yy);
			 endGame = endStat.str();
			for(int i =0;i<endGame.length();i++){
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endGame[i]);
			}
			yy=yy-0.1;
		}		
	}
	else if(unitList2.size()==0)
	{
		endStat<<"Player 2's army is empty!!!! ";
		endStat<<"Player 1's remaining army is : ";
		glRasterPos2f(-0.5,yy);
		endGame = endStat.str();
		for(int i =0;i<endGame.length();i++){
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endGame[i]);
		}
		yy=yy-0.1;
		for (int i =0;i<5;i++)
		{
			endStat.str(string());
			endStat<<unitList1.at(i)->toString();
			glRasterPos2f(-0.5,yy);
			endGame = endStat.str();
			for(int i =0;i<endGame.length();i++){
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endGame[i]);
			}
			yy=yy-0.1;
		}
	}
	else
	{	
		float yy2=0.2;
		endStat<<"Player 1's remaining army is : ";
		glRasterPos2f(-0.5,yy);
		endGame = endStat.str();
		for(int i =0;i<endGame.length();i++){
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endGame[i]);
		}
		yy=yy-0.1;
		for (int i =0;i<5;i++)
		{	
			endStat.str(string());
			endStat<<unitList1.at(i)->toString();
			glRasterPos2f(-0.5,yy);
			endGame = endStat.str();
			for(int i =0;i<endGame.length();i++){
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endGame[i]);
			}
			yy=yy-0.1;
		}
		endStat.str(string());
		//displaying 2nd player 
		endStat<<"Player 2's remaining army is : ";
		glRasterPos2f(0.3,yy2);
			endGame = endStat.str();
			for(int i =0;i<endGame.length();i++){
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endGame[i]);
		}
		yy2=yy2-0.1;
		for (int i =0;i<5;i++)
		{		
			endStat.str(string());
			endStat<<unitList2.at(i)->toString();
			glRasterPos2f(0.3,yy2);
			endGame = endStat.str();
			for(int i =0;i<endGame.length();i++){
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endGame[i]);
			}
			yy2=yy2-0.1;
		}
	}

	// replay button
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(-0.1, -0.6);
	glVertex2f(-0.1, -0.4);
	glVertex2f(0.25, -0.4);
	glVertex2f(0.25, -0.6);
	glEnd();
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-0.04, -0.53);
	stringstream ss;
	ss << "Replay";
	string play = ss.str();
	for (int i = 0; i<play.length(); i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, play[i]);
	}
}
#pragma mark endregion
void drawOutline()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glColor3f(0.3,0.79,0.12);
		glVertex2f(-unitList1.at(0)->getPosX(), -unitList1.at(0)->getPosX());
		glVertex2f( unitList1.at(0)->getPosX(), -unitList1.at(0)->getPosX());
		glColor3f(0.52,0.34,0.22);
		glVertex2f( unitList1.at(0)->getPosX(),  unitList1.at(0)->getPosX());
		glVertex2f(-unitList1.at(0)->getPosX(),  unitList1.at(0)->getPosX());
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch (currentScene)
	{
	case 0: // main menu
		MainMenuDisplay();
		break;
	case 1:	// set up pieces
		UnitSetupDisplay();
		break;
	case 2: // main gain
		MainGameDisplay();
		break;
	case 3: // end game
		EndGameDisplay();
		break;
	default:
		cout << "Error, unknown scene" << endl;
		break;
	}
	glutSwapBuffers();
	//glFlush();
}

void resizeWindow(int x, int y)
{
	glutReshapeWindow(500,500);

	glMatrixMode(GL_PROJECTION); // set the matrix mode to reset the camera
	glLoadIdentity(); // get the identity matrix
	glViewport(0, 0, 500, 500);	// set up viewport
	//gluPerspective(fieldofview, aspectRatio, nearPlane, farPlane);

	glMatrixMode(GL_MODELVIEW); // bring it back to matrix mode for scaling/rotation/translations
	glLoadIdentity(); // load back the identity matrix JIC
}

void init()
{
	LoadTexture();

	/* set background clear color to black */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/* set current color to white */
	glColor3f(1.0, 0.0, 0.0);

	/* identify the projection matrix that we would like to alter */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* the window will correspond to these world coorinates */
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glViewport(250, 250, 500, 500);
	/* identify the modeling and viewing matrix that can be modified from here on */
	/* we leave the routine in this mode in case we want to move the object around */
	/* or specify the camera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*doing a second view port*////////////////////////////////////////
	/*glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10.0,10.0,-10.0,10.0);*/
}

#endif