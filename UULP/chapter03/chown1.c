/*
* 功能：模仿chown改变用户权限
* 用法：sudo ./chown1 username filename
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static char username[BUFSIZ];
uid_t name_to_uid(char *username);
void do_chown(char *username, char *filename);

int main(int argc, char *argv[])
{
    if (argc < 3)
        fprintf(stderr, "Usage:%s username filenae", argv[0]);
    else
    {
        strcpy(username, *++argv);
        //printf("%s\n", username);
        argc--;
        while (--argc > 0)
        {
            do_chown(username, *++argv);
            //printf("%s\n", *argv);
        }
    }
    return 0;
}

void do_chown(char *username, char *filename)
{
    uid_t uid;
    struct stat stbufp;
    if ((uid = name_to_uid(username)) == 0)
    {
        fprintf(stderr, "Canot find uid fo %s", username);
        exit(1);
    }
    if (stat(filename, &stbufp) == -1)
    {
        fprintf(stderr, "Cannot stat file: %s", filename);
        exit(1);
    }
    //printf("set_uid:%d, origin_uid: %d origin_gid:%d", uid, stbufp.st_uid, stbufp.st_gid);
    chown(filename, uid, stbufp.st_gid);
}
#include <pwd.h>
uid_t name_to_uid(char *username)
{
    struct passwd *pwd_ptr;
    uid_t id;
    while ((pwd_ptr = getpwnam(username)) == NULL)
    {
        id = 0;
        return id;
    }
    return pwd_ptr->pw_uid;
}