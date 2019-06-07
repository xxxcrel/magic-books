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
    printf("unsigned char max = %u\n", (unsigned char) ~0);
    printf("unsigned shrot max = %u\n", (unsigned short) ~0);
    printf("unsigned int max = %u\n", (unsigned int) ~0);
    printf("unsigned long max = %lu\n", (unsigned long)~0);
}