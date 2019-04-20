#include"queue.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
	Queue Q;
	Q = CreatQueue();
	ElementType Ch;
	printf("Please enter the queue element,end of '#':");
	while((Ch = getchar()) != '#'){
		Enqueue(Q, Ch);
	}
	getchar();

	ElementType In;
	printf("Please enter the element you want insert:");
	In = getchar();
	getchar();
	Enqueue(Q, In);
	PrintQueue(Q);
	printf("The rear element is %c\n", Q->Rear->Element);
	printf("The front element is %c\n", Q->Front->Element);

	ElementType Out;
	printf("Now Dequeue the front element\n");
	Dequeue(Q);
	PrintQueue(Q);
	printf("The rear element is %c\n", Q->Rear->Element);
	printf("The front element is %c\n", Q->Front->Element);

	ElementType Front;
	Front = FrontAndDequeue(Q);
	printf("%c\n", Front);
	PrintQueue(Q);

	return 0;
}
