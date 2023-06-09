// os.cpp
// (C) Martin Alebachew, 2023

#include "os.hpp"

#ifdef _WIN32 // Windows
#include <vector>
#include <Windows.h>
#include <tlhelp32.h>

std::string ToUppercase(std::string original) {
	boost::to_upper(original);
	return original;
}

std::vector<HANDLE> GetProcessHandlesByName(std::string execName) {
	std::vector<HANDLE> hProcesses;
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	while (Process32Next(snapshot, &entry)) {
		if (ToUppercase(entry.szExeFile) == ToUppercase(execName))
			hProcesses.push_back(OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID));
	}

	CloseHandle(snapshot);
	return hProcesses;
}

bool OS::KillProcessByExecName(std::string execName) const {
	std::vector<HANDLE> hProcesses = GetProcessHandlesByName(execName);

	if (!hProcesses.size()) {
		std::cout << "Failed to locate processes of " << execName << std::endl;
		return false;
	}

	for (int i = 0; i < hProcesses.size(); i++) {
		HANDLE hProcess = hProcesses[i];

		if (hProcess && TerminateProcess(hProcess, 0)) {
			WaitForSingleObject(hProcess, INFINITE); // Wait until process terminates
			CloseHandle(hProcess);
		}
	}

	std::cout << "Terminated all processes of " << execName << std::endl;
	return true;
}

bool OS::LaunchBrowserExec(std::string execPath, std::string flags) const {
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcessA(
		(LPCSTR)execPath.c_str(),
		(LPSTR)("\"" + execPath + "\" " + flags).c_str(), // Command line flags
		NULL,                       // Process handle is not inheritable
		NULL,                       // Thread handle is not inheritable
		false,                      // Don't inherit Commandeer's handles
		CREATE_NEW_PROCESS_GROUP | DETACHED_PROCESS, // Process creation flags.
		NULL,                       // Use Commandeer's environment
		NULL,                       // Start at the same workind directory as Commandeer
		&si,                        // Pointer to STARTUPINFOA structure
		&pi                         // Pointer to PROCESS_INFORMATION structure
	)) {
		std::cout << "Failed to create process with error: ";
		DWORD errorCode = GetLastError();
		CHAR* errorMessage;

		if (FormatMessageA(
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			errorCode,
			0x409,                  // Retrieve error in en-US
			(LPSTR)&errorMessage,   // Pointer to the message buffer, out
			0,                      // Minumum size of the message buffer in TCHARs
			NULL
		))
			std::cout << errorMessage << std::endl;
		else
			std::cout << errorCode << std::endl;

		return false;
	}
	
	std::cout << "Browser process created." << std::endl;

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
	return true;
}

void OS::Wait(unsigned int seconds) const {
	Sleep(seconds * 1000);
}
#endif // Windows