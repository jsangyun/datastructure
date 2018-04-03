//for visual studio 2013(fscanf_s problem)

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <stdlib.h>

 

#define MAX_QUEUE_SIZE 5

typedef int element;

typedef struct {

	element queue[MAX_QUEUE_SIZE ];

	int front, rear;

} QueueType;

 

void init(QueueType *q);

void error(char *message);

int is_empty(QueueType *q);  

int is_full (QueueType *q); 

void enqueue( QueueType *q, element item );

element dequeue(QueueType *q);

element peek(QueueType *q);

 

int main(int argc, char *argv[])

{

 

	char command;

	int key;

	FILE *input;

	

	input = fopen(argv[1], "r");

	

	QueueType *queue = (QueueType*)malloc(sizeof(QueueType));

	init(queue);
	

	while(1){

		command = fgetc(input);

		if(feof(input)) break;

		switch(command){

			case 'e':

				fscanf(input, "%d", &key);

				enqueue(queue, key);
				break;

			

			case 'd':

				dequeue(queue);
				break;

				

			case 'p':

				peek(queue);
				break;

		}

	}

    fclose(input);

    return 0;

}

 

void error(char *message)

{

        fprintf(stderr,"%s\n",message);

        exit(1);

}

 

 

void init(QueueType *q)

{

	q->front = 0;

	q->rear = 0;

  printf("init front = %d, rear = %d\n", q->front, q->rear);
}

 

int is_empty(QueueType *q)

{

	if(q->front >= q->rear){

		return 1;

	}

	else{

		return 0;

	}

}

 

int is_full (QueueType *q)

{

	if(q->rear == MAX_QUEUE_SIZE-1){

		return 1;

	}

	else{

		return 0;

	}

}

 

void enqueue( QueueType *q, element item )

{

	if(is_full(q) == 1){
    
		printf("Queue is full\n");

	}

	else{
		q->rear++;

		q->queue[q->rear] = item;

		printf("enqueue() = %d\n", item);
		
		
    printf("front = %d, rear = %d\n", q->front, q->rear);

	}	

}

 

element dequeue(QueueType *q)

{

	if(is_empty(q) == 1){

		printf("Queue is empty\n");

	}

	else{

		q->front++;


		printf("dequeue() = %d\n", q->queue[q->front]);
		
		printf("front = %d, rear = %d\n", q->front, q->rear);
	}

}

 

element peek(QueueType *q)

{

	if(is_empty(q)){

		printf("Queue is empty\n");

	}

	else{

		printf("%d\n", q->queue[q->front+1]);

	}

}
