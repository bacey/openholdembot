//******************************************************************************
//
// This file is part of the OpenHoldem project
//    Source code:           https://github.com/OpenHoldem/openholdembot/
//    Forums:                http://www.maxinmontreal.com/forums/index.php
//    Licensed under GPL v3: http://www.gnu.org/licenses/gpl.html
//
//******************************************************************************
//
// Purpose: Very simple user-DLL as a starting-point
//
// Required OpenHoldem version: 12.1.6
//
//******************************************************************************

// Needs to be defined here, before #include "user.h"
// to generate proper export- and inport-definitions
#define USER_DLL

#include "user.h"
//#include <conio.h>
#include <windows.h>
//#include <iostream>
#include <cpr/cpr.h>
#include "OpenHoldemFunctions.h"

using namespace cpr;

//******************************************************************************
//
// Place all your initalizations in the functions below
// DLLOnLoad() amd DLLOnUnLoad() get called by the DLL,
// the other functions get called by OpenHoldem
//
//******************************************************************************

void DLLOnLoad() {
}

void DLLOnUnLoad() {
}

void __stdcall DLLUpdateOnNewFormula() {
}

void __stdcall DLLUpdateOnConnection() {
}

void __stdcall DLLUpdateOnHandreset() {
}

void __stdcall DLLUpdateOnNewRound() {
}

void __stdcall DLLUpdateOnMyTurn() {
}

void __stdcall DLLUpdateOnHeartbeat() {
}

//******************************************************************************
//
// ProcessQuery()
// Handling the lookup of dll$symbols
//
//******************************************************************************

DLL_IMPLEMENTS double __stdcall ProcessQuery(const char* pquery) {
	const double defaultActionCode = 0;

	if (pquery == NULL) {
		return defaultActionCode;
	}

	if (strncmp(pquery, "dll$askExternalServer", 22) == 0) {
		// TODO bjuhasz: move into a separate class which also transmits the game state
		// TODO bjuhasz: GET request with body?
		// TODO bjuhasz: read the URL from a cfg file
		const Response response = Get(Url{ "http://172.22.125.57:5000/" });

		if (response.status_code == 200) {
			double actionCode = std::stod(response.text);
			return actionCode;
		}
		else {
			// TODO bjuhasz: log the Response object
		}
	}

	return defaultActionCode;
}

//******************************************************************************
//
// DLL entry point
//
//******************************************************************************

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
  switch (ul_reason_for_call)	{
		case DLL_PROCESS_ATTACH:
#ifdef _DEBUG
			AllocConsole();
#endif _DEBUG
			InitializeOpenHoldemFunctionInterface();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
#ifdef _DEBUG
			FreeConsole();
#endif _DEBUG
			break;
    }
  return TRUE;
}
