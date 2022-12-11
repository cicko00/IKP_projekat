#define _WINSOCK_DEPRECATED_NO_WARNINGS
//test
#include <stdio.h>
#include <stdlib.h>
#include "Communication.h"
#include <ws2tcpip.h>
#include "WorkerList.h"
#include <Windows.h>
#include "CircularBuffer.h"
#include <conio.h>

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT_CLIENTLINK "5059"
#define DEFAULT_PORT_WORKERECHO "5058"
#define SERVER_IP_ADDERESS "127.0.0.1"
#pragma comment(lib,"Ws2_32.lib")
bool InitializeWindowsSockets();
CRITICAL_SECTION cs;

int SendToWorker(int& port, const char* msg,int cnt);
int SendToWorker_We(int& pMin, int& pMax, int count, int& data);



HANDLE semaphore1;           // semafor koji ukazuje da li postoje i koliko, praznih mesta u kruznom baferu. 
HANDLE semaphore2;            // semafor koji ukazuje koliko mesta je popunjeno u kruznom baferom.
HANDLE semaphore3;
HANDLE semaphore_1;           // semafor koji ukazuje da li postoje i koliko, praznih mesta u kruznom baferu. 
HANDLE semaphore_2;            // semafor koji ukazuje koliko mesta je popunjeno u kruznom baferom.
HANDLE semaphore_3;


HANDLE semaphores[3] = { semaphore1,semaphore2,semaphore3 };
HANDLE semaphores_we[3] = { semaphore_1, semaphore_2, semaphore_3 };


int port[3], port_weMax[3], port_weMin[3], brojPoruka[3];
char msg[3][512];
int i = 0, j = 0;

struct param1 {
    int cnt=0;
    int *p=&port[0];
   const char* c=msg[0];

}PARAM1;

struct param2 {
    int cnt = 1;
    int *p = &port[1];
   const char* c = msg[1];

}PARAM2;

struct param3 {
    int cnt = 2;
    int *p = &port[2];
   const char* c = msg[2];

}PARAM3;
/// <summary>
/// //////////////////////////////////////////////////////
/// </summary>
struct param_1 {
    int cnt = 0;
    int* pMin = &port_weMin[0];
    int* pMax = &port_weMax[0];
    int* d = &brojPoruka[0];

}PARAM_1;

struct param_2 {
    int cnt = 1;
    int* pMin = &port_weMin[1];
    int* pMax = &port_weMax[1];
    int* d = &brojPoruka[1];

}PARAM_2;

struct param_3 {
    int cnt = 2;
    int* pMin = &port_weMin[2];
    int* pMax = &port_weMax[2];
    int* d = &brojPoruka[2];

}PARAM_3;

DWORD print1ID, print2ID, print3ID, print1_ID, print2_ID, print3_ID;
HANDLE hPrint1, hPrint2, hPrint3, hPrint_1, hPrint_2, hPrint_3;



DWORD WINAPI ff1(LPVOID lpParam) {

    
    int *p = (*(param1*)lpParam).p;
   const char *c = (*(param1*)lpParam).c;
    int cnt= (*(param1*)lpParam).cnt;
    
    return SendToWorker(*p,c,cnt);
}


DWORD WINAPI ff2(LPVOID lpParam) {
    int *p = (*(param2*)lpParam).p;
   const char* c = (*(param2*)lpParam).c;
    int cnt = (*(param2*)lpParam).cnt;

    return SendToWorker(*p, c, cnt);

}
DWORD WINAPI ff3(LPVOID lpParam) {
    int *p = (*(param3*)lpParam).p;
   const char* c = (*(param3*)lpParam).c;
    int cnt = (*(param3*)lpParam).cnt;

    return SendToWorker(*p, c, cnt);
}

/// <summary>
/// //////////////////////////////////////////////
/// </summary>

