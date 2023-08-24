// os.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include <iostream>

bool KillProcessByExecName(std::string execName);
bool LaunchBrowserExec(std::string execPath, std::string flags);
void Wait(unsigned int seconds);