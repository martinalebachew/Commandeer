// Windows.cpp
// (C) Martin Alebachew, 2023

#include <vector>
#include <Windows.h> // Win32 API
#include <tlhelp32.h>
#include "Windows.h" // 'Windows' class header file

std::vector<HANDLE> Windows::GetProcessHandlesByName(std::string execName) {
	std::vector<HANDLE> hProcesses;
	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(PROCESSENTRY32W);
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	wchar_t* wExecName = new wchar_t[execName.length() + 1];
	for (int i = 0; i < execName.length(); i++)
		wExecName[i] = execName[i];
	wExecName[execName.length()] = NULL; // Null termination character

	while (Process32Next(snapshot, &entry)) {
		if (_wcsicmp((WCHAR*)entry.szExeFile, wExecName) == 0)
			hProcesses.push_back(OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID));
	}

	CloseHandle(snapshot);
	return hProcesses;
}

bool Windows::KillProcessByExecName(std::string execName) {
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

bool Windows::LaunchBrowserExec(std::string execPath, std::string flags) {
	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	if (!CreateProcessA(
		(LPCSTR)execPath.c_str(),   // Browser's executable path
		(LPSTR)flags.c_str(),       // Command line flags: headless, remote-debugging-port, user-data-dir
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
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS, // Formatting options
			NULL,                   // Argument is irrelevant
			errorCode,              // Specify requested message id as the error id
			0x409,                  // Retrieve error in en-US
			(LPSTR)&errorMessage,   // Pointer to the message buffer, out
			0,                      // Minumum size of the message buffer in TCHARs
			NULL                    // Argument is irrelevant (no inserts)
		))
			std::cout << errorMessage << std::endl;
		else
			std::cout << errorCode << std::endl;

		return false;
	}
	
	std::cout << "Browser process created." << std::endl;
	
	// *** Uncomment to wait for process termination and print exit code ***
	// DWORD exitCode;
	// WaitForSingleObject(pi.hProcess, INFINITE);
	// GetExitCodeProcess(pi.hProcess, &exitCode);
	// std::cout << "Process finished with exit code: " << exitCode << std::endl;

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	return true;
}