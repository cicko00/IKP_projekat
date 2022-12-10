#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<WinSock2.h>
#include "Communication.h"
#include "CircularBuffer.h"


int port[3];
char* msg[3];
int i = 0;



DWORD print1ID, print2ID, print3ID;
HANDLE hPrint1, hPrint2, hPrint3;

DWORD WINAPI f1(LPVOID lpParam) {
    return SendToWorker(port[0], msg[0]);
}

DWORD WINAPI f2(LPVOID lpParam) {
    return SendToWorker(port[1], msg[1]);

}
DWORD WINAPI f3(LPVOID lpParam) {
        return SendToWorker(port[2], msg[2]);
    }

int WorkerLink() {

    hPrint1 = CreateThread(NULL, 0, &f1, NULL, 0, &print1ID);
    hPrint2 = CreateThread(NULL, 0, &f2, NULL, 0, &print2ID);
    hPrint3 = CreateThread(NULL, 0, &f3, NULL, 0, &print3ID);


    while (1) {
        char poruka[512] = "";
        strcpy_s(poruka, circularBufferPop());

        if (strcmp(poruka, "") != 0) {

            if (i == 2)
            {
                i = 0;
            }
            else { i++; }
            
            //pusti semafor
        }



    }
}
