
#include <stdexcept>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <iostream>

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

	INIReader reader("user.ini");

	if (reader.ParseError() < 0) {
		std::cout << "Couldn't load 'user.ini'\n";
		return 1;
	}

	const string serverUrl = reader.Get("server", "url", "http://localhost:5000/");

	/*
	std::cout << "Config loaded from 'test.ini': version="
		<< reader.GetInteger("protocol", "version", -1) << ", name="
		<<  << ", email="
		<< reader.Get("user", "email", "UNKNOWN") << ", pi="
		<< reader.GetReal("user", "pi", -1) << ", active="
		<< reader.GetBoolean("user", "active", true) << "\n";
	*/

	const Response response = Get(Url{ "http://172.22.125.57:5000/" });

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
