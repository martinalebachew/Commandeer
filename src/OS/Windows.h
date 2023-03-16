// Windows.h
// (C) Martin Alebachew, 2023

#pragma once
#include <iostream>
#include "OS.h"

class Windows : public OS {
public:
	bool KillProcessByExecName(std::string execName) override;
	bool LaunchExec(std::string execPath, std::string flags) override;
};