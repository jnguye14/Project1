// Jordan Nguyen and Allen Hsia start
// example code taken from the microsoft site:
// http://msdn.microsoft.com/en-us/library/ms720163(v=vs.85).aspx
// and also from Elasticboy at
// http://stackoverflow.com/questions/16547349/sapi-speech-to-text-example
// September 28, 2013

#include "Main.h"

void MouseButton(int button, int state, int x, int y)
{
  // Respond to mouse button presses.
  // If button1 pressed, mark this state so we know in motion function.
	if(button==GLUT_LEFT_BUTTON)
	{
		if(state==GLUT_UP)
		{
		//printf("(%d, %d)\n",x, y);
			if((x>224)&&(x<274)&&(y>226)&&(y<275))
			{
				currentScene=1;
				glutPostRedisplay();
			}
		printf("%s","pressed button");
		}
	}
}

void speechWait()
{
	glutPostRedisplay();
}
void motion(int x, int y)
{
	printf("(%d, %d)\n",x, y);
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
	default:
		cout << "Error, unknown scene" << endl;
		break;
	}
	glutSwapBuffers();
	//glFlush();
}

#pragma mark region Game Screens
void MainMenuDisplay()
{
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2f(-0.1,-0.1);
	glVertex2f(0.1,-0.1);
	glVertex2f(0.1,0.1);
	glVertex2f(-0.1,0.1);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2f(-0.5,-0.5);
	glVertex2f(-0.3,-0.5);
	glVertex2f(-0.3,-0.3);
	glVertex2f(-0.5,-0.3);
	glColor3f(0.0,0.0,1.0);
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
		cout<<"Set up piece"<<endl;
				masterP2.posX=400;
		masterP2.toString();
		masterP.toString();
		cout<<"Pause"<<endl;

		// ask player one to set up
		// after player one finishes set up
		isPlayerOneTurn = false;
	}
	else
	{
		cout<<"Set up piece"<<endl;

		cout<<"Pause"<<endl;

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
	cout << "Entering main game command loop" << endl;
	game(); // player one and player two alternate turns until game ends

	// at game over:
	if (endGame)
	{
		cout << "\nEnd of Game Demo\n" << endl;
		//currentScene = 3;
	}
}

void EndGameDisplay()
{
	printf("%s","YOU ARE NOW IN THE END GAME\n\n\n\nEVERYONE IS A WINNAR!");
	//show stats/winner
	// replay button
}
#pragma mark endregion

void pieceInit()
{
	//create arrays
	//initalize position for the 2 arrays
	//use this for the position set up
}

void init()
{
	cout << "Initializing SAPI interface" << endl;
	if (!SAPIinit())
	{
		cout << "Error: Failed to initialize SAPI interface. Exiting program." << endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}
	cout << "Initialization complete. " << endl;

	cout << "\nPlease start Windows Recognition if you haven't yet done so." << endl;

	/* set background clear color to black */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	/* set current color to white */
	glColor3f(1.0, 0.0, 0.0);

	/* identify the projection matrix that we would like to alter */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* the window will correspond to these world coorinates */
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
	glViewport(250,250,500,500);
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
	
	/* entering the event loop */
	glutMainLoop();
	SAPIcleanup();
	return EXIT_SUCCESS;
}


