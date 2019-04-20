#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void display(FILE *, FILE *);
void oops(const char *, const char *);

int main(int argc, const char *argv[])
{
    if (argc == 1)
    {
        display(stdin, stdout);
        exit(0);
    }
    FILE *fp;
    while (--argc)
    {
        if ((fp = fopen(*++argv, "r")) == NULL)
            oops("Cannot open file", *argv);
        printf("==> %s <==\n", *argv);
        display(fp, stdout);
        if(fclose(fp) == -1)
            oops("Closing file error", *argv);
    }
    return 0;
}

void display(FILE *from, FILE *to)
{
    char buf[BUFSIZ];
    while(fgets(buf, BUFSIZ, from) != NULL)
        fputs(buf, to);
}

void oops(const char *s1, const char *s2)
{
    fprintf(stderr, "Error:%s", s1);
    perror(s2);
    exit(1);
}