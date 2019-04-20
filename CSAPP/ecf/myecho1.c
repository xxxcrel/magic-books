#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[], char const *envp[])
{
    int i = 0;
    printf("Command-Line arguments:\n");
    for(int i = 0; i < argc; ++i)
        printf("argv[%d]: %s\n", argc, argv[i]);

    printf("Environment arguments:\n");
    while(*envp != NULL)
    {
        printf("envp[%d]: %s\n", i, *envp);
        i++;
        envp++;
    }  
    return 0;
}
