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
 *   (done) something shows on screen after command given(from menu options)
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

#include "JNNSAPI.h"
#include "MainView.h"
#include <thread>
#include "MasterPiece.h"
JNNSAPI sapi;

int main(int argc, char* argv []);

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

// JNN: main game controls
void game();
void MainGameControl();
void performAction();
//void doAction(piece unit, int command, string location);
bool checkPiece(MasterPiece* unit, MasterPiece* target);