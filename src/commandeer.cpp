// commandeer.cpp
// (C) Martin Alebachew, 2023

#include <boost/algorithm/string.hpp>
#include <iostream>
#include "browser.hpp"
#include "os.hpp"

int main()
{    
	Browser brave((std::string)"brave.exe",
    (std::string)R"(C:\Program Files\BraveSoftware\Brave-Browser\Application\brave.exe)",
    (std::string)R"(--remote-debugging-port=9222 --headless=new --user-data-dir="C:\Users\martin\AppData\Local\BraveSoftware\Brave-Browser\User Data")")

    brave.Kill();
    brave.LaunchWithFlags();
    brave.WaitUntilEndpointAccessible();
    std::string dbg_endpoint = brave.ParseDebugEndpoint();
    std::string cookies = brave.GetAllCookies(dbg_endpoint);
    brave.DumpJSONIntoFile(cookies);
    brave.Kill();
}