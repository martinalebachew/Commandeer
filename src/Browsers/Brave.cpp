// Brave.cpp
// (C) Martin Alebachew, 2023

#include "pch.h"
#include "Browser.h"
#include "../OS/OS.h"
#include "Brave.h"

Brave::Brave(OS* os) :
	Browser((std::string)"Brave.exe",
		(std::string)R"(C:\Program Files\BraveSoftware\Brave-Browser\Application\brave.exe)",
		(std::string)R"(--remote-debugging-port=9222 --user-data-dir="C:\Users\martin\AppData\Local\BraveSoftware\Brave-Browser\User Data")",
		os) { }