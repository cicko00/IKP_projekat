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
#include "MessageList.h"
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")



DWORD print1ID, print2ID,print3ID;
HANDLE hPrint1, hPrint2,hPrint3;


DWORD WINAPI f1(LPVOID lpParam) {
    int *i = (int*)lpParam;
    return Activate(i[0],i[1]);
}

DWORD WINAPI f2(LPVOID lpParam) {
    int i = *(int*)lpParam;
    return RecvData(i);
}

DWORD WINAPI f3(LPVOID lpParam) {
    int port = *(int*)lpParam;
    return SendData(port);
}




int  main(void)
{

        printf("Unesite port za prijem poruka: \n");
        
        

        int port_RD=0;
        scanf("%d", &port_RD);
       
        printf("Unesite port za redistribuciju podataka: \n");
        int port_SD = 0;
        scanf("%d", &port_SD);

    DWORD print1ID, print2ID,print3ID;
    HANDLE hPrint1, hPrint2,hPrint3;

    int paket_f2[2] = { port_RD,port_SD };
    
    hPrint1 = CreateThread(NULL, 0, &f1, &paket_f2, 0, &print1ID);

    hPrint2 = CreateThread(NULL, 0, &f2, &port_RD, 0, &print2ID);

    hPrint3 = CreateThread(NULL, 0, &f3, &port_SD, 0, &print3ID);

    int cKey = getchar();
    int t = getchar();
    CloseHandle(hPrint1);
    CloseHandle(hPrint2);
    CloseHandle(hPrint3);
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
