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

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define BUFFER_SIZE 1024
#define SERVER_PORT 5055

bool skladistenjePodatakaUTxt(const char* message, int port);

int main()
{
    //deo za prijem poruke od Load Balancera
    SOCKET listenSocket = INVALID_SOCKET;
    SOCKET acceptedSocket = INVALID_SOCKET;
    int iResult;
    char dataBuffer[BUFFER_SIZE];

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return 1;
    }

    sockaddr_in serverAddress;
    memset((char*)&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;				// IPv4 address family
    serverAddress.sin_addr.s_addr = INADDR_ANY;		// Use all available addresses
    serverAddress.sin_port = htons(SERVER_PORT);	// Use specific port


    // Create a SOCKET for connecting to server
    listenSocket = socket(AF_INET,      // IPv4 address family
        SOCK_STREAM,  // Stream socket
        IPPROTO_TCP); // TCP protocol

    // Check if socket is successfully created
    if (listenSocket == INVALID_SOCKET)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    // Setup the TCP listening socket - bind port number and local address to socket
    iResult = bind(listenSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Check if socket is successfully binded to address and port from sockaddr_in structure
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Set listenSocket in listening mode
    iResult = listen(listenSocket, 3);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    printf("Server socket is set to listening mode. Waiting for new connection requests.\n");

    do
    {
        acceptedSocket = accept(listenSocket, NULL, NULL);

        if (acceptedSocket == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }


        // Receive data until the client shuts down the connection
        iResult = recv(acceptedSocket, dataBuffer, BUFFER_SIZE, 0);
        if (iResult > 0)
        {
            dataBuffer[iResult] = '\0';
            //ovde ce se raditi logika za uspis u txt fajl,
            //napravice se metoda i ovde ce se pozvati
            printf("Load Balancer je poslao: %s\n", dataBuffer);
            printf("Rezultat je: %d\n", iResult);
            //printf("\nNew worker with port: %s succesfully added\n");
            bool skladistio = false;
            skladistio = skladistenjePodatakaUTxt(dataBuffer, SERVER_PORT);
            if (skladistio == true)
            {
                printf("Upisan je u txt.");
            }
            else
            {
                printf("Nije upisan u txt.");
            }
        }
        else if (iResult == 0)
        {
            // connection was closed gracefully
            printf("Connection with client closed.\n");
            closesocket(acceptedSocket);
        }
        else
        {
            // there was an error during recv
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(acceptedSocket);
        }

    } while (true);
}

bool skladistenjePodatakaUTxt(const char* dataBuffer, int portOfLoadBalancer)
{

    char buffer[BUFFER_SIZE] = "podaci_";
    char mesto[10];
    _itoa(portOfLoadBalancer, mesto, 10);
    printf("Broj: %s", mesto);



    char* filename1 = strcat(buffer, mesto);
    char* filename2 = strcat(filename1, ".txt");



    FILE* fp = fopen(filename2, "w");
    if (fp == NULL)
    {
        printf("Error with opening the file %s: ", filename2);
        return false;
    }


    fprintf(fp, "Poslati tekst: %s\n", dataBuffer);


    fclose(fp);
    return true;
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
