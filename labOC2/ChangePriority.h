#include "framework.h"
#include "labOC2.h"
#include <windows.h>
#include <tchar.h>
#include <vector>
#include <string.h>
#include <shlobj.h>
#include <sstream>
#include <tlhelp32.h>
#include <strsafe.h>
#include <shlwapi.h>
#include <set>

void Change(std::string choice) {
    HANDLE WH = GetForegroundWindow();
    PROCESS_INFORMATION hProc;
    PROCESSENTRY32W pe = { 0 };
    pe.dwSize = sizeof(pe);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    if (choice == "NORMAL")
    {
        SetPriorityClass(hProcess, NORMAL_PRIORITY_CLASS);
    }
    else if (choice == "HIGH")
    {
        SetPriorityClass(hProcess, HIGH_PRIORITY_CLASS);
    }
    else if (choice == "LOW")
    {
        SetPriorityClass(hProcess, IDLE_PRIORITY_CLASS);
    }
}