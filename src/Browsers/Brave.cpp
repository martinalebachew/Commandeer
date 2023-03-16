// Brave.cpp
// (C) Martin Alebachew, 2023

#include "Browser.h"
#include "../OS/OS.h"
#include "Brave.h"

Brave::Brave(OS* os) :
	Browser((std::string)"Brave.exe", (std::string)"BRAVEPATH", (std::string)"BRAVEFLAGS", os) { }