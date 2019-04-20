#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>

#define CPOYMODE 0644

void oops(char *, char *);
void do_cp(char *from, char *to);

int main(int argc, char *argv[])
{

    if (argc != 3)
    {
        fprintf(stderr, "Usage:%s src dest", argv[0]);
        exit(1);
    }
    if (strcmp(argv[1], argv[2]) == 0)
    {
        fprintf(stderr, "%s: \'%s\' and \'%s\' are the same file\n", argv[0], argv[1], argv[2]);
        exit(1);
    }
    int prompt;
    struct stat stbuf;
    char name[BUFSIZ];
    // if((prompt = open(argv[2], O_RDONLY)) != -1)
    // {
    //     printf("%s: overwrite \'%s\'?", argv[0], argv[2]);
    //     while((c = getchar()) != EOF)
    //     {
    //         if(c == 'y' || c == 'Y')
    //         {
    //             do_cp(argv[1], argv[2]);
    //             exit(0);
    //         }
    //         if(c == 'n' || c == 'N')
    //             exit(1);
    //     }
    // }
    if (stat(argv[2], &stbuf) != -1)
    {
        if ((stbuf.st_mode & __S_IFMT) == __S_IFDIR)
        {
            sprintf(name, "%s/%s", argv[2], argv[1]);
            do_cp(argv[1], name);
        }
        else if((stbuf.st_mode & __S_IFMT) == __S_IFREG)
        {
            int c;
            printf("%s: overwrite \'%s\' ?", argv[0], argv[2]);
            while((c = getchar()) != EOF)
            {
                if(c == 'y' || c == 'Y')
                {
                    do_cp(argv[1], argv[2]);
                    exit(0);
                }
                if(c == 'n' || c == 'N')
                    exit(1);
            }
        }
    }
    else
        do_cp(argv[1], argv[2]);

    return 0;
}

void do_cp(char *from, char *to)
{
    char buf[BUFSIZ];
    int n_chars;
    int infd, outfd;
    if ((infd = open(from, O_RDONLY)) == -1)
        oops("Cannot open file ", from);
    if ((outfd = creat(to, CPOYMODE)) == -1)
        oops("Cannot creat file ", to);
    while ((n_chars = read(infd, buf, BUFSIZ)) > 0)
        if (write(outfd, buf, n_chars) != n_chars)
            oops("Write error to ", to);
    if (n_chars == -1)
        oops("Rear error from", to);
    if (close(infd) == -1 || close(outfd) == -10)
        oops("Error closing files", "");
}
void oops(char *s1, char *s2)
{
    fprintf(stderr, "Error:%s", s1);
    perror(s2);
    exit(1);
}