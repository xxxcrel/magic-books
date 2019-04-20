#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *de;
    if (argc == 1)
        dp = opendir(".");
    else
        dp = opendir(*++argv);
    while ((de = readdir(dp)) != NULL)
    {
        if (de->d_ino == 0)
            continue;
        printf("i_no:%ld\n", de->d_ino);
        printf("d_name:%s\n", de->d_name);
        printf("d_type:%c\n", de->d_type);
        printf("d_reclen:%d\n", de->d_reclen);
    }
    closedir(dp);
}