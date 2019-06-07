#include <stdio.h>

main()
{
    int nBlanks;
    int c;
    while((c = getchar()) != EOF)
    {
        if(c == ' ')
            ++nBlanks;
        else
        {
            if(nBlanks > 0)
            {
                putchar(' ');
                nBlanks = 0;
            }
            putchar(c);
        }
    }
}