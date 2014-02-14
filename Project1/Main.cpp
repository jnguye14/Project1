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
	glutReshapeFunc(resizeWindow);
	glutMotionFunc(motion);
	glutMouseFunc(MouseButton);
	glutKeyboardFunc(movement);

//	drawOutline();
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
	int numberOfCommands = sapi.commandList.size();
	for (int i = 0; i < numberOfCommands; i++)
	{
		// for debugging
		cout << "Heard: " << command << "; Checking With: " << sapi.commandList.at(i) << endl;
		
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
		//system("PAUSE");
		isPlayerOneTurn = !isPlayerOneTurn;

		// create new pieces
		Commander* commander = new Commander(1);
		Heavy* heavy = new Heavy(1);
		Medic* medic = new Medic(1);
		//Scout* scout = new Scout(1);
		Sniper* sniper = new Sniper(1);
		Soldier* soldier = new Soldier(1);

		unitList1.clear();
		unitList1.push_back(commander);
		unitList1.push_back(heavy);
		unitList1.push_back(medic);
		unitList1.push_back(soldier);
		unitList1.push_back(sniper);
		//unitList1.push_back(scout);

		for (int i = 0; i<unitList1.size(); i++)
		{
			unitList1.at(i)->texture = texture;
		}

		playerSetup();
	}
	else // player 2's turn to set his/her pieces
	{
		cout << "Player Two, set pieces" << endl;
		//system("PAUSE");
		isPlayerOneTurn = !isPlayerOneTurn;

		// create new pieces
		Commander* commander = new Commander(2);
		Heavy* heavy = new Heavy(2);
		Medic* medic = new Medic(2);
		//Scout* scout = new Scout(2);
		Sniper* sniper = new Sniper(2);
		Soldier* soldier = new Soldier(2);

		unitList2.clear();
		unitList2.push_back(commander);
		unitList2.push_back(heavy);
		unitList2.push_back(medic);
		unitList2.push_back(soldier);
		unitList2.push_back(sniper);
		//unitList2.push_back(scout);

		for (int i = 0; i<unitList2.size(); i++)
		{
			unitList2.at(i)->texture = texture_1;
		}

		currentScene = 2;
	}
}
#pragma mark endregion