/* Initialize states -- called before */
#pragma mark region SAPI Speech-to-Text JNN
bool SAPIinit()
{
	// Initialize COM library
	if (FAILED(::CoInitialize(NULL))) // difference between NULL and nullptr?
	{
		cout << "Error: unable to initialize COM library." << endl;
		return false;
	}

	// Create SAPI's voice (not needed)
	hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **) &pVoice);
	check_result(hr);

	// Create a voice recognizer:
	// http://social.msdn.microsoft.com/Forums/windowsdesktop/en-US/f2f213d6-d801-49a1-b7dd-4139a357c517/how-to-disable-windows-7-speech-recognition-commands?forum=windowsgeneraldevelopmentissues
	// CLSID_SpSharedRecognizer = recognizer shared with windows
	// CLSID_SpInprocRecognizer = in-process (i.e. private) recognizer
	//hr = CoCreateInstance(CLSID_SpInprocRecognizer, nullptr, CLSCTX_ALL, IID_ISpRecognizer, reinterpret_cast<void**>(&recognizer));
	hr = CoCreateInstance(CLSID_SpSharedRecognizer, nullptr, CLSCTX_ALL, IID_ISpRecognizer, reinterpret_cast<void**>(&recognizer));
	check_result(hr);

	// Create a recognition context from voice recognizer
	hr = recognizer->CreateRecoContext(&recoContext);
	check_result(hr);

	// Disable context so grammar can be added
	hr = recoContext->Pause(0);
	check_result(hr);

	cout << "Adding commands to grammar" << endl;
	if (!initGrammar())
	{
		// unable to add commands to recognition context's grammar
		cout << "Error: Problem adding commands." << endl;
		return false;
	}

	// JNN: not sure, double check!
	hr = recoContext->SetNotifyWin32Event();
	check_result(hr);

	// Create event handlers
	handles[0] = recoContext->GetNotifyEventHandle();
	if (handles[0] == INVALID_HANDLE_VALUE)
	{
		check_result(E_FAIL);
	}

	// Create interest? ...JNN: double check
	ULONGLONG interest; // interest?
	interest = SPFEI(SPEI_RECOGNITION);
	hr = recoContext->SetInterest(interest, interest);
	check_result(hr);

	// Activate Grammar
	hr = recoGrammar->SetRuleState(ruleName1, 0, SPRS_ACTIVE);
	check_result(hr);


	// more calls to set up audio input
	//hr = CoCreateInstance(CLSID_SpMMAudioIn, NULL, CLSCTX_ALL, IID_ISpAudio, (void **) &pMMSysAudio);
	//check_result(hr);
	//pMMSysAudio->SetDeviceId();


	/* //hr = recognizer->SetInput(pInputStream, true);
	hr = pAudio->SetState(SPAS_STOP, 0); // to stop audio input
	check_result(hr);
	hr = pAudio->SetState(SPAS_RUN, 0); // enable audio
	check_result(hr);
	hr = pAudio->SetState(SPAS_CLOSED, 0); // to stop and close audio input
	check_result(hr);
	ULONG* volume;
	hr = pAudio->GetVolumeLevel(volume); // from 0 to 10000
	check_result(hr);
	hr = recognizer->SetInput(pAudio, true);
	check_result(hr);
	// also SPAS_PAUSE, but I don't see a reason for this
	//*/

	//* // JNN: two additional calls due to recognizer no longer being shared with windows
	// manually activate audio stream from microphone/line in
	hr = recoGrammar->SetGrammarState(SPGS_ENABLED);
	check_result(hr);
	hr = recoGrammar->SetDictationState(SPRS_ACTIVE);
	check_result(hr);
	//*/


	// Enable context, grammars have been set
	hr = recoContext->Resume(0);
	check_result(hr);

	return true;
}

bool initGrammar()
{
	SPSTATEHANDLE sate;

	// Create recognition grammar
	hr = recoContext->CreateGrammar(grammarId, &recoGrammar);
	check_result(hr);

	// set language
	//WORD langId = MAKELANGID(LANG_FRENCH, SUBLANG_FRENCH); // doesn't support french apparently
	//WORD langId = MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_US); // doesn't support spanish either
	WORD langId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US); // supports english though
	try
	{
		hr = recoGrammar->ResetGrammar(langId);
		check_result(hr);
	}
	catch (exception ex)
	{
		langId = GetUserDefaultUILanguage();
		hr = recoGrammar->ResetGrammar(langId);
		check_result(hr);
	}

	// Create rules
	hr = recoGrammar->GetRule(ruleName1, 0, SPRAF_TopLevel | SPRAF_Active, true, &sate);
	check_result(hr);

	// Add commands
	int numberOfCommands = sizeof(commandList) / sizeof(string);
	for (int i = 0; i < numberOfCommands; i++)
	{
		// add command to recognition grammar
		const wstring commandWstr = wstring(commandList[i].begin(), commandList[i].end());
		hr = recoGrammar->AddWordTransition(sate, NULL, commandWstr.c_str(), L" ", SPWT_LEXICAL, 1, nullptr);
		check_result(hr);

		// Commit changes
		hr = recoGrammar->Commit(0);
		check_result(hr);
	}

	// add locations
	makeLocations();
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			// add location to recognition grammar
			const wstring commandWstr = wstring(locations[i][j].begin(), locations[i][j].end());
			hr = recoGrammar->AddWordTransition(sate, NULL, commandWstr.c_str(), L" ", SPWT_LEXICAL, 1, nullptr);
			check_result(hr);

			// Commit changes
			hr = recoGrammar->Commit(0);
			check_result(hr);
		}
	}

	return true;
}

void SAPIcleanup()
{
	if (pVoice != nullptr)
	{
		pVoice->Release();
		pVoice = nullptr;
		cout << "Released SAPI's voice" << endl;
	}
	if (recognizer != nullptr)
	{
		recognizer->Release();
		recognizer = nullptr;
		cout << "Released SAPI's recognizer" << endl;
	}
	if (recoContext != nullptr)
	{
		recoContext->Release();
		recoContext = nullptr;
		cout << "Released SAPI's recognition context" << endl;
	}
	if (recoGrammar != nullptr)
	{
		recoGrammar->Release();
		recoGrammar = nullptr;
		cout << "Released SAPI's recognition grammar" << endl;
	}
	::CoUninitialize();
}

