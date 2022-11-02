// labOC3.cpp : Defines the entry point for the application.
//

#include<iostream>
#include<fstream>
#include <windows.h>
#include<chrono>
#include <tchar.h>
#include <vector>
#include <string.h>
#include<string>
#include<charconv>
#include <shlobj.h>
#include <sstream>
#include <tlhelp32.h>
#include <strsafe.h>
#include <shlwapi.h>
#include <set>
#include<random>
#define THREADS 100
#define SIZE 10
#define MAX_LOADSTRING 100

using namespace std;
using namespace std::chrono;

//void findEl(int **arr, int *repeat,int n) {
//    int index = 0, m = 0;
//    int maxREPindex = 0, maxindex = 0;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++) {
//            repeat[m] = arr[i][j];
//            m++;
//        }
//    }
//
//    for (int i = 0; i < n * n; i++) {
//        for (int j = i; j >= 0; j--) {
//            if (repeat[i] == repeat[j]) {
//                index++;
//            }
//            if (index > maxREPindex) {
//                maxindex = j;
//                maxREPindex = index;
//            }
//        }
//    }
//
//    std::cout << "Element with the maximum index: " << repeat[maxindex]<<std::endl;
//    std::cout << "The maximum index of repeats: " << maxREPindex << std::endl;
//}
//
//int main() {
//    int n = 10;
//    int** arr = new int* [n];
//    for (int i = 0; i < n; i++) {
//        arr[i] = new int[n];
//        for (int j = 0; j < n; j++) {
//            std::cin >> arr[i][j];
//        }
//    }
//    int* rep = new int[n*n];
//    findEl(arr, rep, n);
//}
int num = 0;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

int A[SIZE];
int B[SIZE];
int step = 0;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



int GenerateRandomNumber(int from, int to) {
    random_device rd; // obtain a random number from hardware     
    mt19937 gen(rd()); // seed the generator    
    uniform_int_distribution<> distr(from, to); // define the range   
    return distr(gen);
}



DWORD WINAPI findEl1(LPVOID p) {
    int indexSTART = -1, indexFINISH = 0;
    int maxindexSTART = 0, maxindexFINISH = 0;
    int max = 0;
    bool skip = false;
    for (int i = 0; i < SIZE; i++) {
        B[i] = 0;
        if (A[i] < A[i + 1] && skip == false) {
            skip = true;
            indexSTART = i;
        }
        else if (A[i] > A[i + 1] && indexSTART != -1) {
            indexFINISH = i;
            if (indexFINISH - indexSTART > max) {
                max = indexFINISH - indexSTART;
                maxindexSTART = indexSTART;
                maxindexFINISH = indexFINISH;
            }
            indexSTART = -1;
            skip = false;
        }
    }

    int counter = 0;
    for (int i = maxindexSTART; i <= maxindexFINISH; i++) {
        B[counter] = A[i];
        counter++;
    }

    ExitThread(0);
}


DWORD WINAPI findEl(LPVOID p) {
    int a = SIZE / THREADS;
    int indexSTART = -1, indexFINISH = 0;
    int maxindexSTART = 0, maxindexFINISH = 0;
    int max = 0;
    int thread_num = 1;
    bool skip = false;
    for (int i = thread_num * (a); i < (thread_num + 1) * (a); i++) {
        for (int j = 0; j < SIZE; j++) {
            if (A[j] < A[j + 1] && skip == false) {
                skip = true;
                indexSTART = j;
            }
            else if (A[j] > A[j + 1] && indexSTART != -1) {
                indexFINISH = j;
                if (indexFINISH - indexSTART > max) {
                    max = indexFINISH - indexSTART;
                    maxindexSTART = indexSTART;
                    maxindexFINISH = indexFINISH;
                }
                indexSTART = -1;
                skip = false;
            }
        }
    }
    int counter = 0;
    for (int i = maxindexSTART; i < maxindexFINISH; i++) {
        B[counter] = A[i];
        counter++;
    }

    ExitThread(0);
}


int main() {
    ofstream fA;
    fA.open("SMALL TEST", ios::out);

    for (int i = 0; i < SIZE; i++)
    {

        A[i] = rand() % 10;
        fA << A[i] << " ";

        fA << endl;
    }
    fA.close();

    HANDLE hThreadArray1;
    auto start1 = high_resolution_clock::now();

    hThreadArray1 = CreateThread(
        NULL,
        0,
        findEl1,
        NULL,
        0,
        NULL);

    if (hThreadArray1 == NULL) {
        return 1;
    }


    WaitForSingleObject(hThreadArray1, INFINITE);

    CloseHandle(hThreadArray1);

    auto stop1 = high_resolution_clock::now();

    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    ofstream f;
    f.open("Res.txt", ios::out);

    cout << endl << "Res: " << endl;

    for (int i = 0; i < SIZE; i++)
    {
        if (B[i] != 0) {
            f << B[i] << " ";
            cout << B[i] << " ";

            cout << endl;
            f << endl;
        }
        else {
            break;
        }
    }
    f.close();

    cout << endl << endl;

    cout << "time(one handle): " << duration1.count() << endl;

    cout << endl << endl;


    HANDLE hThreadArray[THREADS] {};
    DWORD dwThreadIdArray[THREADS]{};
    auto start = high_resolution_clock::now();

    for (int i = 0; i < THREADS; i++) {
        hThreadArray[i] = CreateThread(
            NULL,
            0,
            findEl,
            NULL,
            0,
            &dwThreadIdArray[i]);

        if (hThreadArray[i] == NULL) {
            return 1;
        }
    }

    WaitForMultipleObjects(THREADS, hThreadArray, TRUE, INFINITE);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    for (int i = 0; i < THREADS; i++) {
        if (hThreadArray[i] != INVALID_HANDLE_VALUE) {
            CloseHandle(hThreadArray[i]);
        }
    }

    cout << endl << "RES: " << endl;

    for (int i = 0; i < SIZE; i++)
    {

        cout << B[i] << endl;

    }

    cout << endl << endl;

    cout << "time(one handle): " << duration.count() << endl;

    cout << endl << endl;
}
