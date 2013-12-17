#pragma once

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "glut.h"
#include "MasterPiece.h"
#include <mutex>
#include <sstream>
int currentScene = 0;
bool isPlayerOneTurn = true;
bool endGame = false;

MasterPiece masterP;

MasterPiece masterP2;

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
	// Renders screen

	// player one and player two set their pieces
	// gameSetup(); //Look at this method
	if (isPlayerOneTurn)
	{
		cout << "Set up piece" << endl;
		masterP2.posX = 400;
		masterP2.toString();
		masterP.toString();
		cout << "Pause" << endl;

		// ask player one to set up
		// after player one finishes set up
		isPlayerOneTurn = false;
	}
	else
	{
		cout << "Set up piece" << endl;

		cout << "Pause" << endl;

		// ask player two to set up
		// after player two finishes set up
		isPlayerOneTurn = true;
	}
	currentScene = 2; // MainGameDisplay()
}

void MainGameDisplay()
{
	// Allen Renders Battle Scene

	// JNN's stuff
	//cout << "Entering main game command loop" << endl;
	//game(); // player one and player two alternate turns until game ends

	// at game over:
	if (endGame)
	{
		cout << "\nEnd of Game Demo\n" << endl;
		//currentScene = 3;
	}
}

void EndGameDisplay()
{
	printf("%s", "YOU ARE NOW IN THE END GAME\n\n\n\nEVERYONE IS A WINNAR!");
	//show stats/winner
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
	default:
		cout << "Error, unknown scene" << endl;
		break;
	}
	glutSwapBuffers();
	//glFlush();
}

void pieceInit()
{
	//create arrays
	//initalize position for the 2 arrays
	//use this for the position set up
}

void init()
{
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