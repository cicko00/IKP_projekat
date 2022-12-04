#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "Communication.h"



DWORD print1ID, print2ID;
HANDLE hPrint1, hPrint2;


DWORD WINAPI f1(LPVOID lpParam) {
   return WorkerEcho();
}

DWORD WINAPI f2(LPVOID lpParam) {
   return ClientLink();
}





int  main(void)
{
    DWORD print1ID, print2ID;
    HANDLE hPrint1, hPrint2;


    hPrint1 = CreateThread(NULL, 0, &f1, NULL, 0, &print1ID);
    
    hPrint2 = CreateThread(NULL, 0, &f2, NULL, 0, &print2ID);
    
    int cKey = getchar();

    CloseHandle(hPrint1);
    CloseHandle(hPrint2);
}
