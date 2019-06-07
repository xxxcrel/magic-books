#include <stdio.h>
#define MAXHIST 15 // max length of histogram
#define MAXWORD 11 // max length of a word
#define IN 1       // inside a word
#define OUT 0      // outside a word

main()
{
    int c, i, j, nc, state;
    int len;         // length of each bar
    int maxvalue;    //maximum value for wl[]
    int overflow;    //number of voerflow words
    int wl[MAXWORD]; //word lenghts counter

    state = OUT;
    nc = 0;
    overflow = 0;
    for (i = 0; i < MAXWORD; ++i)
        wl[i] = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n')
        {
            if (nc > 0)
                if (nc < MAXWORD)
                    ++wl[nc];
                else
                    ++overflow;
            nc = 0;
        }
        else if (state == OUT)
        {
            state = IN;
            nc = 1; //beginning of a new word
        }
        else
            ++nc;
    }
    maxvalue = 0;
    for (i = 1; i < MAXWORD; ++i)
        if (wl[i] > maxvalue)
            maxvalue = wl[i];

    //bars hroizontal
    for (i = 1; i < MAXWORD; ++i)
    {
        printf("%5d - %5d : ", i, wl[i]);
        if (wl[i] > 0)
        {
            if ((len = wl[i] * MAXHIST / maxvalue) <= 0)
                len = 1;
        }
        else
            len = 0;
        while (len > 0)
        {
            putchar('*');
            --len;
        }
        putchar('\n');
    }

    //vertical orientation
    for (i = MAXHIST; i > 0; --i)
    {
        for (j = 1; j < MAXWORD; ++j)
            if (wl[j] * MAXHIST / maxvalue >= i)
                printf("   * ");
            else
                printf("     ");
        putchar('\n');
    }
    for (i = 1; i < MAXWORD; ++i)
        printf("%4d ", i);
    putchar('\n');
    for (i = 1; i < MAXWORD; ++i)
        printf("%4d ", wl[i]);
    putchar('\n');

    if (overflow > 0)
        printf("There are %d words >= %d\n", overflow, MAXWORD);
}