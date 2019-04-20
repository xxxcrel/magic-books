#include <stdio.h>
#include <string.h>

int getline(char line[], int lim);
void reverse(char s[]);

main()
{
    char s[1000];
    while(getline(s, 1000) > 0)
    {
        reverse(s);
        printf("%s", s);
    }
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

void reverse(char s[])
{
    int i, j;
    j = 0;
    while(s[j] != '\0')
        ++j;
    --j;   //back off from '\0'
    if(s[j] == '\n')
        --j;
    i = 0;
    while(i < j)
    {
        char temp = s[i];
        s[i++] = s[j];
        s[j--] = temp;
    }
}