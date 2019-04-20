#include<stdio.h>

int Power(int X, int N)
{
    printf("time clock\n");
    if(N == 0)
        return 1;
    if(N == 1)
        return X;
    else if(N % 2 != 0)
        return X * Power(X * X, N / 2);
    else
        return Power(X * X, N / 2);
}
int main()
{
    Power(2, 16);
    return 0;
}