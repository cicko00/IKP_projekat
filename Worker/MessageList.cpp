#include "MessageList.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ws2tcpip.h>
struct messagelist
{
	char message[1024];
	messagelist* head;
};

struct messagelist* first = NULL;
struct messagelist* last = NULL;
struct messagelist* NEW = NULL;

void MessageListAddElement(const char* message)
{
	 NEW = (struct messagelist*)malloc(sizeof(struct messagelist));

	if (first == NULL)
	{
		first = NEW;
		NEW->head = NULL;
	}
	else
	{
		NEW->head = last;
	}
	strcpy_s(NEW->message, message);
	
	last = NEW;
}

const char* MessageListTakeElement()
{
	if (first == NULL)
	{
		return "";
	}
	
	else
	{
		const char* message = last->message;
		while (last->head == NULL) {
			Sleep(10);
		}
		last = last->head;
		
		return message;
	}
	
	
}

void PrintAll()
{
	int cnt = 0;
	struct messagelist* ml = last;
	if (ml == NULL)
	{
		return;
	}
	while (1)
	{
		printf("PORUKA: %s\n", ml->message);
		cnt++;
		if (ml == first)
		{
			printf("\n\n\nUKUPAN BROJ PORUKA: %d", cnt);
			return;
		}
		ml = ml->head;
	}
}


void clearMsgList() {
	free(NEW);
	
	
	
}

