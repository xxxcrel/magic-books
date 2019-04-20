#include <stdio.h>
#include <stdlib.h>
#include <utmp.h>
#include <fcntl.h>
#include <features.h>
#include <unistd.h>
#include <time.h>
#include <paths.h>

//#define SHOWHOST

void show_info(struct utmp *);
void show_start_time(long);
void show_end_time(long);
static char *sys = "system boot";

int main()
{
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);
    if((utmpfd = open(WTMP_FILE, O_RDONLY)) == -1)
    {
        perror(UTMP_FILE);
        exit(1);
    }
    printf("[t] [ pid ] [ id  ] [ name ] [   line   ] [    host    ]    [  time  ]\n");
    while (read(utmpfd, &current_record, reclen) == reclen)
        show_info(&current_record);
    close(utmpfd);
    return 0;    
}

void show_info(struct utmp *utbufp)
{
    if(utbufp->ut_type != BOOT_TIME && utbufp->ut_type != USER_PROCESS && utbufp->ut_type != DEAD_PROCESS)
        return;
    printf("[%d]", utbufp->ut_type);
    printf(" ");
    printf("[%5d]", utbufp->ut_pid);
    printf(" ");
    printf("[%5s]", utbufp->ut_id);
    printf(" ");
    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-12.12s", utbufp->ut_line);
    printf(" ");
    printf("%-18.18s", utbufp->ut_host);
    show_start_time(utbufp->ut_time);
    #ifdef SHOWHOST
    printf("( %s )", utbufp->ut_host);
    #endif
    printf("\n");
}

void show_start_time(long timeval)
{
    char *cp;
    cp = ctime(&timeval);
    printf("%12.12s", cp + 4);
}

void show_end_time(long timeval)
{
    char *cp;
    cp = ctime(&timeval);
    printf("%12.12s", cp + 4);
}