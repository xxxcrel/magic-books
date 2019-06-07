#include <stdio.h>
#define TABINC 8

main()
{
    int c, nb, nt, pos;
    nb = 0;
    nt = 0;
    for (pos = 1; (c = getchar()) != EOF; ++pos)
    {
        if(c == ' ')
        {
            if(pos % TABINC != 0)
                ++nb;
            else
            {
                nb = 0;
                ++nt;
            }
        }
        else
        {
            for (; nt > 0; --nt)    //out tab(s)
                putchar('\t');
            if (c == '\t')      //forget the blank(s)
                nb = 0;
            else
                for (; nb > 0; --nb)  // output blank(s)
                    putchar(' ');
            putchar(c);
            if (c == '\n')
                pos = 0;     //reset position
            else if (c == '\t')
                pos = pos + (TABINC - (pos - 1) % TABINC) - 1;
        }
    }
}