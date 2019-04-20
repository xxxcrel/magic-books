#include"queue.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	Queue Q;
	int MaxQueueSize;
	printf("Please enter the maxqueuesize of queue:");
	scanf("%d", &MaxQueueSize);
	getchar();//dispose of newline
	Q = CreatQueue(MaxQueueSize);

	ElementType QE[MaxQueueSize];
	printf("Please enter the queue element，end of '#':");
	int i;
	for(i = 0; (QE[i] = getchar()) != '#'; i++){
		Enqueue(Q, QE[i]);
    }

    ElementType front;
    Dequeue(Q);
    front = Front(Q);
    printf("After Dequeue the front element is : %c\n", front);

    front = FrontAndDequeue(Q);
    printf("After FrontAndQueue the front element is : %c\n", front);
    front = Front(Q);
    printf("%c\n", front);

    return 0;
}
