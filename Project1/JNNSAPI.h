#pragma once

// example code taken from the microsoft site:
// http://msdn.microsoft.com/en-us/library/ms720163(v=vs.85).aspx
// and also from Elasticboy at
// http://stackoverflow.com/questions/16547349/sapi-speech-to-text-example
// September 28, 2013

#ifndef JNNSAPI_H
#define JNNSAPI_H

//#include <stdafx.h>
// sphelper.h deprecated GetVersionExA (line 1319)
//   for: SpGetDefaultTokenFromCategoryId()
//#include <sphelper.h>

#include <sapi.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class JNNSAPI
{
public:
	// JNN: made global since is used everywhere
	HRESULT hr; // used to test SAPI results
	ISpVoice *pVoice;// = nullptr; // voice that speaks to you (not needed)
private:
	ISpRecognizer* recognizer;// = nullptr; // voice recognizer
	ISpRecoContext* recoContext;// = nullptr; // recognition context
	ISpRecoGrammar* recoGrammar;// = nullptr; // grammar recognizer, needed for each grammar, rule, or word
	HANDLE handles[1]; // event handlers, we really only need one

	// Audio stream
	//ISpStream* pInputStream;
	//ISpAudio* pAudio;
	//ISpMMSysAudio* pMMSysAudio;
	//SpMMAudioIn* MMAudioIn;

public:
	vector<string> commandList;
	enum Command
	{
		Hello,
		Goodbye,
		Attack,
		Group,
		Move,
		Heal,
		King
	};
	
	bool saidHello;// = false;

	// 26 letters, ten numbers
	string locations[26][10];

	// location of piece
	string pieceLocation; // current piece

	// last command said as an enum
	int currentCommand;

	// location of action to perform
	string actionLocation;

	JNNSAPI()
	{
		cout << "Initializing SAPI interface" << endl;

		saidHello = false;
		commandList = {
			"yellow",
			"goodbye",
			"attack",
			"group",
			"move",
			"heal",
			"king"
		};

		if (!SAPIinit())
		{
			cout << "Error: Failed to initialize SAPI interface. Exiting program." << endl;
			system("PAUSE");
			exit(EXIT_FAILURE);
		}
		cout << "Initialization complete. " << endl;

		cout << "\nPlease start Windows Recognition if you haven't yet done so." << endl;
	}

	~JNNSAPI()
	{
		SAPIcleanup();
	}

	// JNN: location functions
	void makeLocations();
	char getLetter(string location);
	int getNumber(string location);

	char* listen(); // returns what it heard
	void Say(string phrase);

private:
	// JNN: modified SAPI speech-to-text code
	bool SAPIinit(); // returns true if successful
	bool initGrammar(); // returns true if successful
	void SAPIcleanup(); // releases SAPI stuff
	void check_result(const HRESULT& result);
};

#endif