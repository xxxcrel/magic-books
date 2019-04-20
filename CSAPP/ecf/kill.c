/* $begin kill */
#include "csapp.h"

int main()
{
    pid_t pid;

    /* Child sleeps until SIGKILL signal received, then dies */
    if ((pid = Fork()) == 0)
    {
        printf("I'm child\n");
        Pause(); /* Wait for a signal to arrive */
        printf("control should never reach here!\n");
        exit(0);
    }

    /* Parent sends a SIGKILL signal to a child */
    printf("I'm parent and i will kill my child process\n");
    Kill(pid, SIGKILL);
    exit(0);
}
/* $end kill */
