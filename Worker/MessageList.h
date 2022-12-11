#pragma once
#ifndef MessageList
#define MessageList

void MessageListAddElement(const char* message);

const char* MessageListTakeElement();
void ListTest();

#endif // MessageList