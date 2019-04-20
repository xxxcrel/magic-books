#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

//#define SHOWHOST

void show_info(struct utmp *);
void show_user_name(struct utmp *);
void show_time(long);

int main(int argc, char *argv[])
{
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);
    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1)
    {
        perror(UTMP_FILE);
        exit(1);
    }
    while (read(utmpfd, &current_record, reclen) == reclen)
        if(argc == 1)
            show_info(&current_record);
        else if(argc == 3 && strcmp(argv[1], "am") == 0 && strcmp(argv[2], "i") == 0)
            show_user_name(&current_record);
    close(utmpfd);
    return 0;
}
//for who am i 
void show_user_name(struct utmp *utbufp)
{
    if (utbufp->ut_type != USER_PROCESS)
        return;
    printf("%-8.8s", utbufp->ut_name);
    printf("\n");
}

void show_info(struct utmp *utbufp)
{
    if (utbufp->ut_type != USER_PROCESS)
        return;
    printf("%-8.8s", utbufp->ut_name);
    printf(" ");
    printf("%-8.8s", utbufp->ut_line);
    printf(" ");
    show_time(utbufp->ut_time);
#ifdef SHOWHOST
    printf("( %s )", utbufp->ut_host);
#endif
    printf("\n");
}

void show_time(long timeval)
{
    char *cp;
    cp = ctime(&timeval);
    printf("%12.12s", cp + 4);
}