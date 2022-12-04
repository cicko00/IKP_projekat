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
#include "Writer.h"


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define BUFFER_SIZE 1024

bool WriteInTxt(const char* dataBuffer,int port){

    char buffer[BUFFER_SIZE] = "podaci_";
    char mesto[10];
    _itoa(port, mesto, 10);
    printf("Broj: %s", mesto);



    char* filename1 = strcat(buffer, mesto);
    char* filename2 = strcat(filename1, ".txt");



    FILE* fp = fopen(filename2, "a");
    if (fp == NULL)
    {
        printf("Error with opening the file %s: ", filename2);
        return false;
    }


    fprintf(fp, "Poslati tekst: %s\n", dataBuffer);


    fclose(fp);
    return true;


}

