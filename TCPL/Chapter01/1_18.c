#include <stdio.h>
#define MAXLINE 1000

int getline(char line[], int MAXLINE);
int remove(char s[]);

main()
{
    char line[MAXLINE];

    while(getline(line, MAXLINE) > 0)
        if(remove(line) > 0)
            printf("%s", line);
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

int remove(char s[])
{
    int i;
    i = 0;

    while(s[i] != '\n')  //find newline character
        ++i;
    --i; //back off from '\n'
    while(i >= 0 && (s[i] == ' ' || s[i] == '\t'))
        --i;
    if(i >= 0)
    {
        ++i; //is it a nonblank line?
        s[i] = '\n';
        ++i;
        s[i] = '\0';
    }
    return i;
}