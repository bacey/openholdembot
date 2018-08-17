
#include <stdexcept>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

// TODO bjuhasz: these are needed only by GetCurrentDirectory,
// delete them later
#include <windows.h>
#include <string>

#include "INIReader.h"
#include "ExternalBotLogicClient.h"
#include "OpenHoldemFunctions.h"

using namespace std;
using namespace cpr;
using json = nlohmann::json;


ExternalBotLogicClient::ExternalBotLogicClient()
{
}

double ExternalBotLogicClient::askExternalBotLogicServer() {

	double symbolValue = GetSymbol("nplayersdealt");

	json j2 = {
		{ "pi", 3.141 },
		{ "happy", true },
		{ "name", "Niels" },
		{ "nothing", nullptr },
		{ "answer", {
			{ "everything", 42 }
		}},
		{ "list",{ 1, 0, 2 } },
		{ "object", {
			{ "currency", "USD" },
			{ "value", 42.99 }
		}}
	};

	string s = j2.dump();

	//#define MAX_PATH 10000
	//TCHAR pwd[MAX_PATH];
	//GetCurrentDirectory(MAX_PATH, pwd);

	INIReader iniReader("user.ini");

	if (iniReader.ParseError() < 0) {
		std::cout << "Couldn't load 'user.ini'\n";
		return 1;
	}

	const string defaultServerUrl = "http://localhost:5000/";
	const string serverUrl = iniReader.Get("server", "url", defaultServerUrl);

	const Response response = Get(Url{ serverUrl });

	if (response.status_code == 200) {
		double actionCode = stod(response.text);
		return actionCode;
	}
	else {
		// TODO bjuhasz: log the Response object
		throw domain_error("TODO throw an error with message and stack trace");
	}
}


ExternalBotLogicClient::~ExternalBotLogicClient()
{
}
