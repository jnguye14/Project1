#pragma once

/* Voice Combattants : The Emblem
 * JNN TODO:
 *   (done) identify commands in command list
 *   (done) make some text appear after giving command
 *   identify locations e.g. "A6"
 *   create command format: "<pieceLocation> <currentCommand> <actionLocation>"
 *
 * Allen TODO:
 *   make GUI: basic start/instruction/end screens
 *   menu options for commands
 *   something shows on screen after command given(from menu options)
 *
 * Later TODO:
 *   create pieces (health/defense, offense, agility, range, currentPosition)
 *     1 commander/king, 1 heavy/queen, 2 medics, 2 scouts/spys, 2 snipers/long-ranged, 8 grunts/soldiers
 *   basic game play (making pieces interact)
 *   set pieces upon start up
 *   end game conditions (win/lose)
 *   Debugging
 *
 * Optional TODO (if time permits):
 *   additional units: engineer, pyro, aerial strikes
 *   special commmander abilities/soldier promotion/other powerups
 *   "Pass," "Surrender," "Leave" group/squad commands
 *   Move diagonally
 *   music/SAPI voice acting?
 *   scoring implementation
 *   special spaces (water/tree/treasure)
 *   story/plot
 *   providing voice inrecognition feedback
 *   turning on and off windows recognition automatically
 *   timers (speed chess)
 *
 * Known bugs:
 *  WaitForMultipleObjects() in infinite loop (holds up other background processes)
 *		such as window drag, minimize, maximize, and exit
 *  listens while not in WaitForMultipleObjects()
 *		luckily only takes in one command thanks to:
        recoResult = reinterpret_cast<ISpRecoResult*>(events[0].lParam);
 */

//#include <stdafx.h>
// sphelper.h deprecated GetVersionExA (line 1319)
//   for: SpGetDefaultTokenFromCategoryId()
//#include <sphelper.h>
#include <sapi.h>
#include <iostream>
#include <string>

using namespace std;

const ULONGLONG grammarId = 0;
const wchar_t *ruleName1 = L"ruleName1";

// JNN: made global since is used everywhere
HRESULT hr; // used to test SAPI results
ISpVoice *pVoice = nullptr; // voice that speaks to you (not needed)
ISpRecognizer* recognizer = nullptr; // voice recognizer
ISpRecoContext* recoContext = nullptr; // recognition context
ISpRecoGrammar* recoGrammar = nullptr; // grammar recognizer, needed for each grammar, rule, or word
HANDLE handles[1]; // event handlers, we really only need one

// Audio stream
//ISpStream* pInputStream;
//ISpAudio* pAudio;
//ISpMMSysAudio* pMMSysAudio;
//SpMMAudioIn* MMAudioIn;


bool saidHello = false;
bool isPlayerOneTurn = true;
bool endGame = false;

enum Command
{
	Hello,
	Goodbye,
	Attack,
	Group,
	Move,
	Heal
};

string commandList[] =
{
	"Yello",
	"Goodbye",
	"Attack",
	"Group",
	"Move",
	"Heal"
};

// 26 letters, ten numbers
string locations [26][10];

// location of piece
string pieceLocation; // current piece

// last command said as an enum
int currentCommand;

// location of action to perform
string actionLocation;


int main(int argc, char* argv []);

// JNN: modified SAPI speech-to-text code
bool SAPIinit(); // returns true if successful
bool initGrammar(); // returns true if successful
void SAPIcleanup(); // releases SAPI stuff
char* listen(); // returns what it heard

// JNN: game listening functions
void listenForPiece();
void listenForCommand();
void listenForActionLocation();
string getLocation(char* command);
bool isPieceAtLocation(string location);
int getCommand(char* command);

// JNN: setup functions
void gameSetup();
void playerSetup();

// JNN: location functions
void makeLocations();
char getLetter(string location);
int getNumber(string location);

// JNN: main game controls
void game();
void performAction();
//void doAction(piece unit, int command, string location);

// Elasticboy: sample SAPI speech-to-text code
int start_listening(const std::string& word);
ISpRecoGrammar* init_grammar(ISpRecoContext* recoContext, const std::string& command);
void get_text(ISpRecoContext* reco_context);
void check_result(const HRESULT& result);