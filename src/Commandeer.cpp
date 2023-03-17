// Commandeer.cpp
// (C) Martin Alebachew, 2023

#include <iostream>
#include "OS/Windows.h"
#include "Browsers/Brave.h"

int main()
{    
    OS* windows = new Windows();
    Browser* browser = new Brave(windows);

    //browser->Kill();
    //browser->LaunchWithFlags();
    std::string dbg_endpoint = browser->ParseDebugEndpoint();
    std::cout << dbg_endpoint << std::endl;
    //std::string cookies = browser->GetAllCookies(dbg_endpoint);
    //std::cout << cookies << std::endl;
    //browser->Kill();

    delete browser;
    delete windows;
}