#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void write_end();
void oops(char *, char *);

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s file\n", *argv);
        exit(1);
    }
    write_end(*argv[1]);
    return 0;
}

void write_end(char *c_file)
{
    int fd;
    if((fd = open(c_file, O_WRONLY)) == -1)
        oops("Cannot open", c_file);
    if((lseek(fd, 1000, SEEK_END) == -1))
        oops("Cannot seek", c_file);
    if((write(fd, "hello", 6) == -1))
        oops("Cannot write", c_file);
}

void oops(char *s1, char *s2)
{
    fprintf(stderr, "Error: %s", s1);
    perror(s2);
    exit(1);
}