#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define STDIN_FD 0
#define STDOUT_FD 1
void display(int in_fd, int out_fd);
void display_nobuf(int in_fd, int out_fd);
void oops(const char *, const char *);

int main(int argc, const char *argv[])
{
    if (argc == 1)
    {
        display(STDIN_FD, STDOUT_FD);
        exit(0);
    }
    int in_fd = -1;
    while(--argc)
    {
        if((in_fd = open(*++argv, O_RDONLY)) == -1)
            oops("Cannot open file", *argv);
        printf("==> %s <==\n", *argv);
        display_nobuf(in_fd, STDOUT_FD);
        if(close(in_fd) == -1)
            oops("Closing file error", "");
    }
    return 0;
}

void display(int in_fd, int out_fd)
{
    int n_chars = 0;
    char buf[BUFSIZ];
    while((n_chars = read(in_fd, buf, BUFSIZ)) > 0)
        write(out_fd, buf, n_chars);
}

void display_nobuf(int in_fd, int out_fd)
{   
    char c;
    while(read(in_fd, &c, 1))
        write(out_fd, &c, 1);
        
}
void oops(const char *s1, const char *s2)
{
    fprintf(stderr, "Error:%s", s1);
    perror(s2);
    exit(1);
}