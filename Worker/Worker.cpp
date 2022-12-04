// Worker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iostream>
#include <conio.h>
#include <ws2tcpip.h>
#include <string>
#include <string.h>
#include "Communication.h";
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


DWORD print1ID, print2ID;
HANDLE hPrint1, hPrint2;


DWORD WINAPI f1(LPVOID lpParam) {
    int i = *(int*)lpParam;
    return Activate(i);
}

DWORD WINAPI f2(LPVOID lpParam) {
    int i = *(int*)lpParam;
    return RecvData(i);
}





int  main(void)
{
        printf("Unesite port:\n");
        
        

        int port=0;
        scanf("%d", &port);
       



    DWORD print1ID, print2ID;
    HANDLE hPrint1, hPrint2;


    hPrint1 = CreateThread(NULL, 0, &f1, &port, 0, &print1ID);

    hPrint2 = CreateThread(NULL, 0, &f2, &port, 0, &print2ID);

    int cKey = getchar();
    int t = getchar();
    CloseHandle(hPrint1);
    CloseHandle(hPrint2);
}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
