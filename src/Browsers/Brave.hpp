// Brave.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include "../OS/OS.hpp"
#include "Browser.hpp"


class Brave : public Browser {
public:
	Brave(OS* os);
};