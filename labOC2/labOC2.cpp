// labOC2.cpp : Defines the entry point for the application.
//

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
#include"func.h"
#include"ChangePriority.h"
#include"Header.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
static std::vector <PROCESS_INFORMATION> handlesToThreads;
const auto explorer = OpenProcess(PROCESS_TERMINATE, false, GetCurrentProcessId());
std::wstring siteChrome = L"https://www.google.com/";
std::wstring siteBing = L"https://www.bing.com/";
std::wstring siteYahoo = L"https://www.yahoo.com/";
std::wstring siteDuckDuckGo = L"https://duckduckgo.com/";

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


//void SelectFolder(HWND hWnd) {
//
//    BROWSEINFO bi = { 0 };
//    bi.lpszTitle = _T("Browsing...");
//    bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE | BIF_NONEWFOLDERBUTTON;
//    bi.hwndOwner = hWnd;
//
//    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
//    TCHAR path[MAX_PATH];
//    if (pidl) {
//        SHGetPathFromIDList(pidl, path);
//        MessageBox(NULL,
//            path,
//            _T("The path folder, that you selected"),
//            NULL);
//        TCHAR szDir[MAX_PATH];
//
//        StringCchCopy(szDir, MAX_PATH, path);
//        StringCchCat(szDir, MAX_PATH, TEXT("\\*"));
//
//        WIN32_FIND_DATA ffd;
//        HANDLE hFind = INVALID_HANDLE_VALUE;
//        hFind = FindFirstFile(szDir, &ffd);
//
//        std::set<std::wstring> types;
//
//        do {
//            std::wstring ws(ffd.cFileName);
//            int idx = ws.find_last_of('.') + 1;
//            std::wstring type = ws.substr(idx);
//            for (int i = 0; i < type.size(); i++) {
//                type[i] = tolower(type[i]);
//            }
//            std::wstring wStr;
//
//            std::wstring zip = _T("7z");
//            if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && type != zip) {
//                types.insert(type);
//            }
//
//        } while (FindNextFile(hFind, &ffd) != 0);
//
//        handlesToThreads.clear();
//        for (std::wstring type : types) {
//            std::wstring wpath(path);
//            STARTUPINFO si;
//            PROCESS_INFORMATION pi;
//
//            ZeroMemory(&si, sizeof(si));
//            si.cb = sizeof(si);
//            ZeroMemory(&pi, sizeof(pi));
//            // Compress
//            handlesToThreads.push_back(pi);
//        }
//    }
//}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LABOC2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABOC2));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABOC2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+2);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABOC2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, L"Zipper", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: {

        HWND text = CreateWindowW(L"STATIC",
            L"CHOOSE THE OPTION THAT YOU WANT TO USE:",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            20,
            20,
            322,
            20,
            hWnd,
            NULL,
            NULL,
            NULL);

        HWND buttonGoogle = CreateWindowW(L"BUTTON",
            L"Google",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            20,
            70,
            200,
            20,
            hWnd,
            (HMENU)1,
            NULL,
            NULL);

        HWND buttonAll = CreateWindowW(L"BUTTON",
            L"All websites",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            20,
            100,
            200,
            20,
            hWnd,
            (HMENU)5,
            NULL,
            NULL);


        HWND buttonQUIT = CreateWindowW(L"BUTTON",
            L"QUIT",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            20,
            220,
            200,
            20,
            hWnd,
            (HMENU)6,
            NULL,
            NULL);

        HWND buttonSUSPEND = CreateWindowW(L"BUTTON",
            L"SUSPEND PROCESS",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            230,
            70,
            200,
            20,
            hWnd,
            (HMENU)7,
            NULL,
            NULL);

        HWND buttonRESUME = CreateWindowW(L"BUTTON",
            L"RESUME PROCESS",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            230,
            100,
            200,
            20,
            hWnd,
            (HMENU)8,
            NULL,
            NULL);

        HWND buttonKILL = CreateWindowW(L"BUTTON",
            L"KILL PROCESS",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            230,
            130,
            200,
            20,
            hWnd,
            (HMENU)9,
            NULL,
            NULL);

        HWND buttonLOW = CreateWindowW(L"BUTTON",
            L"SET LOW PRIORITY",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            440,
            70,
            200,
            20,
            hWnd,
            (HMENU)10,
            NULL,
            NULL);

        HWND buttonNORMAL = CreateWindowW(L"BUTTON",
            L"SET NORMAL PRIORITY",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            440,
            100,
            200,
            20,
            hWnd,
            (HMENU)11,
            NULL,
            NULL);

        HWND buttonHIGH = CreateWindowW(L"BUTTON",
            L"SET HIGH PRIORITY",
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            440,
            130,
            200,
            20,
            hWnd,
            (HMENU)12,
            NULL,
            NULL);

        break;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case 1:
            func1(siteChrome);
            break;
        case 5:
            func();
            break;
        case 6:
            ::MessageBeep(MB_ICONERROR);
            ::MessageBoxA(hWnd, "THE PROGRAM WAS CLOSED", "Zipper", MB_OKCANCEL);
            SendMessage(hWnd, WM_CLOSE, 0, 0);
            break;
        case 7:
            /*suspend(GetCurrentProcessId());*/
            system("pause");
            break;
        case 8:
            break;
        case 9:
            TerminateProcess(explorer, 1);
            CloseHandle(explorer);
        case 10:
            Change("LOW");
            break;
        case 11:
            Change("NORMAL");
            break;
        case 12:
            Change("HIGH");
            break;
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
