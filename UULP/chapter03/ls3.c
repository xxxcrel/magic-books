/* ls3.c
 *	purpose  list contents of directory or directories
 *	action   if no args, use .  else list files in args
 *	note     uses stat and pwd.h and grp.h 
 *	
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "syscall.h"
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

void do_ls(char *);
void show_file_info(char *, struct stat *);
void mode_to_letters(int, char *);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);
void ls_dir(char *);

int main(int argc, char *argv[])
{
    if (argc == 1)
        do_ls(".");
    else
        while (--argc)
        {
            printf("%s:\n", *++argv);
            do_ls(*argv);
        }
    return 0;
}

void do_ls(char *name)
/*
 *	list files in directory called dirname
 */
{
    struct stat stbuf;
    if(stat(name, &stbuf) == -1)
        perror(name);
    else if((stbuf.st_mode & __S_IFMT) == __S_IFDIR)
        ls_dir(name);
    else
        show_file_info(name, &stbuf);

}

void ls_dir(char *dirname)
{
    char name[1024];
    struct dirent *dp;
    DIR *dfd;
    struct stat stbuf;
    if((dfd = opendir(dirname)) == NULL)
        perror(dirname);
    while((dp = readdir(dfd)) != NULL)
    {
        if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        else 
        {
            sprintf(name, "%s/%s", dirname, dp->d_name);
            if(stat(name, &stbuf) == -1)
                perror(name);
            else 
                show_file_info(dp->d_name, &stbuf);
        }
    }
    closedir(dfd);
}

void show_file_info(char *filename, struct stat *info_p)
/*
 * display the info about 'filename'.  The info is stored in struct at *info_p
 */
{
    char modestr[11];
    mode_to_letters(info_p->st_mode, modestr);

    printf("%s", modestr);
    printf("%4d ", (int)info_p->st_nlink);
    printf("%-8s ", uid_to_name(info_p->st_uid));
    printf("%-8s ", gid_to_name(info_p->st_gid));
    printf("%8ld ", (long)info_p->st_size);
    printf("%.12s ", 4 + ctime(&info_p->st_mtime));
    printf("%s\n", filename);
}
/*
 * utility functions
 */

/*
 * This function takes a mode value and a char array
 * and puts into the char array the file type and the 
 * nine letters that correspond to the bits in mode.
 * NOTE: It does not code setuid, setgid, and sticky
 * codes
 */
void mode_to_letters(int mode, char str[])
{
    strcpy(str, "----------"); /* default=no perms */

    if (S_ISDIR(mode))
        str[0] = 'd'; /* directory?       */
    if (S_ISCHR(mode))
        str[0] = 'c'; /* char devices     */
    if (S_ISBLK(mode))
        str[0] = 'b'; /* block device     */

    if (mode & S_IRUSR)
        str[1] = 'r'; /* 3 bits for user  */
    if (mode & S_IWUSR)
        str[2] = 'w';
    if (mode & S_IXUSR)
        str[3] = 'x';

    if (mode & S_IRGRP)
        str[4] = 'r'; /* 3 bits for group */
    if (mode & S_IWGRP)
        str[5] = 'w';
    if (mode & S_IXGRP)
        str[6] = 'x';

    if (mode & S_IROTH)
        str[7] = 'r'; /* 3 bits for other */
    if (mode & S_IWOTH)
        str[8] = 'w';
    if (mode & S_IXOTH)
        str[9] = 'x';
}
#include <pwd.h>

char *uid_to_name(uid_t uid)
/* 
 *	returns pointer to username associated with uid, uses getpw()
 */
{
    struct passwd *getpwuid(), *pw_ptr;
    static char numstr[10];

    if ((pw_ptr = getpwuid(uid)) == NULL)
    {
        sprintf(numstr, "%d", uid);
        return numstr;
    }
    else
        return pw_ptr->pw_name;
}

#include <grp.h>

char *gid_to_name(gid_t gid)
/*
 *	returns pointer to group number gid. used getgrgid(3)
 */
{
    struct group *getgrgid(), *grp_ptr;
    static char numstr[10];

    if ((grp_ptr = getgrgid(gid)) == NULL)
    {
        sprintf(numstr, "%d", gid);
        return numstr;
    }
    else
        return grp_ptr->gr_name;
}