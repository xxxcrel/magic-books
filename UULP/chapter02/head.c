#include <stdio.h>
#include <stdlib.h>

#define LINELEN 80
#define HEADLENS 10

void do_head(FILE *, FILE *);
void oops(const char *, const char *);

int main(int argc, const char *argv[])
{
    if(argc == 1)
        do_head(stdin, stdout);
    FILE *fp;
    while(--argc)
    {
        if((fp = fopen(*++argv, "r")) == NULL)
            oops("Cannot open file", *argv);
        printf("==> %s <==\n", *argv);
        do_head(fp, stdout);
        if(fclose(fp) == -1)
            oops("Closing file error", *argv);
    }
    return 0;
}

void do_head(FILE *from, FILE *to)
{
    
    char buf[LINELEN];
    long headlens = HEADLENS;
    while(fgets(buf, LINELEN, from) != NULL && headlens--)
        fputs(buf, stdout);
}
void oops(const char *s1, const char *s2)
{
    fprintf(stderr, "Error:%s", s1);
    perror(s2);
    exit(1);
}