#ifndef JNN_SAPI_H
#define JNN_SAPI_H

#pragma once

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

string commandList [] =
{
	"Yello",
	"Goodbye",
	"Attack",
	"Group",
	"Move",
	"Heal"
};

// 26 letters, ten numbers
string locations[26][10];

// JNN: location functions
void makeLocations();
char getLetter(string location);
int getNumber(string location);


// JNN: modified SAPI speech-to-text code
bool SAPIinit(); // returns true if successful
bool initGrammar(); // returns true if successful
void SAPIcleanup(); // releases SAPI stuff
char* listen(); // returns what it heard

// Elasticboy: sample SAPI speech-to-text code
//int start_listening(const std::string& word);
//ISpRecoGrammar* init_grammar(ISpRecoContext* recoContext, const std::string& command);
//void get_text(ISpRecoContext* reco_context);
//void check_result(const HRESULT& result);


#endif