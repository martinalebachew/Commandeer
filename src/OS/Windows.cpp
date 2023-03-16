// Windows.cpp
// (C) Martin Alebachew, 2023

#include "Windows.h"

bool Windows::KillProcessByExecName(std::string execName) {
	std::cout << "Killing process by name: " << execName << std::endl;
	return true;
}

bool Windows::LaunchExec(std::string execPath, std::string flags) {
	std::cout << "Running command\nExecPath:\n" << execPath << "\nFlags:\n" << flags << std::endl;
	return true;
}