DWORD WINAPI f1_we(LPVOID lpParam) {


    int* pMin = (*(param_1*)lpParam).pMin;
    int* pMax = (*(param_1*)lpParam).pMax;
    int* c = (*(param_1*)lpParam).d;
    int cnt = (*(param_1*)lpParam).cnt;

    return SendToWorker_We(*pMax, *pMin, cnt, *c);
}


DWORD WINAPI f2_we(LPVOID lpParam) {
    int* pMin = (*(param_2*)lpParam).pMin;
    int* pMax = (*(param_2*)lpParam).pMax;
    int* c = (*(param_2*)lpParam).d;
    int cnt = (*(param_2*)lpParam).cnt;

    return SendToWorker_We(*pMax, *pMin, cnt, *c);

}
DWORD WINAPI f3_we(LPVOID lpParam) {
    int* pMin = (*(param_3*)lpParam).pMin;
    int* pMax = (*(param_3*)lpParam).pMax;
    int* c = (*(param_3*)lpParam).d;
    int cnt = (*(param_3*)lpParam).cnt;

    return SendToWorker_We(*pMax, *pMin, cnt, *c);
}

int WorkerLink() {

    semaphores[0] = CreateSemaphore(0, 0, 1, NULL);
    semaphores[1] = CreateSemaphore(0, 0, 1, NULL);
    semaphores[2] = CreateSemaphore(0, 0, 1, NULL);
    
    hPrint1 = CreateThread(NULL, 0, &ff1, &PARAM1, 0, &print1ID);
    hPrint2 = CreateThread(NULL, 0, &ff2, &PARAM2, 0, &print2ID);
    hPrint3 = CreateThread(NULL, 0, &ff3, &PARAM3, 0, &print3ID);
    InitializeCriticalSection(&cs);
    
    while (1) {
        char poruka[512] = "";
        strcpy_s(poruka, circularBufferPop());
       
        
        if (strcmp(poruka, "") != 0) {

            port[i] = findMin();
            strcpy_s(msg[i], poruka);
           
            ReleaseSemaphore(semaphores[i], 1, 0);

            if (i == 2)
            {
                i = 0;
            }
            else { i++; }

            //pusti semafor
        }
    }
}

