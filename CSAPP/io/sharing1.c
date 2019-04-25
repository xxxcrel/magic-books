/* $begin sharing1 */
#include "csapp.h"

int main()
{
    int fd1, fd2;
    char c;

    fd1 = Open("foobar.txt", O_RDONLY, 0);
    fd2 = Open("foobar.txt", O_RDONLY, 0);
    // fprintf(stdout, "%d\n", fd1);
    // fprintf(stdout, "%d\n", fd2);
    // Write(STDOUT_FILENO, &fd1, 1);
    // //fflush(stdout);
    // Write(STDOUT_FILENO, &fd2, 1);
    // fflush(stdout);
    Read(fd1, &c, 1);
    Read(fd2, &c, 1);
    //printf("c = %c\n", c);s
    exit(0);
}
/* $end sharing1 */
