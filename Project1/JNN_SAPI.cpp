#include "JNN_SAPI.h"


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
#pragma mark endregion


#pragma mark region SAPI speech-to-text Elasticboy
// This function exits when the word passed as parameter is said by the user
int start_listening(const string& word)
{
	// Create a voice recognizer
	hr = CoCreateInstance(CLSID_SpSharedRecognizer, nullptr, CLSCTX_ALL, IID_ISpRecognizer, reinterpret_cast<void**>(&recognizer));
	check_result(hr);

	// Create a context recognizer
	hr = recognizer->CreateRecoContext(&recoContext);
	check_result(hr);

	// Disable context so grammar can be added
	hr = recoContext->Pause(0);
	check_result(hr);

	// Create grammar recognizer for each grammar, rule, or word
	recoGrammar = init_grammar(recoContext, word);
	ISpRecoGrammar* recoGrammar2 = init_grammar(recoContext, "Goodbye");

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
	hr = recoGrammar2->SetRuleState(ruleName1, 0, SPRS_ACTIVE);
	check_result(hr);

	// Enable context
	hr = recoContext->Resume(0);
	check_result(hr);

	// Wait for SAPI to recognize a voice command
	WaitForMultipleObjects(1, handles, FALSE, INFINITE); // waits here
	get_text(recoContext);

	/*
	if (saidHello)
	{
		cout << "Hello user" << endl;
	}
	else
	{
		cout << "Goodbye user" << endl;
	}//*/

	recoGrammar->Release();
	recoGrammar2->Release();

	return EXIT_SUCCESS;
}

/**
* Create and initialize the Grammar.
* Create a rule for the grammar.
* Add word to the grammar.
*/
ISpRecoGrammar* init_grammar(ISpRecoContext* recoContext, const string& command)
{
	//HRESULT hr;
	SPSTATEHANDLE sate;

	ISpRecoGrammar* recoGrammar;
	hr = recoContext->CreateGrammar(grammarId, &recoGrammar);
	check_result(hr);

	WORD langId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US); // supports english
	//WORD langId = MAKELANGID(LANG_FRENCH, SUBLANG_FRENCH); // doesn't support french apparently
	//WORD langId = MAKELANGID(LANG_SPANISH, SUBLANG_SPANISH_US); // neither does it support spanish
	try
	{
		hr = recoGrammar->ResetGrammar(langId);
		check_result(hr);
	}
	catch (exception ex)
	{
		langId = GetUserDefaultUILanguage();
		hr = recoGrammar->ResetGrammar(langId);
	}

	// Create rules
	hr = recoGrammar->GetRule(ruleName1, 0, SPRAF_TopLevel | SPRAF_Active, true, &sate);
	check_result(hr);

	// Add a word
	const wstring commandWstr = wstring(command.begin(), command.end());
	hr = recoGrammar->AddWordTransition(sate, NULL, commandWstr.c_str(), L" ", SPWT_LEXICAL, 1, nullptr);
	check_result(hr);

	// Commit changes
	hr = recoGrammar->Commit(0);
	check_result(hr);

	return recoGrammar;
}

void get_text(ISpRecoContext* reco_context)
{
	const ULONG maxEvents = 10;
	SPEVENT events[maxEvents];

	ULONG eventCount;
	hr = reco_context->GetEvents(maxEvents, events, &eventCount);

	// Warning hr equal S_FALSE if everything is OK
	// but eventCount < requestedEventCount
	if (!(hr == S_OK || hr == S_FALSE))
	{
		check_result(hr);
	}

	ISpRecoResult* recoResult;
	recoResult = reinterpret_cast<ISpRecoResult*>(events[0].lParam);

	/* // JNN: trying to make SAPI say what I just said
	ULONG ulStreamNum = 1;
	hr = recoResult->SpeakAudio(0, 0, 0, &ulStreamNum);
	if (SUCCEEDED(hr))
	{
	cout << "success" << endl;
	}
	else
	{
	cout << "fail" << endl;
	}//*/

	wchar_t* text;
	hr = recoResult->GetText(SP_GETWHOLEPHRASE, SP_GETWHOLEPHRASE, FALSE, &text, NULL);
	check_result(hr);

	// JNN: convert wchar_t* to char*
	size_t size = (wcslen(text) + 1); // +1 for '\0'
	size_t convertedChars = 0;
	char *nstring = new char[size];
	wcstombs_s(&convertedChars, nstring, size, text, _TRUNCATE);
	//*/

	/*//cout << nstring << endl;
	if (strcmp(nstring, "Hello") == 0)
	{
		saidHello = true;
	}
	else
	{
		saidHello = false;
	}//*/

	CoTaskMemFree(text);
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