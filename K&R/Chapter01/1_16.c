#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int maxline);
void copy(char to[], char from[]);

main()
{
    int len;               //current line length
    int max;               //maximum length seeen so far
    char line[MAXLINE];    //current input line
    char longest[MAXLINE]; //longest line saved here

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0)
    {
        printf("%d, %s", len, line);
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0)
        printf("%s", longest);
}

int getline(char s[], int lim)
{
    int c, i, j;
    j = 0;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
    {
        if (i < lim - 2)//lim - 2 because we need add '\n' and '\0' within the limits
        {
            s[j] = c;
            ++j;
        }
    }
    if (c == '\n')
    {
        s[j] = '\n';
        ++i;//because the array subscript starts from 0, so the length need plus one
        ++j;
    }
    s[j] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i;
    i = 0;
    while((to[i] = from[i]) != '\0')//!!!  '\0' is also copy to the 'to[]' array
        ++i;
}