// should run on separate thread from display
void game()
{
	sapi.Say("Voice Combattants : The Emblem. A game made by Allen Hsia and Jordan Nguyen. Please press play to start.");

	// continue running this loop while the game lasts
	while (!endGame)
	{
		switch (currentScene)
		{
		case 0: // main menu, do nothing
			break;
		case 1: // set up pieces
			if (!isSet)
			{
				playerSetup();
			}
			break;
		case 2: // main game
			MainGameControl();
			break;
		case 3: // end game, do nothing
			break;
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
		//cout << "Player One, say location" << endl;
		//system("PAUSE"); // listenForPiece();
		cout << "Player One, say command" << endl;
		listenForCommand();
		//cout << "Player One, say location" << endl;
		//system("PAUSE"); // listenForActionLocation();
	}
	else // player's two turn
	{
		cout << "\nPlayer Two's Turn" << endl;
		//cout << "Player Two, say location" << endl;
		//system("PAUSE"); // listenForPiece();
		cout << "Player Two, say command" << endl;
		listenForCommand();
		//cout << "Player Two, say location" << endl;
		//system("Pause"); // listenForActionLocation();
		//cout << "\nPerforming action" << endl;
	}

	cout << "\nPerforming action" << endl;
	performAction();

	isPlayerOneTurn = !isPlayerOneTurn;
	if (selectedUnit != NULL)
	{
		selectedUnit->unselect();
		selectedUnit = NULL;
	}
}

void performAction()
{
	if (selectedUnit == NULL)
	{
		sapi.Say("No units selected for action.");
		return;
	}

	switch (sapi.currentCommand)
	{
	case sapi.Hello:
		sapi.Say("Hello User");
		cout << "Hello User" << endl;
		break;
	case sapi.Goodbye:
		sapi.Say("Goodbye User");
		cout << "Goodbye User" << endl;
		currentScene = 3;
		// disable restart?
		endGame = true;
		break;
	case sapi.Attack:
		sapi.Say("Attacking Piece");
		//cout << sapi.pieceLocation << " attacking opponent " << sapi.actionLocation << endl;

		if (isPlayerOneTurn) // player one attacking player two
		{
			int n = -1;
			for (int i = 0; i < unitList2.size(); i++)
			{
				if (checkPiece(selectedUnit, unitList2.at(i)))
				{
					unitList2.at(i)->isAttacked( selectedUnit->getAttackDamage());
					n = i;
					break;
				}
			}
			if (n != -1)
			{
				if (unitList2.at(n)->getHealth() <= 0)
				{
					unitList2.erase(unitList2.begin() + n);
					if (n == 0 || unitList2.size() == 0)
					{
						currentScene = 3;
						playerWinner = 1;
					}
				}
			}
		}
		else // player two attacking player one
		{
			int n = -1;
			for (int i = 0; i < unitList1.size(); i++)
			{
				if (checkPiece(selectedUnit, unitList1.at(i)))
				{
					unitList1.at(i)->isAttacked( selectedUnit->getAttackDamage());
					break;
				}
			}
			if (n != -1)
			{
				if (unitList1.at(n)->getHealth() <= 0)
				{
					unitList1.erase(unitList1.begin() + n);
					if (n == 0 || unitList1.size() == 0)
					{
						currentScene = 3;
						playerWinner = 2;
					}
				}
			}
		}
		break;
	case sapi.Group:
		sapi.Say("Grouping Together");
		cout << "grouping piece " << sapi.pieceLocation << " together with group " << sapi.actionLocation << endl;
		break;
	case sapi.Heal:
		sapi.Say("Healing Piece");
		cout << sapi.pieceLocation << " healing piece " << sapi.actionLocation << endl;
		break;
	case sapi.King:
		break;

	// TODO: error checking so you won't move on top of pieces
	case sapi.MoveU:
		if (selectedUnit != NULL)
		{
			selectedUnit->moveU();
		}
		break;
	case sapi.MoveD:
		if (selectedUnit != NULL)
		{
			selectedUnit->moveD();
		}
		break;
	case sapi.MoveL:
		if (selectedUnit != NULL)
		{
			selectedUnit->moveL();
		}
		break;
	case sapi.MoveR:
		if (selectedUnit != NULL)
		{
			selectedUnit->moveR();
		}
		break;
	default:
		cout << "unknown command" << endl;
		break;
	}
}

//change unit range to float
//make everyone's range in their separate .h files to 0.1
//set sniper to 0.3
bool checkPiece(MasterPiece* unit, MasterPiece* target)
{
	float minX = unit->getPosX() - unit->getAttackRange();
	float maxX = unit->getPosX() + unit->getAttackRange();
	float minY = unit->getPosY() - unit->getAttackRange();
	float maxY = unit->getPosY() + unit->getAttackRange();
	float TargetX = target->getPosX();
	float TargetY = target->getPosY();

	if (TargetX > minX && TargetX < maxX && TargetY - 0.2f > minY && TargetY - 0.2f < maxY) // north
	{
		return true;
	}
	if (TargetX + 0.2f > minX && TargetX + 0.2f < maxX && TargetY > minY && TargetY < maxY) // west
	{
		return true;
	}
	if (TargetX > minX && TargetX < maxX && TargetY + 0.2f > minY && TargetY + 0.2f < maxY) // south
	{
		return true;
	}
	if (TargetX - 0.2f > minX && TargetX - 0.2f < maxX && TargetY > minY && TargetY < maxY) // east
	{
		return true;
	}
	return false;
}
