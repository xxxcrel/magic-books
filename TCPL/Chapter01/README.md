> ## In this chapter, 95% of the code is copied from the answer book to The C Programming Language

## Exercise 1-1
**Run the "hello world" program on your system. Experiment with leaving out parts of program, to see what error messages you get.**
```C
#include <stdio.h>

main()
{
    printf("hello world");
}
```
```C
#include <stdio.h>

main()
{
    printf("hello, world\n")
}
```
```C
#include <stdio.h>

main()
{
    printf("hello, world\n');
}
```
## Exercise 1-2
**Experiment to find out what happen when printf's argument string contains `\c`, where `c` is some character not listed above.**
```C
#include <stdio.h>

main()
{
    printf("\c");
    printf("\7");
    printf("\?");S
}
```
## Exercise 1-3
**Modify the temperature conversion program to print a heading above the table.**
```C
#include <stdio.h>

main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("Fahr Celsius\n");
    while(fahr <= upper)
    {
        celsius = (5.0/9.0) * (fahr - 32.0);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}
```
## Exercise 1-4
**Write a program to print the corrsponding Celsius to Fahrenheit tablee.**
```C
#include <stdio.h>

main()
{
    float fahr, celsius;
    int lower = 0, upper = 200, step = 20;

    celsius = lower;
    printf("Celsius Fahr\n");
    while(celsius <= upper)
    {
        fahr = (celsius * 9.0) / 5.0 + 32;
        printf("%6.1f %3.0f\n", celsius, fahr);
        celsius = celsius + step;
    }
}
```
## Exercise 1-5
**Modify the temperature conversion program to print the table in reverse order, that is, from 300 degrees to 0.**
```C
#include <stdio.h>

main()
{
    int fahr;

    for(fahr = 300; fahr >= 00; fahr = farh - 20)
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0) * (fahr - 32));
}
```
## Exercise 1-6
**Verify that the expression `getchar() != EOF` is `0` of `1`.
```C
#include <stdio.h>

main()
{
    int c;

    while(c = getchar() != EOF)//equivalent to ( c = (getchar() != EOF) )
        printf("%d\n", c);
    printf("%d - at EOF\n", c);
}
```
> ### This exercise makes lots of sense, it's a big challenge for beginner.
> ### Why output two lines follow a input?
![16.PNG](https://i.loli.net/2019/01/17/5c4044badbcbf.png)
> ### because when you enter the `<enter>` key,the `getchar()` function assume is a input, but you may be don't want this key
> ### so you can add a getchar() in the `{}` to avoid this happening.
```C
#include <stdio.h>

main()
{
    int c;
    while(c = getchar() != EOF)
    {
        getchar();
        printf("%d\n", c);
    }
    printf("%d - at EOF\n", c);
}
```
## Exercise 1-7
**Write a program to print the value of `EOF`**.
```C
#include <stdio.h>

main()
{
    printf("EOF is %d\n", EOF);
}
```
## Exercise 1-8
**Write a program to count blanks, tabs, newlines.**
```C
#include <stdio.h>
main()
{
    int nb = 0, nt = 0, nl = 0;
    int c;
    while((c = getchar()) != EOF)
    {
        if(c == '\n')
            ++nl;
        if(c == '\t')
            ++nt;
        if(c == ' ')
            ++nb;
    }
    printf("blanks = %d, tabs = %d, newlines = %d", nb, nt, nl);
}
```
## Exercise 1-9
**Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank.**
> first solution(my way)
```C
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
```
> one of the answer book's solution

```C
#include <stdio.h>
#define NONBLANK 'a'

main()
{
    int c, lastc = NONBLANK;
    while((c = getchar()) != EOF)
    {
        //output the first one when input one or more blanks
        if(c != ' ' || lastc != ' ')
            putchar(c);
        lastc = c;//important!!
    }
}
```
**This solution make lots of sense**
## Exercise 1-10
**Write a program to copy its input to its output, replacing each tab by \t, each backspace by \b, and each backslash by \\. This makes tabs and backspaces visible in an unambigous way.**
```C
#include <stdio.h>

main()
{
    int c;
    while((c = getchar()) != EOF)
    {
        if(c == '\t')
            printf("\\t");
        else if(c == '\b')
            printf("\\b");
        else if(c == '\\')
            printf("\\\\");
        else
            putchar(c);
    }
}
```
## Exercise 1-11
**How would you test the word count program? What kind of iput are most likely to uncover bugs if ther are any?**
* No input
* No word(only input '\n')
* No word(only input '\', '\t', '\n')
* One word per line(don't have ' ' and '\t')
* Word appears at the beginning of the text line
* Word appears after a string of spaces

## Exercise 1-12
**Write a program that prints its input one word per line.**
```C
#include <stdio.h>
#define IN 1
#define OUT 0

main()
{
    int c, state = OUT;
    while((c = getchar()) != EOF)
    {
        if(c == ' ' || c == '\t' || c == '\n')
        //handing the first word separator
            if(state == IN)
            {
                putchar('\n');
                state = OUT;
            }
        //find the first character of next word
        else if(state == OUT)
        {
            putchar(c);
            state = IN;
        }
        else
            putchar(c);
    }
}
```
## Exercise 1-13
**Write a program to print a histogram of the lengths of words in its input. It is easy to draw the histogram with the bars horizontal; a vertical orientation is more challenging.**
**[details](https://github.com/CrelDevi/Notes/blob/master/K%26R/Chapter01/1_13.c)**

## Exercise 1-14
**Write a program to print histogram of the frequencies of different characters in its input.**
**[details](https://github.com/CrelDevi/Notes/blob/master/K%26R/Chapter01/1_14.c)**
> P.S:we can write some interesting code throught this exercise
**[ASCII](https://github.com/CrelDevi/Notes/blob/master/K%26R/Chapter01/ASCII.c)**

## Exercise 1-15
**Rewirte the temperature conversion program of Section 1.2 to use a function for conversion.**
```C
#include <stdio.h>

float celsius(float fahr);

main()
{
    float fahr;
    int lower, uppper, setp;
    lower = 0;
    upper = 300;
    step = 20;
    fahr = lower;
    while(fahr < upper)
    {
        printf("%3.0f %6.1f\n", fahr, celsius(fahr));
        fahr = fahr + step;
    }
}

float celsius(float fahr)
{
    return (5.0 / 9.0) * (fahr + 32);
}
```
## Exercise 1-16
**Revise the main routine of the longest-line program so it will correctly print the length fo arbitrarily long input lines, and as much as possible of the text.**
**[details](https://github.com/CrelDevi/Notes/blob/master/K%26R/Chapter01/1_16.c)**

## Exercise 1-17
**Write a program to print all input lines that are longer 80 character.**
```C
#include <stdio.h>
#define MAXLINE 1000
#define LONGLINE 80

int getline(char line[], int MAXLINE);

main()
{
    int len;           //current line length
    char line[MAXLINE];//current input line

    while(((len = getline(line, MAXLINE)) > 0)
        if(len > LONGLINE)
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
```
## Exercise 1-18
**Write a program to remove trailing blanks and tabs from each line of input, and delete entirely blank lines.**

**[details](https://github.com/CrelDevi/Notes/blob/master/K%26R/Chapter01/1_18.c)**

## Exercise 1-19
**Write a function *reverse(s)* that reverses the character string *s*, Use it to write a program that reverses its input a line at a time.**

**[details](https://github.com/CrelDevi/Notes/blob/master/K%26R/Chapter01/1_19.c)**

## Exercise 1-20
**Write a program `detab` that replaces strings of blanks by the minimum number of tebs and blanks tot achieve the same spacing. Use the same tab stops as for detab. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?**

**[details](https://github.com/CrelDevi/Notes/blob/master/K%26R/Chapter01/1_20.c)**

## Exercise 1-21
**Write a program `entab` that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for `detab`. When either a tab or single blank would suffice to reach a tab stop, which should be given preference?**

**[details](https://github.com/CrelDevi/Notes/blob/master/K%26R/Chapter01/1_21.c)**

## Exercise 1-22
**Write a program to "fold" long input lines into two or more shorter lines after the last non-blank character that occurs before the n-th column of input. Make sure your program does something intelligent with very long lines, and if there are no blanks or tabs before the specified column.**

**[details](https://github.com/CrelDevi/Notes/blob/master/K%26R/Chapter01/1_22.c)**

## Exercise 1-23
**Write a program to remove all comments from a `C` Program. Don't forget to handle quoted strings and character constants properly. `C` comments do not nest.**

**[details](https://github.com/CrelDevi/Notes/blob/master/K%26R/Chapter01/1_23.c)**

## Exercise 1-24
**Write a program to check a `C` program for rudimentary syntax errors like unbalanced parentheses, brackets and braces. Don't forget about quotes, both single and double, escape sequences, and comments. (This program is hard if you do it in full generality.)**

**[details](https://github.com/CrelDevi/Notes/blob/master/K%26R/Chapter01/1_24.c)**
