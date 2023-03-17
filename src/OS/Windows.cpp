// Windows.cpp
// (C) Martin Alebachew, 2023

#include <Windows.h> // Win32 API
#include "Windows.h" // 'Windows' class header file

bool Windows::KillProcessByExecName(std::string execName) {
	std::cout << "Killing process by name: " << execName << std::endl;
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
			NULL,                    // Argument is irrelevant
			errorCode,                   // Specify requested message id as the error id
			0x409,                   // Retrieve error in en-US
			(LPSTR)&errorMessage,    // Pointer to the message buffer, out
			0,                       // Minumum size of the message buffer in TCHARs
			NULL                     // Argument is irrelevant (no inserts)
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