// Jordan Nguyen and Allen Hsia start

#include "Main.h"

int main(int argc, char* argv[])
{
	//masterP.toString();
	/* create a window, position it, and name it */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//GLUT_SINGLE);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("basics");
	
	/* create a callback routine for (re-)display */
	glutIdleFunc(speechWait);
	glutDisplayFunc(display);
	glutMotionFunc(motion);
	glutMouseFunc(MouseButton);
	/* init some states */
	init();

	// runs the game in a separate thread from the OpenGL GUI
	thread controlThread(game);

	/* entering the OpenGL event loop */
	glutMainLoop();
	
	controlThread.join(); // pauses until the control thread finishes

	return EXIT_SUCCESS;
}

#pragma mark region Game listening functions
void listenForPiece()
{
	// listen for location
	string location = getLocation(sapi.listen());
	//bool again = true;
	//while(again)
	//{
		while (location.compare("ERROR") == 0) // while invalid location
		{
			cout << "Invalid location. Please repeat your location" << endl;
			location = getLocation(sapi.listen());
		}
		//if(isPieceAtLocation(location))
		//{
			// again = false;
		//}
		//else
		//{
			//cout << "No piece at location. Please repeat a location" << endl;
			//again = true;
			// location = getLocation(location);
		//}
	//}
		sapi.pieceLocation = location;
}

void listenForCommand()
{
	// listen for command
	int command = getCommand(sapi.listen());
	while(command == -1) // while command is invalid
	{
		cout << "Invalid command. Please repeat your command" << endl;
		command = getCommand(sapi.listen());
	}
	sapi.currentCommand = command;
}

void listenForActionLocation()
{
	char* heard = sapi.listen();
	// while (heard != validlocation)
	// {
	//		heard = listen();
	//      if(location within piece.range)
	//			able to perform action
	//		else, choose another location
	// }
	// actionLocation = heard;
}

string getLocation(char* command)
{
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (sapi.locations[i][j].compare(command) == 0)
			{
				// location found, return it
				return sapi.locations[i][j];
			}
		}
	}
	return "ERROR"; // invalid location
}

int getCommand(char* command)
{
	int numberOfCommands = sapi.commandList.size();//sizeof(sapi.commandList) / sizeof(string);
	for (int i = 0; i < numberOfCommands; i++)
	{
		if (sapi.commandList.at(i).compare(command) == 0)
		{
			return i; // index of command, same as Command enum
		}
	}
	return -1; // invalid command
}
#pragma mark endregion

#pragma mark region Setup
void gameSetup()
{
	cout << "\nSetting up game parameters" << endl;
	// set up options/settings if time permits us to add functionality	
	playerSetup();
	cout << "Game set up complete" << endl;
	system("PAUSE");
}

void playerSetup()
{
	// set player pieces in their correct places
	if (isPlayerOneTurn) // player 1's turn to set his/her pieces
	{
		cout << "Player One, set pieces" << endl;
		system("PAUSE");
		isPlayerOneTurn = !isPlayerOneTurn;
		playerSetup();
	}
	else // player 2's turn to set his/her pieces
	{
		cout << "Player Two, set pieces" << endl;
		system("PAUSE");
		isPlayerOneTurn = !isPlayerOneTurn;
	}
}
#pragma mark endregion

// should run on separate thread from display
void game()
{
	// continue running this loop while the game lasts
	while (!endGame)
	{
		switch (currentScene)
		{
		case 0: // main menu, do nothing
			break;
		case 1: // set up pieces
			break;
		case 2: // main game
			MainGameControl();
		default: // unknown scene, do nothing (display should display error message)
			break;
		}
	}
}

void MainGameControl()
{
	if (isPlayerOneTurn)
	{
		cout << "\nPlayer One's Turn" << endl;
		cout << "Player One, say location" << endl;
		system("PAUSE"); // listenForPiece();
		cout << "Player One, say command" << endl;
		listenForCommand();
		cout << "Player One, say location" << endl;
		system("PAUSE"); // listenForActionLocation();
	}
	else // player's two turn
	{
		cout << "\nPlayer Two's Turn" << endl;
		cout << "Player Two, say location" << endl;
		system("PAUSE"); // listenForPiece();
		cout << "Player Two, say command" << endl;
		listenForCommand();
		cout << "Player Two, say location" << endl;
		system("Pause"); // listenForActionLocation();
		cout << "\nPerforming action" << endl;
	}

	cout << "\nPerforming action" << endl;
	performAction();

	isPlayerOneTurn = !isPlayerOneTurn;

	// check win game conditions, if
	//endGame = true; // change current scene
}

void performAction()
{
	switch (sapi.currentCommand)
	{
	case sapi.Hello:
		sapi.Say("Hello User");
		cout << "Hello User" << endl;
		break;
	case sapi.Goodbye:
		sapi.Say("Goodbye User");
		cout << "Goodbye User" << endl;
		endGame = true;
		break;
	case sapi.Attack:
		sapi.Say("Attacking Piece");
		cout << sapi.pieceLocation << " attacking opponent " << sapi.actionLocation << endl;
		//if(attackedPiece == defeated)
		//{
		// if the king/commander is defeated, or if the king/commander is the last one standing
		//if(attackedPiece == king/commander || otherPlayer'sNumberPieces == 1)
		//{
		//endGame = true;
		//isPlayerOneWinner = isPlayerOneTurn;
		//}
		//}
		break;
	case sapi.Group:
		sapi.Say("Grouping Together");
		cout << "grouping piece " << sapi.pieceLocation << " together with group " << sapi.actionLocation << endl;
		break;
	case sapi.Move:
		// if(move to enemy space) currentCommand = Attack; performAction(); //autoattack;
		// else if(move to friendly space) currentCommand = Group; performAction(); // autogroup;
		// else: move unit to location
		sapi.Say("Moving Piece");
		cout << "moving " << sapi.pieceLocation << " to location" << sapi.actionLocation << endl;
		break;
	case sapi.Heal:
		sapi.Say("Healing Piece");
		cout << sapi.pieceLocation << " healing piece " << sapi.actionLocation << endl;
		break;
	case sapi.King:

		break;
	default:
		cout << "unknown command" << endl;
		break;
	}
}

