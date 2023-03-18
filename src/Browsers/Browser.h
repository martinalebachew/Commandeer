// Browser.h
// (C) Martin Alebachew, 2023

#pragma once
#include "pch.h"
#include <iostream>
#include "../OS/OS.h"

class Browser {
protected:
	std::string _execName;
	std::string _execPath;
	std::string _flags;
	OS* _os;

public:
	Browser(std::string& execName, std::string& execPath, std::string& flags, OS* os);
	Browser(std::string execName, std::string execPath, std::string flags, OS* os);
	bool Kill() const;
	bool LaunchWithFlags() const;
	std::string ParseDebugEndpoint() const;
	void WaitUntilEndpointAccessible() const;
	std::string GetAllCookies(std::string endpoint) const;
	bool DumpJSONIntoFile(std::string cookies) const;
};