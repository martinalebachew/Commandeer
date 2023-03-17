// Browser.cpp
// (C) Martin Alebachew, 2023

#include <iostream>
#include <curl/curl.h>
#include <json/json.hpp>
#include "Browser.h"
using json = nlohmann::json;

Browser::Browser(std::string& execName, std::string& execPath, std::string& flags, OS* os) :
	_execName(execName), _execPath(execPath), _flags(flags), _os(os) { }

Browser::Browser(std::string execName, std::string execPath, std::string flags, OS* os) :
	_execName(execName), _execPath(execPath), _flags(flags), _os(os) { }

bool Browser::Kill() const {
	return _os->KillProcessByExecName(_execName);
}

bool Browser::LaunchWithFlags() const {
	return _os->LaunchBrowserExec(_execPath, _flags);
}

static size_t WritePageToStringCallback(void* contents, size_t size, size_t nmemb, std::string* string) {
	size_t realSize = size * nmemb;
	string->append((char*)contents, realSize);
	return realSize;
}

std::string Browser::ParseDebugEndpoint() const {
	std::string debugEndpoint = "";
	CURL* curl = curl_easy_init();

	if (curl) {
		std::string jsonBuffer;
		curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:9222/json");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WritePageToStringCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonBuffer);
		// curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		if (!curl_easy_perform(curl)) {
			json data = json::parse(jsonBuffer);
			debugEndpoint = data[0]["webSocketDebuggerUrl"];
		}
		curl_easy_cleanup(curl);
	}

	return debugEndpoint;
}
