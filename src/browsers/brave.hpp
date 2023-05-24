// brave.hpp
// (C) Martin Alebachew, 2023

#pragma once
#include "../os.hpp"
#include "browser.hpp"


class Brave : public Browser {
public:
	Brave(OS* os);
};