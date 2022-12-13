// Client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <iostream>
#include <conio.h>
#include <ws2tcpip.h>
#include <string>


#pragma comment(lib,"Ws2_32.lib")
#define OUTGOING_BUFFER_SIZE 1024
#define SERVER_PORT 5059
#define SERVER_IP_ADDRESS "127.0.0.1"

int main()
{
    struct sockaddr_in serv_addr;
    int sockAddrLen = sizeof(struct sockaddr);
    //smestice se poruka u outgoingBuffer
    char outgoingBuffer[OUTGOING_BUFFER_SIZE];
    char outgoingBuffer2[OUTGOING_BUFFER_SIZE];
    int serverPort = SERVER_PORT;

    int iResult;


    memset((char*)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDRESS);
    serv_addr.sin_port = htons((u_short)serverPort);

    // Initialize windows sockets library for this process
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return 1;
    }

    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //(domain, type, protocol)

    if (client_socket == INVALID_SOCKET)
    {
        printf("\nSocket creation error\n");
        WSACleanup();
        return -1;
    }

    if (connect(client_socket, (SOCKADDR*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
     {
         printf("Unable to connect to server.\n");
         closesocket(client_socket);
         WSACleanup();
         return 1;
     }
    int o = 0;
    while (o < 100)
    {
        //printf("Unesite poruku: ");
        //gets_s(outgoingBuffer, OUTGOING_BUFFER_SIZE);
        const char* m = "aaa";
        strcpy_s(outgoingBuffer,m);
        iResult = send(client_socket, outgoingBuffer, (int)strlen(outgoingBuffer), 0);  //socket, buffer, lenght, flags

        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(client_socket);
            WSACleanup();
            return 1;
        }

        printf("Poruka je uspesno poslata. Ukupan broj bajtova: %ld\n", iResult);
        //printf("Da li zelite da posaljete jos poruka? ");
        //gets_s(outgoingBuffer2, OUTGOING_BUFFER_SIZE);

        o++;
        Sleep(10);
        if (strcmp(outgoingBuffer2, "ne") == 0)
        {
            break;
        }
        else
        {
            continue;
        }


        
    } 

    iResult = shutdown(client_socket, SD_BOTH);

    // Check if connection is succesfully shut down.
    if (iResult == SOCKET_ERROR)
    {
        printf("Shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }

    printf("\nPress any key to exit: ");
    _getch();


    // Close connected socket
    closesocket(client_socket);

    // Deinitialize WSA library
    WSACleanup();

    return 0;
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

