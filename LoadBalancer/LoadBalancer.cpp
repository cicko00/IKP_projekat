#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "Communication.h"
#include "CircularBuffer.h"
#include "WorkerList.h"

DWORD WINAPI f1(LPVOID lpParam) {
   return WorkerEcho();
}

DWORD WINAPI f2(LPVOID lpParam) {
   return ClientLink();
}

DWORD WINAPI f3(LPVOID lpParam) {
    return WorkerLink();
}

int  main(void)
{

    DWORD print1ID, print2ID, print3ID;
    HANDLE hPrint1, hPrint2, hPrint3;

    hPrint1 = CreateThread(NULL, 0, &f1, NULL, 0, &print1ID);
    
    hPrint2 = CreateThread(NULL, 0, &f2, NULL, 0, &print2ID);
    hPrint3 = CreateThread(NULL, 0, &f3, NULL, 0, &print3ID);
    
    int cKey = getchar();

    CloseHandle(hPrint1);
    CloseHandle(hPrint2);
    CloseHandle(hPrint3);
}
