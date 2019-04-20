#include <ctype.h>
#include <stdio.h>
#define MAXCHAR 128
#define MAXLINE 30

int main(int argc, char const *argv[])
{
    for (int i = 0; i < MAXLINE; ++i)
    {
        for (int j = i; j < MAXCHAR; j += MAXLINE)
        {
            if (!isprint(j))
                printf("%4d |   |", j);
            else
                printf("%4d | %c |", j, j);
        }
        putchar('\n');
    }
    return 0;
}
