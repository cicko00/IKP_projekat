#include "WorkerList.h"
#include <stdio.h>
#include <stdlib.h>

struct node {
	int port;
	int data_count=0;
	struct node *head=NULL;
};



struct node* first =NULL;
struct node* current = NULL;


void AddElement(int port)
{
	struct node* NEW = (struct node*)malloc(sizeof(struct node));
	NEW->port = port;
	NEW->data_count = 0;
	

	if(first==NULL){
		NEW->head = NULL;
		first = NEW;
		
		
	}
	else {
		NEW->head = current;
	}

	current = NEW;


}

void AddData(int port){

	if (first == NULL) {
		return;
	}
	struct node* s = current;

	while (1) {
		if (s->port == port) {
			s->data_count++;
			break;
		}
		if (s->head == NULL) {
			break;
		}
		s = s->head;

	}

	

}

int findMin() {
	struct node* s = current;
	int port = NULL;
	int minVal = INT_MAX;



	while (1) {
		if (s->data_count <= minVal) {
			minVal = s->data_count;
			port = s->port;


		}
		if (s->head == NULL) {
			return port;

		}
		s = s->head;

	}
}



void PrintList(){
		printf("LISTA:\n\n\n");
		struct node* s = current;
		int cnt = 1;
		while (1) {
			
			printf("%d :port=%d  Data:%d  \n",cnt,s->port,s->data_count);
			cnt++;
			if (s->head == NULL) {
				return;

			}
			s = s->head;

		}



}


int* DistributionData()
{
	int niz[3];
	int prom = 0;
	int flag;
	int min = INT_MAX;
	int max = 0;
	struct node* maxEl;
	struct node* minEl;
	int portMin = 0;
	int portMax = 0;
	struct node* str = current;

	while (1) {
		if (str->data_count <= min) {
			min = str->data_count;
			portMin = str->port;
			minEl = str;
		}
		if (str->data_count >= max)
		{
			max = str->data_count;
			portMax = str->port;
			maxEl = str;
		}
		if (str->head == NULL) {
			break;
		}
		str = str->head;
	}
	if ((max - min) > 1)
	{
		prom = (max - min) / 2;
		minEl->data_count -= prom;
		maxEl->data_count += prom;
		flag = 0;
	}
	else
	{
		flag = 1;
	}
	niz[0] = portMin;
	niz[1] = prom;
	niz[2] = flag;
}




	

