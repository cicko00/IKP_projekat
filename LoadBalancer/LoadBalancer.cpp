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
DWORD WINAPI f4(LPVOID lpParam) {
    return DataRedistributer();
}

int  main(void)
{

    DWORD print1ID, print2ID, print3ID, print4ID;
    HANDLE hPrint1, hPrint2, hPrint3, hPrint4;

    hPrint1 = CreateThread(NULL, 0, &f1, NULL, 0, &print1ID);
    
    hPrint2 = CreateThread(NULL, 0, &f2, NULL, 0, &print2ID);
    hPrint3 = CreateThread(NULL, 0, &f3, NULL, 0, &print3ID);
    hPrint4 = CreateThread(NULL, 0, &f4, NULL, 0, &print4ID);
    
    int cKey = getchar();

    freeMemory();
    ClearWList();
    CloseHandle(hPrint1);
    CloseHandle(hPrint2);
    CloseHandle(hPrint3);
    CloseHandle(hPrint4);

    printf("Now do snapshot.");
    int key = getchar();
    return 0;
}
