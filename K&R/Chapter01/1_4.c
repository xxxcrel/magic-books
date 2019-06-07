#include <stdio.h>

int main()
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
    return 0;
}