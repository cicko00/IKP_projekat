#include "MessageList.h"
#include <stdio.h>
#include <stdlib.h>

struct messagelist
{
	const char* message;
	messagelist* head;
};

struct messagelist* first = NULL;
struct messagelist* last = NULL;

void MessageListAddElement(const char* message)
{
	struct messagelist* NEW = (struct messagelist*)malloc(sizeof(struct messagelist));

	if (first == NULL)
	{
		first = NEW;
		NEW->head = NULL;
	}
	else
	{
		NEW->head = last;
	}
	NEW->message = message;
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
		last = last->head;
		return message;
	}
}

void ListTest()
{
	struct messagelist* ml = last;
	if (ml == NULL)
	{
		return;
	}
	while (1)
	{
		printf("PORUKA: %s\n", ml->message);
		if (ml == first)
		{
			return;
		}
		ml = ml->head;
	}
}