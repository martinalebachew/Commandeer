// browser.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include "os.hpp"
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

class Browser {
protected:
	std::string _execName;
	std::string _execPath;
	std::string _flags;

public:
	Browser(std::string& execName, std::string& execPath, std::string& flags);
	Browser(std::string execName, std::string execPath, std::string flags);
	bool Kill() const;
	bool LaunchWithFlags() const;
	std::string ParseDebugEndpoint() const;
	void WaitUntilEndpointAccessible() const;
	std::string GetAllCookies(std::string endpoint) const;
	bool DumpJSONIntoFile(std::string cookies) const;
};