/* ls2.c
 * 功能：列出目录的文件信息，如果没有给定参数，则执行当前的目录
 * 缺陷：不能列出单个文件的信息，只能作用于目录
 * ---2019.4.8新增---
 * ls -R 选项 递归的列出子目录的文件信息
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

void do_ls(char[]);
void dostat(char *);
void show_file_info(char *, struct stat *);
void mode_to_letters(int, char[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int argc, char *argv[])
{
    if (argc == 1)
        do_ls(".");
    else
        while (--argc)
        {
            argv++;
            do_ls(*argv);
        }
    return 0;
}

void do_ls(char dirname[])
/*
 *	list files in directory called dirname
 */
{
    printf("%s:\n", dirname);
    DIR *dir_ptr;           /* the directory */
    struct dirent *direntp; /* each entry	 */
    struct stat stbuf; /*file info */
    char absname[BUFSIZ];
    if ((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "ls2: cannot open %s\n", dirname);
    else
    {
        while ((direntp = readdir(dir_ptr)) != NULL)
        {
            if(strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
                continue;
            sprintf(absname, "%s/%s", dirname, direntp->d_name);//get absloute path of file  eg:/tmp/filename
            if(stat(absname, &stbuf) == -1)
                perror(absname);
            else if((stbuf.st_mode & __S_IFMT) == __S_IFDIR)//find a director continue to ls contents of this directory
                do_ls(absname);
            else 
                show_file_info(direntp->d_name, &stbuf);
        }
        closedir(dir_ptr);
    }
}

void show_file_info(char *filename, struct stat *info_p)
/*
 * display the info about 'filename'.  The info is stored in struct at *info_p
 */
{
    void mode_to_letters();
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