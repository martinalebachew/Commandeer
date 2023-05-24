// os.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include <iostream>

class OS {
public:
	bool KillProcessByExecName(std::string execName) const;
	bool LaunchBrowserExec(std::string execPath, std::string flags) const;
	void Wait(unsigned int seconds) const;
};