// OS.h
// (C) Martin Alebachew, 2023

#pragma once
#include <iostream>

class OS {
public:
	virtual bool KillProcessByExecName(std::string execName) = 0;
	virtual bool LaunchExec(std::string execPath, std::string flags) = 0;
};