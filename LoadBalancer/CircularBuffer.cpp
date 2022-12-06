#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024

//struktura
struct circular_buffer
{
	 char buffer[30][BUFFER_SIZE];
	 int push;       //index za upis
	int pop;		//index za citanje
	int push_count; //ukupan broj dodatih poruka
	int pop_count; //ukupan broj procitanih poruka
	
};


struct circular_buffer* cb = NULL;
//pushovanje podataka u bafer


int circularBufferPush( const char* data)
{

	if (cb == NULL) {
		cb = (struct circular_buffer*)malloc(sizeof(struct circular_buffer));
		cb->push = 0;
		cb->pop = 0;
		cb->push_count = 0;
		cb->pop_count = 0;
		
	}
	


	strcpy_s(cb->buffer[cb->push], data);  //stavi se podatak u kruzni bafer
	cb->push++;  //pokazivac se pomeri za +1
	cb->push_count++;

	if (cb->push == BUFFER_SIZE) //kruzni bafer je pun
	{
		cb->push = 0;    //sada je pokazivac opet na nultom mesto, jer je stigao do kraja
	}
	return cb->push_count;
	   //upisan je podatak, counter se poveca za jedan
}



//skidanje podataka
const char* circularBufferPop()
{

	if (cb == NULL) {
		return "";
		
	}


	if (cb->pop_count>=cb->push_count) //nemamo elemenata u baferu
	{
		return "";
	}

	const char* data = cb->buffer[cb->pop];  //iscitam u suprotnom
	cb->pop++;
	cb->pop_count++;

	if (cb->pop == BUFFER_SIZE)
	{
		cb->pop = 0;
	}

	
	return data;
}

bool bufferCheck() {
	if (cb == NULL) {
		cb = (struct circular_buffer*)malloc(sizeof(struct circular_buffer));
		cb->push = 0;
		cb->pop = 0;
		cb->push_count = 0;
		cb->pop_count = 0;

	}


	if (cb->pop_count < cb->push_count) {
		return true;
	}
	else {
		return false;
	}
}