## Exercise 2-1
**Write a program to determine the reanges of `char`, `shrot`, `int` and `long` variables, both `signed` and `unsigned`, by printing appropriate values from standard headers and by direct computaion. Harder if you compute them, determine the ranges of the various floating-point types.**
```C
#include <stdio.h>
#include <limits.h>

main()
{
    printf("signed char min = %d\n", SCHAR_MIN);
    printf("signed char max = %d\n", SCHAR_MAX);
    /printf("signed short min = %d\n", SHART_MIN);
    printf("signed short max = %d\n", SHRT_MAX);
    pritnf("signed int min = %d\n", INT_MIN);
    printf("signed int max = %d\n", INT_MAX);
    pritnf("signed long min = %ld\n", LONG_MIN);
    printf("signed long max = %d\n", LONG_MAX);
    //unsigned type
    pritnf("unsigned char max = %u\n", UCHAR_MAX);
    printf("unsigned short max = %u\n", USHRT_MAX);
    printf("unsigned int max = %u\n", UINT_MAX);
    printf("unsigned long max = %u\n", ULOGN_MAX);
}
```
> ##### 2th
```C
#include <stdio.h>

main()
{
    //signed type
    printf("signed char min = %d\n", -(char)(unsigned char) ~0 >> 1);
    printf("signed char max = %d\n", (char)(unsigned char) ~0 >> 1);
    printf("signed short min = %d\n", -(short)(unsigned char) ~0 >> 1);
    printf("signed short max = %d\n", (short)(unsigned char) ~0 >> 1);
    printf("signed int min = %d\n", -(int)(unsigned char) ~0 >> 1);
    printf("signed int max = %d\n", (int)(unsigned char) ~0 >> 1);
    printf("signed long min = %ld\n", -(long)(unsigned char) ~0 >> 1);
    printf("signed long max = %ld\n", (long)(unsigned char) ~0 >> 1);
    //unsigned type
    printf("unsigned char max = %d\n", (unsigned char) ~0);
    printf("unsigned shrot max = %d\n", (unsigned short) ~0);
    printf("unsigned int max = %d\n", (unsigned int) ~0);
    printf("unsigned long max = %d\n", (unsigned long) ~0;
}
```
## Exercise 2-2
**Write a loog equivalent to the for loop above without using `&&` or `||`.**

```C
origin:
for(i = 0; i < lim - 1 && (c = getchar()) ！= "\n" && c != EOF; ++i)

answer:
enum loop { NO, YES };
enum loop okloop = YES;

i = 0;
while(okloop == YES)
{
    if(i >= lim -1)
        okloop = NO;
    else if((c = getchar()) == "\n")
        okloop = NO;
    else if(c == EOF)
        okloop = NO;
    else
    {
        s[i] = c;
        ++i;
    }
}
```

## Exercise 2-3
**Write the function `htoi(s)`, which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value.
The allowable digits are 0 through 9, a through f, and A through F.

```C
#define YES 1
#define NO 0

int htoi(char s[])
{
    int hexdigit, i, inhex, n;
    i = 0;
    if(s[i] == '0')
    {
        ++i;
        if(s[i] == 'x' || s[i] == 'X')
            ++i;
    }
    n = 0;
    inhex = YES;
    for(; inhex == YES; ++i)
    {
        if(s[i] >= '0' && s[i] <= '9')
            hexdigit = s[i] - '0';
        else if(s[i] >= 'a' && s[i] <= 'f')
            hexdigit = s[i] - 'a' + 10;
        else if(s[i] >= 'A' && s[i] <= 'F')
            hexdigit = s[i] - 'A' + 10;
        else
            inhex = NO;
        if(inhex == YES)
            n = 16 * n + hexdigit;
    }
    return n;
}
```
## Exercise 2-4
**Write an alternate version of `squeeze(s1, s2)` that deletes each character in `s1` that matches any character ini the string `s2`.**

```C
void sequeeze(char s1[], char s2[])
{
    int i, j, k;

    for(i = k = 0; s1[i] != '\0'; ++i)
    {
        for(j = 0; s2[j] != '\0' && s1[i] != s2[j]; ++j)
            ;
        if(s2[j] == '\0')
            s1[k++] = s1[i];
    }
    s1[k] = '\0';
}
```
## Exercise 2-5
**Write the function `any(s1, s2)`, which returns the first location in the string `s1` where any character from the string `s2` occurs, or -1 if `s1` contains no characters from `s2`, (The standard library function `strpbrk` does the same job but returns a pointer to the location).**
```C
void any(char s1[], char s2[])
{
    int i, j;

    for(i = 0; s1[i] != '\0'; ++i)
    {
        for(j = 0; s2[j] != '\0'; ++j)
            if(s1[i] == s2[j])
                return i;
    }

    return -1;
}
```

## Exercise 2-6
**Write a function `setbits(x, p, n, y)` that returns `x` with the `n` bits that begin at position `p` set to the rightmost `n` bits of `y`, leaving the other bits unchanged.**
```C
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
    return x & ~(~(~0 << n) << (p + 1 - n)) | (y & ~(~0 << n)) << (p + 1 - n);
}
```
## Exercise 2-7
**Write a function `invert(x, p, n)` that returns `x` with the `n` bits that begin at position `p` inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.**
```C
unsigned invert(unsinged x, int p, int n)
{
    return x ^ (~(~0 << n) << (p + 1 - n));
}
```

## Exercise 2-8
**Write a function `rightrot(x, n)` that returns the value of the integer `x` rotated to the right by `n` bit positions.**

```C
first solution:
unsigned rightrot(unsigned x, int n)
{
    int wordlenght(void);
    int rbit;
    while(n-- > 0)
    {
        rbit = (x & 1) << (wordlenght() - 1);
        x = x >> 1;
        x = x | rbit;
    }
    return x;
}


second sloution:
unsigned rightrot(unsigned x, int n)
{
    int wordlength(void);
    unsigned rbits;

    if((n = n & wordlenght()) > 0)
    {
        rbits = ~(~0 << n) & x;
        rbits = rbits << (wordlength() - n);
        x = x >> n;
        x = x | rbits;
    }
}

//public function wordlength(void)
int wordlenght(void)
{
    int i;
    unsinged v = (unsigned)~0;
    for(i = 1; (v = v >> 1) > 0; ++i)
        ;
    return i;
}
```
## Exercise 2-9
**In a two's complement number system, `x &= (x - 1)` deletes the rightmost `1-bit` in `x`. Explain why. Use this observatioin to write a faster version of `bitcount`.**
```C
int bitcount(unsigned x)
{
    int b;

    for(b = 0; x != 0; X &= x - 1)
        ++b;
    return b;
}
```

## Exercise 2-10
**Rewrite the function `lower`, which converts `upper` case letter to `lower` case, with conditional expression instead of `if-else`**
```C
int lower(int c)
{
    return c >= 'A' && c <= 'Z' ? c + 'a' - 'A' : c;
}
```
