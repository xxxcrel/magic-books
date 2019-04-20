#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define STDIN_FD 0
#define STDOUT_FD 1
#define LINELEN 80
#define HEADLENS 10

void do_head(int in_fd, int out_fd);
void oops(const char *, const char *);
int read_line(int, int, char *);

int main(int argc, const char *argv[])
{
    if (argc == 1)
        do_head(STDIN_FD, STDOUT_FD);
    int in_fd;
    while (--argc)
    {
        if ((in_fd = open(*++argv, O_RDONLY)) == -1)
            oops("Cannot open file ", *argv);
        printf("==> %s <==\n", *argv);
        do_head(in_fd, 1);
        if (close(in_fd) == -1)
            oops("Closing file error ", *argv);
    }
    return 0;
}

void do_head(int in_fd, int out_fd)
{
    char buf[BUFSIZ];
    long n_chars;
    int headlens = HEADLENS;
    while(headlens-- && (n_chars = read_line(in_fd, BUFSIZ, buf)) > 0)
        write(out_fd, buf, n_chars);   
}

int read_line(int in_fd, int n, char *buf)
{
    char c;
    char *cs = buf;
    while (--n > 0 && read(in_fd, &c, 1))
        if ((*cs++ = c) == '\n')
            break;
    *cs = '\0';
    return strlen(buf);
}
void oops(const char *s1, const char *s2)
{
    fprintf(stderr, "Error:%s", s1);
    perror(s2);
    exit(1);
}