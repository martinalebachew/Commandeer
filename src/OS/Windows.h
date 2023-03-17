// Windows.h
// (C) Martin Alebachew, 2023

#pragma once
#include <iostream>
#include <Windows.h> // Win32 API
#include "OS.h"

class Windows : public OS {
public:
	bool KillProcessByExecName(std::string execName) override;
	bool LaunchBrowserExec(std::string execPath, std::string flags) override;
};