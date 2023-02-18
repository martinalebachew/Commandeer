// Commandeer.cpp
// (C) Martin Alebachew, 2023

#include <iostream>
#include <string>
#define PATH C:\Program Files (x86)\BraveSoftware\Brave-Browser\Application\brave.exe

enum Browser { chrome, edge, brave, opera };
enum OS { windows, macos, linux_generic };

class CommandeerDummy {
    OS m_OS;
    Browser m_Browser;
    // TODO: Specify OS supported versions

    std::string m_ProfilePath = R"("C:\Users\martin\AppData\Local\BraveSoftware\Brave-Browser\User Data\Default")";
    std::string m_ExecPath = R"("C:\Program Files (x86)\BraveSoftware\Brave-Browser\Application\brave.exe")";

public:
    CommandeerDummy() {
        m_OS = windows;
        m_Browser = brave;
    }

    std::string GetKillCommand() {
        if (m_Browser == brave && m_OS == windows)
            return R"(taskkill /IM brave.exe /T /F)";
        return "N/A";
    }

    std::string GetLaunchCommand() {
        std::string LaunchCommand = "";
        LaunchCommand += m_ExecPath;
        LaunchCommand += " --remote-debugging-port=9222 --headless --user-data-dir=";
        LaunchCommand += m_ProfilePath;
        return LaunchCommand;
    }
};

int main()
{    
    CommandeerDummy cm;
    std::cout << cm.GetKillCommand() << std::endl;
    std::cout << cm.GetLaunchCommand() << std::endl;

    std::cin.get();
}