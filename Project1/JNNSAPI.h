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
private:
	HRESULT hr; // used to test SAPI results
	ISpVoice *pVoice;// = nullptr; // voice that speaks to you (not needed)
	ISpRecognizer* recognizer;// = nullptr; // voice recognizer
	ISpRecoContext* recoContext;// = nullptr; // recognition context
	ISpRecoGrammar* recoGrammar;// = nullptr; // grammar recognizer, needed for each grammar, rule, or word
	HANDLE handles[1]; // event handlers, we really only need one

	// Audio stream
	//ISpStream* pInputStream;
	//ISpMMSysAudio* pMMSysAudio;
	//SpMMAudioIn* MMAudioIn;

public:
	ISpAudio* pAudio;
	vector<string> commandList;
	enum Command
	{
		Hello,
		Goodbye,
		Attack,
		Group,
		Heal,
		King,
		MoveU,
		MoveD,
		MoveL,
		MoveR
	};
	
	// 26 letters, ten numbers
	string locations[26][10];

	// location of piece
	string pieceLocation; // current piece

	// last command said as an enum
	int currentCommand;

	// location of action to perform
	string actionLocation;

	// SAPI Constructor, Calls SAPIInit() which calls initGrammar()
	JNNSAPI()
	{
		cout << "Initializing SAPI interface" << endl;
		commandList.push_back("hello");
		commandList.push_back("I surrender");
		commandList.push_back("attack");
		commandList.push_back("group");
		commandList.push_back("heal");
		commandList.push_back("king");
		commandList.push_back("Move unit up");
		commandList.push_back("Move unit down");
		commandList.push_back("Move unit left");
		commandList.push_back("Move unit right");

		if (!SAPIinit())
		{
			cout << "Error: Failed to initialize SAPI interface. Exiting program." << endl;
			system("PAUSE");
			exit(EXIT_FAILURE);
		}
		cout << "Initialization complete. " << endl;

		cout << "\nPlease start Windows Recognition if you haven't yet done so." << endl;
	}

	// SAPI Clean Up
	~JNNSAPI()
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

	// JNN: location functions
	void makeLocations();
	char getLetter(string location);
	int getNumber(string location);

	void Say(string phrase);
	char* listen(); // returns what it heard

private:
	bool SAPIinit(); // returns true if successful
	bool initGrammar(); // returns true if successful
	void check_result(const HRESULT& result);
};

#endif