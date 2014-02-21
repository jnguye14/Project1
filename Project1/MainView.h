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
				if ((x > 325) && (x < 400) && (y>275) && (y < 330))
				{
					exit(0);
				}
				if ((x > 100) && (x < 175) && (y>275) && (y < 330))
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
				if ((x > 210) && (x < 260) && (y>400) && (y < 465))
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

// float values with respect to gl ortho viewport
// (x,y) = LOWER left corner of square
// w = width
// h = height
// texture = GLuint indicating which texture to use
void drawRect(float x, float y, float w, float h, GLuint texture)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x, y + h);
	glTexCoord2f(1.0f, 0.0f);
	glVertex2f(x + w, y + h);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x + w, y);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2f(x, y + h);
	glTexCoord2f(1.0f, 1.0f);
	glVertex2f(x + w, y);
	glTexCoord2f(0.0f, 1.0f);
	glVertex2f(x, y);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}
void hud(int player)
{
	glColor3f(1.0,1.0,1.0);
	stringstream ss;
	if(isPlayerOneTurn)
	{
		drawRect(-0.3f,-0.5f,0.5f,0.9f,turnTexture1);
	}
	else
	{
		drawRect(-0.3f,-0.5f,0.5f,0.9f,turnTexture2);
	}
	ss.str(string());
	if(selectedUnit){
		glColor3f(1.0,0.0,0.0);
		if (selectedUnit) ss << "Unit: " << selectedUnit->toString();
		float xx=-0.9;
		string stats = ss.str();
		glRasterPos2f(xx,0.7);
		for(int i =0;i<stats.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,stats[i]);
		}
		ss.str(string());
		if (selectedUnit) ss << "Attack damage: " << selectedUnit->getAttackDamage();
		glRasterPos2f(xx,0.3);
		stats = ss.str();
		for(int i =0;i<stats.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,stats[i]);
		}
		ss.str(string());
		if (selectedUnit) ss << "Health: " << selectedUnit->getHealth();
		glRasterPos2f(xx,-0.1);
		stats = ss.str();
		for(int i =0;i<stats.length();i++){
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,stats[i]);
		}
	}
}

#pragma mark region Game Screens
void MainMenuDisplay()
{
	// draw play and quit buttons
	drawRect(-0.6f, -0.1f, 0.3f, 0.2f, playTexture);
	drawRect(0.3f, -0.1f, 0.3f, 0.2f, quitTexture);

	drawRect(-0.28f,0.5f,0.5f,0.5f, titleTexture);
	glColor3f(1.0,1.0,1.0);
}

void UnitSetupDisplay()
{
	//currentScene = 2; // MainGameDisplay()
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(-0.28, 0.5);
	stringstream loadingText;
	loadingText << "Loading . . .";
	string title = loadingText.str();
	for (int i = 0; i<title.length(); i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, title[i]);
	}
	glutSwapBuffers();
	Sleep(1000);
}

//*
void drawGrid()
{
	glLineWidth(2);
	glColor3f(1.0f, 1.0f, 1.0f);

	glBegin(GL_LINES);
	for (float i = -0.9f; i <= 0.95f; i += 0.1f)
	{
		// draw horizontal lines
		glVertex2f(-0.9f, i);
		glVertex2f(0.9f, i);

		// draw vertical line
		glVertex2f(i, -0.9f);
		glVertex2f(i, 0.9f);
	}
	glEnd();
}//*/

void MainGameDisplay()
{
	drawGrid();

	// Allen Renders Battle Scene
	for (int i = 0; i<unitList1.size(); i++)
	{
		unitList1.at(i)->drawPiece();
	}

	for(int i=0;i<unitList2.size();i++)
	{
		unitList2.at(i)->drawPiece();
	}
	//hud(playerNumber);
}

void EndGameDisplay()
{
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(-0.28,0.5);
	stringstream endStat;
	string endGame;
	float yy=0.2;
	glColor3f(0.5,0.5,0.5);
	if(unitList1.size()==0)
	{
		drawRect(-0.28f,0.5f,0.7f,0.3f,playWinTexture2);
		endStat<<"Player 1's army is empty!!!! ";
		endStat<<"Player 2's remaining army is : ";
		glRasterPos2f(-0.5,yy);
		endGame = endStat.str();
		for(int i =0;i<endGame.length();i++){
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endGame[i]);
		}
		yy=yy-0.1;
		for (int i =0;i<unitList2.size();i++)
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
		drawRect(-0.28f,0.5f,0.7f,0.3f,playWinTexture1);
		endStat<<"Player 2's army is empty!!!! ";
		endStat<<"Player 1's remaining army is : ";
		glRasterPos2f(-0.5,yy);
		endGame = endStat.str();
		for(int i =0;i<endGame.length();i++){
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endGame[i]);
		}
		yy=yy-0.1;
		for (int i =0;i<unitList1.size();i++)
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
		drawRect(-0.28f,0.5f,0.7f,0.3f,itIsADrawTexture);
		float yy2=0.2;
		glRasterPos2f(-0.5,yy);
		endStat<<"Player 1's remaining army is : ";
		endGame = endStat.str();
		for(int i =0;i<endGame.length();i++){
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endGame[i]);
		}
		yy=yy-0.1;
		for (int i =0;i<unitList1.size();i++)
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
		for (int i =0;i<unitList2.size();i++)
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
	//replay button
	glPushMatrix();
	drawRect(-0.15f,-0.55f,0.2f,0.2f,replayTexture);
	glPopMatrix();
}
#pragma mark endregion

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	switch (currentScene)
	{
	case 0: // main menu
		glViewport(0,0,500,600);
		MainMenuDisplay();
		break;
	case 1:	// set up pieces
		glViewport(0,0,500,600);
		UnitSetupDisplay();
		break;
	case 2: // main gain
		glViewport(0,500,500,100);
		hud(playerNumber);
		glViewport(0,0,500,500);
		MainGameDisplay();
		break;
	case 3: // end game
		glViewport(0,0,500,600);
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
	glutReshapeWindow(500,600);

	glMatrixMode(GL_PROJECTION); // set the matrix mode to reset the camera
	glLoadIdentity(); // get the identity matrix
	//glViewport(0, 0, 500, 500);	// set up viewport
	//gluPerspective(fieldofview, aspectRatio, nearPlane, farPlane);
	
	glMatrixMode(GL_MODELVIEW); // bring it back to matrix mode for scaling/rotation/translations
	glLoadIdentity(); // load back the identity matrix JIC
}

void init()
{
	LoadGameTextures();
	glEnable(GL_BLEND); // For blending alpha chanels
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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