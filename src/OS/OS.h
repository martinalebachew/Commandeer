// OS.h
// (C) Martin Alebachew, 2023

#pragma once
#include "pch.h"
#include <iostream>

class OS {
public:
	virtual bool KillProcessByExecName(std::string execName) const = 0;
	virtual bool LaunchBrowserExec(std::string execPath, std::string flags) const = 0;
	virtual void Wait(unsigned int seconds) const = 0;
};