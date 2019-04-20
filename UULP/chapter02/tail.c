#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define LINELENS BUFSIZ
#define TAILLENS 10

void do_tail(FILE *, FILE *);
void oops(const char *, const char *);
int get_offset(FILE *);
int get_line(char *, int, FILE *);
void updateTen(int[], int);

int main(int argc, const char *argv[])
{
    if(argc == 1)
    {
        int c;
        while((c = getc(stdin)) != EOF)
            putc(c, stdout);
        exit(0);
    }
    FILE *fp;
    while(--argc)
    {
        if((fp = fopen(*++argv, "r")) == NULL)
            oops("Cannot open file", *argv);
        do_tail(fp, stdout);
        if(fclose(fp) == -1)
            oops("Closing file error", *argv);
    }
    return 0;
}

void do_tail(FILE *from, FILE *to)
{
    char buf[LINELENS];
    long taillens = TAILLENS;
    int offset = get_offset(from);
    //printf("%d", offset);
    fseek(from, -offset, SEEK_END);
    while(fgets(buf, BUFSIZ, from) != NULL)
        fputs(buf, to);
}

int get_offset(FILE *fp)
{
    int cnt = 0, ret = 0;
    char buf[BUFSIZ];
    long lensOfTail = 0;
    int ten[10] = {0};
    while((ret = get_line(buf, BUFSIZ, fp)) != 0)
    {
        lensOfTail += ret;
        if(cnt < 10)
            ten[cnt] = ret;
        else
        {
            lensOfTail -= ten[0];
            updateTen(ten, ret);
        }
        cnt++;
    }
    return lensOfTail;
}

void updateTen(int ten[], int new)
{
    int i;
    for(i = 0; i < 9; i++)
        ten[i] = ten[i + 1];
    ten[i] = new;
}
int get_line(char *buf, int len, FILE *fp)
{
    if(fgets(buf, len, fp) == NULL)
        return 0;
    else 
        return strlen(buf);
}
void oops(const char *s1, const char *s2)
{
    fprintf(stderr, "Error:%s", s1);
    perror(s2);
    exit(1);
}