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

void func() {
    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwProcessId = 0;
    DWORD dwThreadId = 0;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    BOOL bCreateProcess = NULL;

    std::wstring siteChrome = L"--new https://www.google.com/";
    std::wstring siteBing = L"--new https://www.bing.com/";
    std::wstring siteYahoo = L"--new https://www.yahoo.com/";
    std::wstring siteDuckDuckGo = L"--new https://duckduckgo.com/";
    std::wstring browser = L"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe";

    if (!CreateProcess(&browser[0], 
        &siteChrome[0], 
        NULL, 
        NULL, 
        FALSE, 
        0, 
        NULL, 
        NULL, 
        &si, 
        &pi)) 
        MessageBox(NULL, 
            L"Unsuccessfuly", 
            L"Error", 
            MB_OK);
    if (!CreateProcess(&browser[0], 
        &siteBing[0], 
        NULL, 
        NULL, 
        FALSE, 
        0, 
        NULL,
        NULL, 
        &si, 
        &pi)) 
        MessageBox(NULL, 
            L"Unsuccessfuly", 
            L"Error", 
            MB_OK);
    if (!CreateProcess(&browser[0], 
        &siteYahoo[0], 
        NULL, 
        NULL, 
        FALSE, 
        0, 
        NULL, 
        NULL, 
        &si, 
        &pi)) 
        MessageBox(NULL, 
            L"Unsuccessfuly",
            L"Error", 
            MB_OK);
    if (!CreateProcess(&browser[0], 
        &siteDuckDuckGo[0], 
        NULL, 
        NULL, 
        FALSE, 
        0, 
        NULL, 
        NULL, 
        &si, 
        &pi)) 
        MessageBox(NULL, 
            L"Unsuccessfuly",
            L"Error", 
            MB_OK);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

}


void func1(std::wstring site) {
    HANDLE hProcess = NULL;
    HANDLE hThread = NULL;
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD dwProcessId = 0;
    DWORD dwThreadId = 0;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    BOOL bCreateProcess = NULL;

    std::wstring browser = L"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe";

    if (!CreateProcess(&browser[0], 
        &site[0], 
        NULL, 
        NULL, 
        FALSE, 
        0, 
        NULL, 
        NULL, 
        &si, 
        &pi)) 
        MessageBox(NULL, 
            L"Unsuccessfuly", 
            L"Error", 
            MB_OK);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

}
