#pragma once
#ifndef Communication
#define Communaction

int ClientLink();




int WorkerEcho();

int SendToWorker(int port, char msg[]);

//int WorkerLink();

#endif