char* listen()
{
	// Wait for SAPI to recognize a voice command
	WaitForMultipleObjects(1, handles, FALSE, INFINITE); // waits here in an infinite loop
	const ULONG maxEvents = 10;
	SPEVENT events[maxEvents];

	ULONG eventCount;
	hr = recoContext->GetEvents(maxEvents, events, &eventCount);
	// Warning hr equal S_FALSE if everything is OK, but eventCount < requestedEventCount
	if (!(hr == S_OK || hr == S_FALSE))
	{
		check_result(hr);
	}

	// reinterprets the event from the handle into a recognizable result
	ISpRecoResult* recoResult;
	recoResult = reinterpret_cast<ISpRecoResult*>(events[0].lParam);

	// get the recognition result as a wchar_t*
	wchar_t* text;
	hr = recoResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, FALSE, &text, NULL);
	check_result(hr);

	// convert wchar_t* to char* (which is more meaningul to me)
	size_t size = (wcslen(text) + 1); // +1 for '\0'
	size_t convertedChars = 0;
	char* nstring = new char[size];
	wcstombs_s(&convertedChars, nstring, size, text, _TRUNCATE);
	
	// get rid of wchar_t* since it was a temporary variable
	CoTaskMemFree(text);

	// return what it heard as a char*
	return nstring;
}

void check_result(const HRESULT& result)
{
	if (result == S_OK)
	{
		return;
	}

	string message;
	switch (result)
	{
	case E_ABORT:
		message = "Error, operation is aborting.";
		break;
	case E_ACCESSDENIED:
		message = "Acces Denied.";
		break;
	case E_FAIL:
		message = "Failure.";
		break;
	case E_HANDLE:
		message = "Handle is not valid.";
		break;
	case E_INVALIDARG:
		message = "One or more arguments are invalids.";
		break;
	case E_NOINTERFACE:
		message = "Interface does not exist.";
		break;
	case E_NOTIMPL:
		message = "Not implemented method.";
		break;
	case E_OUTOFMEMORY:
		message = "Out of memory.";
		break;
	case E_POINTER:
		message = "Invalid pointer.";
		break;
	case E_UNEXPECTED:
		message = "Unexpecter error.";
		break;
	default:
		message = "Unknown : " + to_string(result);
		break;
	}

	throw exception(message.c_str());
}
#pragma mark endregion

#pragma mark region Game listening functions
void listenForPiece()
{
	// listen for location
	string location = getLocation(listen());
	//bool again = true;
	//while(again)
	//{
		while (location.compare("ERROR") == 0) // while invalid location
		{
			cout << "Invalid location. Please repeat your location" << endl;
			location = getLocation(listen());
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
	pieceLocation = location;
}

void listenForCommand()
{
	// listen for command
	int command = getCommand(listen());
	while(command == -1) // while command is invalid
	{
		cout << "Invalid command. Please repeat your command" << endl;
		command = getCommand(listen());
	}
	currentCommand = command;
}

void listenForActionLocation()
{
	char* heard = listen();
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
			if (locations[i][j].compare(command) == 0)
			{
				// location found, return it
				return locations[i][j];
			}
		}
	}
	return "ERROR"; // invalid location
}

int getCommand(char* command)
{
	int numberOfCommands = sizeof(commandList) / sizeof(string);
	for (int i = 0; i < numberOfCommands; i++)
	{
		if (commandList[i].compare(command) == 0)
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

#pragma mark region Location functions
void makeLocations()
{
	// create all possible location strings for SAPI to recognize
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			locations[i][j] += ('A' + i);
			locations[i][j] += ('0' + j);
		}
	}

	/* // JNN: printf to check if location strings were made correctly
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 10; j++)
		{
		cout << locations[i][j] << " ";
		}
		cout << endl;
	}
	//*/

	/* // JNN: alternative printf that performs the same task
	cout << endl;
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << getLetter(locations[i][j]) << getNumber(locations[i][j]) << " ";
		}
		cout << endl;
	}
	//*/
}

char getLetter(string location)
{
	return location.at(0);
}

int getNumber(string location)
{
	return (location.at(1) - 48);
}
#pragma mark endregion

void game()
{
	// main game loop
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
	//endGame = true;
}

void performAction()
{
	switch (currentCommand)
	{
	case Hello:
		hr = pVoice->Speak(L"<pitch middle = '+10'/>Hello User", 0, NULL);
		cout << "Hello User" << endl;
		break;
	case Goodbye:
		hr = pVoice->Speak(L"<pitch middle = '+10'/>Goodbye User", 0, NULL);
		cout << "Goodbye User" << endl;
		endGame = true;
		break;
	case Attack:
		hr = pVoice->Speak(L"<pitch middle = '+10'/>Attacking Piece", 0, NULL);
		cout << pieceLocation << " attacking opponent " << actionLocation << endl;
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
	case Group:
		hr = pVoice->Speak(L"<pitch middle = '+10'/>Grouping Together", 0, NULL);
		cout << "grouping piece " << pieceLocation << " together with group " << actionLocation << endl;
		break;
	case Move:
		// if(move to enemy space) currentCommand = Attack; performAction(); //autoattack;
		// else if(move to friendly space) currentCommand = Group; performAction(); // autogroup;
		// else: move unit to location
		hr = pVoice->Speak(L"<pitch middle = '+10'/>Moving Piece", 0, NULL);
		cout << "moving " << pieceLocation << " to location" << actionLocation << endl;
		break;
	case Heal:
		hr = pVoice->Speak(L"<pitch middle = '+10'/>Healing Piece", 0, NULL);
		cout << pieceLocation << " healing piece " << actionLocation << endl;
		break;
	case King:

		break;
	default:
		cout << "unknown command" << endl;
		break;
	}
}

