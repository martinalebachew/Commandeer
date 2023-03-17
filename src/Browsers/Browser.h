// Browser.h
// (C) Martin Alebachew, 2023

#pragma once
#include <iostream>
#include "../OS/OS.h"

class Browser {
protected:
	std::string _execName;
	std::string _execPath;
	std::string _flags;
	OS* _os;

public:
	Browser(std::string& execName, std::string& execPath, std::string& flags, OS* os) :
		_execName(execName), _execPath(execPath), _flags(flags), _os(os) { }

	Browser(std::string execName, std::string execPath, std::string flags, OS* os) :
		_execName(execName), _execPath(execPath), _flags(flags), _os(os) { }

	bool Kill() const {
		return _os->KillProcessByExecName(_execName);
	}
	
	bool LaunchWithFlags() const {
		return _os->LaunchBrowserExec(_execPath, _flags);
	}
};