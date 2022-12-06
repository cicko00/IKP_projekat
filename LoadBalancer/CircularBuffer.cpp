#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 1024

//struktura
struct circular_buffer
{
	const char* buffer[BUFFER_SIZE];
	int push;
	int pop;
	int count;
};


struct circular_buffer* cb = NULL;
//pushovanje podataka u bafer


int circularBufferPush( const char* data)
{
	if (cb->count == BUFFER_SIZE)
	{
		return -1;
	}

	cb->buffer[cb->push] = data;  //stavi se podatak u kruzni bafer
	cb->push++;  //pokazivac se pomeri za +1

	if (cb->push == BUFFER_SIZE) //kruzni bafer je pun
	{
		cb->push = 0;    //sada je pokazivac opet na nultom mesto, jer je stigao do kraja
	}

	cb->count++;   //upisan je podatak, counter se poveca za jedan
}



//skidanje podataka
int circularBufferPop(const char* data)
{
	if (cb->count == 0) //nemamo elemenata u baferu
	{
		return -1;
	}

	data = cb->buffer[cb->pop];  //iscitam u suprotnom
	cb->pop++;

	if (cb->pop == BUFFER_SIZE)
	{
		cb->pop = 0;
	}

	cb->count--;  //umanji se brojac za jedan
}