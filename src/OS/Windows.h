// Windows.h
// (C) Martin Alebachew, 2023

#pragma once
#include <iostream>
#include <vector>
#include <Windows.h> // Win32 API
#include "OS.h"

class Windows : public OS {
protected:
	std::vector<HANDLE> GetProcessHandlesByName(std::string execName) const;

public:
	bool KillProcessByExecName(std::string execName) const override;
	bool LaunchBrowserExec(std::string execPath, std::string flags) const override;
};