int SendToWorker_We(int &port_weMax, int &port_weMin, int cnt, int &brojPoruka)
{
    SOCKET connectSocket = INVALID_SOCKET;
    // variable used to store function return value
    int iResult;

    if (InitializeWindowsSockets() == false)
    {
        // we won't log anything since it will be logged
        // by InitializeWindowsSockets() function
        return 1;
    }
    while (1)
    {
        WaitForSingleObject(semaphores_we[cnt], INFINITE); //da li ima max vrednost

        // create a socket
        connectSocket = socket(AF_INET,
            SOCK_STREAM,
            IPPROTO_TCP);

        if (connectSocket == INVALID_SOCKET)
        {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // create and initialize address structure
        sockaddr_in serverAddress;
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDERESS);
        serverAddress.sin_port = htons(u_short(port_weMax));
        // connect to server specified in serverAddress and socket connectSocket
        if (connect(connectSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
        {
            printf("Unable to connect to server.\n");
            closesocket(connectSocket);
            WSACleanup();
        }

        // Send an prepared message with null terminator included

        int paket[2];
        paket[0] = port_weMin;
        paket[1] = brojPoruka;

        iResult = send(connectSocket, (const char*)paket, (int)strlen((const char*)paket) + 1, 0);

        if (iResult == SOCKET_ERROR)
        {
            printf("send failed with error: %d\n", WSAGetLastError());
            closesocket(connectSocket);
            WSACleanup();
            return 1;
        }
        
        printf("Bytes Sent: %ld : port min: %d,broj poruka: %d\n", iResult, paket[0], paket[1]);
    }

    // cleanup
    closesocket(connectSocket);
    WSACleanup();

    return 0;
}


int SendToWorker(int &port,const char* msg,int cnt) {
    
    char sendbuf[512]="";
    const char* message="";
    // socket used to communicate with server
    SOCKET connectSocket = INVALID_SOCKET;
    // variable used to store function return value
    int iResult;
    // message to send
    const char* messageToSend = "this is a test";

      

    if (InitializeWindowsSockets() == false)
    {
        // we won't log anything since it will be logged
        // by InitializeWindowsSockets() function
        return 1;
    }
 while (1) 
 {
     WaitForSingleObject(semaphores[cnt],INFINITE);

         // create a socket
         connectSocket = socket(AF_INET,
             SOCK_STREAM,
             IPPROTO_TCP);

         if (connectSocket == INVALID_SOCKET)
         {
             printf("socket failed with error: %ld\n", WSAGetLastError());
             WSACleanup();
             return 1;
         }


         // create and initialize address structure
         sockaddr_in serverAddress;
         serverAddress.sin_family = AF_INET;
         serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP_ADDERESS);
         serverAddress.sin_port = htons(u_short(port));
         // connect to server specified in serverAddress and socket connectSocket
         if (connect(connectSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
         {
             printf("Unable to connect to server.\n");
             closesocket(connectSocket);
             WSACleanup();
         }

         // Send an prepared message with null terminator included





         iResult = send(connectSocket, msg, (int)strlen(msg) + 1, 0);

         if (iResult == SOCKET_ERROR)
         {
             printf("send failed with error: %d\n", WSAGetLastError());
             closesocket(connectSocket);
             WSACleanup();
             return 1;
         }
         AddData(port);
         printf("Bytes Sent: %ld : %s\n", iResult, msg);

     
 }
    // cleanup
    closesocket(connectSocket);
    WSACleanup();

    return 0;
}





int  ClientLink(){

    // Socket used for listening for new clients 
    SOCKET listenSocket = INVALID_SOCKET;
    // Socket used for communication with client
    SOCKET acceptedSocket = INVALID_SOCKET;
    // variable used to store function return value
    int iResult;
    // Buffer used for storing incoming data
    

    if (InitializeWindowsSockets() == false)
    {
        // we won't log anything since it will be logged
        // by InitializeWindowsSockets() function
        return 1;
    }

    // Prepare address information structures
    addrinfo* resultingAddress = NULL;
    addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4 address
    hints.ai_socktype = SOCK_STREAM; // Provide reliable data streaming
    hints.ai_protocol = IPPROTO_TCP; // Use TCP protocol
    hints.ai_flags = AI_PASSIVE;     // 

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT_CLIENTLINK, &hints, &resultingAddress);
    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    listenSocket = socket(AF_INET,      // IPv4 address famly
        SOCK_STREAM,  // stream socket
        IPPROTO_TCP); // TCP

    if (listenSocket == INVALID_SOCKET)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(resultingAddress);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket - bind port number and local address 
    // to socket
    iResult = bind(listenSocket, resultingAddress->ai_addr, (int)resultingAddress->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(resultingAddress);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Since we don't need resultingAddress any more, free it
    freeaddrinfo(resultingAddress);

    // Set listenSocket in listening mode
    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    printf("Server initialized, waiting for clients.\n");

    do
    {
        // Wait for clients and accept client connections.
        // Returning value is acceptedSocket used for further
        // Client<->Server communication. This version of
        // server will handle only one client.
        acceptedSocket = accept(listenSocket, NULL, NULL);

        if (acceptedSocket == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }
        
       
        do
        {
            
            char recvbuf[DEFAULT_BUFLEN] = "";
            // Receive data until the client shuts down the connection
            iResult = recv(acceptedSocket, recvbuf, DEFAULT_BUFLEN, 0);
            if (iResult > 0)
            {

                int i=circularBufferPush(recvbuf);

                printf("Message received from client: %s.message no. %d\n", recvbuf,i);
                  
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
        } while (iResult > 0);

        // here is where server shutdown loguc could be placed

    } while (1);

    // shutdown the connection since we're done
    iResult = shutdown(acceptedSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(acceptedSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(listenSocket);
    closesocket(acceptedSocket);
    WSACleanup();

    return 1;
}


int WorkerEcho(){

    semaphores_we[0] = CreateSemaphore(0, 0, 1, NULL);
    semaphores_we[1] = CreateSemaphore(0, 0, 1, NULL);
    semaphores_we[2] = CreateSemaphore(0, 0, 1, NULL);

    hPrint_1 = CreateThread(NULL, 0, &f1_we, &PARAM_1, 0, &print1_ID);
    hPrint_2 = CreateThread(NULL, 0, &f2_we, &PARAM_2, 0, &print2_ID);
    hPrint_3 = CreateThread(NULL, 0, &f3_we, &PARAM_3, 0, &print3_ID);
    // Socket used for listening for new clients 
    SOCKET listenSocket = INVALID_SOCKET;
    // Socket used for communication with client
    SOCKET acceptedSocket = INVALID_SOCKET;
    // variable used to store function return value
    int iResult;
    // Buffer used for storing incoming data
    char recvbuf[DEFAULT_BUFLEN];

    if (InitializeWindowsSockets() == false)
    {
        // we won't log anything since it will be logged
        // by InitializeWindowsSockets() function
        return 1;
    }

    // Prepare address information structures
    addrinfo* resultingAddress = NULL;
    addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;       // IPv4 address
    hints.ai_socktype = SOCK_STREAM; // Provide reliable data streaming
    hints.ai_protocol = IPPROTO_TCP; // Use TCP protocol
    hints.ai_flags = AI_PASSIVE;     // 

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT_WORKERECHO, &hints, &resultingAddress);
    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    listenSocket = socket(AF_INET,      // IPv4 address famly
        SOCK_STREAM,  // stream socket
        IPPROTO_TCP); // TCP

    if (listenSocket == INVALID_SOCKET)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(resultingAddress);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket - bind port number and local address 
    // to socket
    iResult = bind(listenSocket, resultingAddress->ai_addr, (int)resultingAddress->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(resultingAddress);
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Since we don't need resultingAddress any more, free it
    freeaddrinfo(resultingAddress);

    // Set listenSocket in listening mode
    iResult = listen(listenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    printf("Server initialized, waiting for clients.\n");

    do
    {
        // Wait for clients and accept client connections.
        // Returning value is acceptedSocket used for further
        // Client<->Server communication. This version of
        // server will handle only one client.
        acceptedSocket = accept(listenSocket, NULL, NULL);

        if (acceptedSocket == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        
            // Receive data until the client shuts down the connection
            iResult = recv(acceptedSocket, recvbuf, DEFAULT_BUFLEN, 0);
            if (iResult > 0)
            {
                int i = atoi(recvbuf);
                AddElement(i);
                printf("\nNew worker with port: %d succesfully added\n",i);
                //port_weMax[3], port_weMin[3], brojPoruka[3]
                while (1)
                {
                    int* niz = DistributionData();
                    if (niz[3] == 0)
                    {
                        port_weMax[j] = niz[0];
                        port_weMin[j] = niz[1];
                        brojPoruka[j] = niz[2];

                        ReleaseSemaphore(semaphores_we[j], 1, 0);

                        if (j == 2)
                        {
                            j = 0;
                        }
                        else
                        {
                            j++;
                        }
                    }
                    else
                    {
                        break;
                    }
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
        

        // here is where server shutdown loguc could be placed

    } while (1);

    // shutdown the connection since we're done
    iResult = shutdown(acceptedSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(acceptedSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(listenSocket);
    closesocket(acceptedSocket);
    WSACleanup();

    return 0;
}


bool InitializeWindowsSockets()
{
    WSADATA wsaData;
    // Initialize windows sockets library for this process
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed with error: %d\n", WSAGetLastError());
        return false;
    }
    return true;
}



