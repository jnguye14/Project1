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
#include <mutex>
#include <sstream>

int currentScene = 0;
int playerWinner = 0;
bool isPlayerOneTurn = true;
bool endGame = false;

Commander commander;
Heavy heavy;
Medic medic;
Scout scout;
Sniper sniper;
Soldier soldier;

vector <MasterPiece*> unitList1;
vector <MasterPiece*> unitList2;

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
			//printf("(%d, %d)\n",x, y);
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
	//comment out one of them to display the ending for the win condition of one player having all units gone
	// Renders screen
	// player one and player two set their pieces
	// gameSetup(); //Look at this method

	commander.texture = texture;
	unitList1.push_back(&commander);
	unitList1.push_back(&heavy);
	unitList1.push_back(&medic);
	unitList1.push_back(&scout);
	unitList1.push_back(&sniper);
	unitList1.push_back(&soldier);
	for (int i =0;i<6;i++)
	{
		cout<<unitList1.at(i)->toString();
	}
	unitList2.push_back(&commander);
	unitList2.push_back(&heavy);
	unitList2.push_back(&medic);
	unitList2.push_back(&scout);
	unitList2.push_back(&sniper);
	unitList2.push_back(&soldier);
	for (int i =0;i<6;i++)
	{
		cout<<unitList2.at(i)->toString();
	}
	commander.drawPiece();
	//currentScene = 2; // MainGameDisplay()
}

void MainGameDisplay()
{
	// Allen Renders Battle Scene
	
	// JNN's stuff
	//cout << "Entering main game command loop" << endl;
	//game(); // player one and player two alternate turns until game ends
	if(unitList1.size()==0)
	{
		endGame=true;
		playerWinner=2;
	}
	else if(unitList2.size()==0)
	{
		endGame=true;
		playerWinner=1;
	}
	// at game over:
	if (endGame)
	{
		cout << "\nEnd of Game Demo\n" << endl;
		currentScene = 3;
	}
}

void EndGameDisplay()
{
	glColor3f(1.0,1.0,1.0);
	glRasterPos2f(-0.28,0.5);
	stringstream EndText;
	EndText<<"Player "<<playerWinner<< " is the winner!";
	string endGame = EndText.str();
	for(int i =0;i<endGame.length();i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,endGame[i]);
	}

	stringstream endStat;	
	if(unitList1.size()==0)
	{
		endStat<<"Player 1's army is empty ";
		endStat<<"\nPlayer 2's remaining army is : ";
		for (int i =0;i<6;i++)
		{
			endStat<<unitList2.at(i)->toString();
		}		
	}
	else if(unitList2.size()==0)
	{
		endStat<<"Player 2's army is empty";
		endStat<<"\nPlayer 1's remaining army is : ";
		for (int i =0;i<6;i++)
		{
			endStat<<unitList1.at(i)->toString();
		}
	}
	else
	{
		endStat<<"Player 1's remaining army is : ";
		for (int i =0;i<6;i++)
		{
			endStat<<unitList1.at(i)->toString();
		}
		endStat<<"Player 2's remaining army is : ";
		for (int i =0;i<6;i++)
		{
			endStat<<unitList2.at(i)->toString();
		}
	}
	glColor3f(0.5,0.5,0.5);
	glRasterPos2f(-0.5,-0.5);
	string endText = endStat.str();
	for(int i =0;i<endText.length();i++){
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,endText[i]);
	}

	// replay button
}
#pragma mark endregion

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