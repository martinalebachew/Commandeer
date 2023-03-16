// Commandeer.cpp
// (C) Martin Alebachew, 2023

#include <iostream>
#include "OS/Windows.h"
#include "Browsers/Brave.h"

int main()
{    
    OS* windows = new Windows();
    Browser* browser = new Brave(windows);

    browser->Kill();
    browser->LaunchWithFlags();
    //std::string dbg_endpoint = browser.ExtractDebugEndpoint();
    //std::cout << dbg_endpoint << std::endl;
}