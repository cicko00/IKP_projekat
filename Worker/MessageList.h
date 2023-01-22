#pragma once
#ifndef MessageList
#define MessageList

void MessageListAddElement(const char* message);

const char* MessageListTakeElement();
void PrintAll();

void clearMsgList();
#endif // MessageList