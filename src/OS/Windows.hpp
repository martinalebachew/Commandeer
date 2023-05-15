// Windows.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include "OS.hpp"
#include <iostream>
#include <vector>

#define UNICODE
#include <Windows.h>
#include <tlhelp32.h>

class Windows : public OS {
protected:
	std::vector<HANDLE> GetProcessHandlesByName(std::string execName) const;

public:
	bool KillProcessByExecName(std::string execName) const override;
	bool LaunchBrowserExec(std::string execPath, std::string flags) const override;
	void Wait(unsigned int seconds) const override;
};