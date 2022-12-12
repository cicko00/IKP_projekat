#include "WorkerList.h"
#include <stdio.h>
#include <stdlib.h>

struct node {
	int port_RD;
	int port_SD;
	int data_count=0;
	struct node *head=NULL;
};

struct node* first =NULL;
struct node* current = NULL;


void AddElement(int port_RD,int port_SD)
{
	struct node* NEW = (struct node*)malloc(sizeof(struct node));
	NEW->port_RD = port_RD;
	NEW->port_SD = port_SD;
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

void AddData(int port_RD){

	if (first == NULL) {
		return;
	}
	struct node* s = current;

	while (1) {
		if (s->port_RD == port_RD) {
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
			port = s->port_RD;


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
			
			printf("%d :port=%d  Data:%d  \n",cnt,s->port_RD,s->data_count);
			cnt++;
			if (s->head == NULL) {
				return;

			}
			s = s->head;

		}
}

int* DistributionData()
{

	int niz[4];
	int prom = 0;
	int flag;
	int min = INT_MAX;
	int max = 0;
	struct node* maxEl = NULL;
	struct node* minEl = NULL;
	int portMin = 0;
	int portMax = 0;
	struct node* str = current;

	while (1) {
		if (str->data_count <= min) {
			min = str->data_count;
			portMin = str->port_RD;
			minEl = str;
		}
		if (str->data_count >= max)
		{
			max = str->data_count;
			portMax = str->port_SD;
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
		minEl->data_count += prom;
		maxEl->data_count -= prom;
		flag = 0;
	}
	else
	{
		flag = 1;
	}
	niz[0] = portMax;
	niz[1] = portMin;
	niz[2] = prom;
	niz[3] = flag;

	return niz;
}




	

