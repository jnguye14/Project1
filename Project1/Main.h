#pragma once

#include "JNNSAPI.h"
#include "MainView.h"
#include <thread>
#include "MasterPiece.h"
JNNSAPI sapi;

bool endGame = false; // should never be true to keep main game loop going
// Say "Goodbye" to force game to quit

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