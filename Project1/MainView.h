#pragma once

#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "glut.h"
#include <mutex>

int currentScene = 0;
bool isPlayerOneTurn = true;
bool endGame = false;

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
			if ((x > 224) && (x < 274) && (y>226) && (y < 275))
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
	glVertex2f(-0.1, -0.1);
	glVertex2f(0.1, -0.1);
	glVertex2f(0.1, 0.1);
	glVertex2f(-0.1, 0.1);
	glEnd();
	glColor3f(0.0, 0.0, 1.0);
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5);
	glVertex2f(-0.3, -0.5);
	glVertex2f(-0.3, -0.3);
	glVertex2f(-0.5, -0.3);
	glColor3f(0.0, 0.0, 1.0);
	glEnd();
	glPopMatrix();
}

void UnitSetupDisplay()
{
	// Renders screen

	// player one and player two set their pieces
	// gameSetup(); //Look at this method
	if (isPlayerOneTurn)
	{
		cout << "Set up piece" << endl;

		// ask player one to set up
		// after player one finishes set up
		isPlayerOneTurn = false;
	}
	else
	{
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