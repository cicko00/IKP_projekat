#pragma once
#ifndef  CircularBuffer
#define CircularBuffer


int circularBufferPush(const char* data);

const char* circularBufferPop();

bool bufferCheck();

void cleanCirclBuffer();
#endif // ! CircularBuffer

