/* $begin alarm */
#include "csapp.h"

void handler(int sig)
{
    static int beeps = 0;

    printf("%d", sig);
    printf("BEEP\n");
    if (++beeps < 3)
        alarm(1); /* Next SIGALRM will be delivered in 1 second */
    else
    {
        printf("BOOM!\n");
        exit(0);
    }
}

int main()
{
    Signal(SIGALRM, handler); /* Install SIGALRM handler */
    alarm(1);                 /* Next SIGALRM will be delivered in 1s */

    while (1)
    {
        ; /* Signal handler returns control here each time */
    }
    exit(0);
}
/* $end alarm */
