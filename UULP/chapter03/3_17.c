#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#undef BUFSIZ
#define BUFSIZ 10
int main(int argc, char *argv[])
{
    int n_chars;
    int fd;
    char char_buf[BUFSIZ];
    fd = open("test.txt", 'r');
    while ((n_chars = read(fd, char_buf, BUFSIZ)) == n_chars)
    {
        write(2, char_buf, n_chars);
        sleep(20);
    }
    return 0;
}
/*实验结果：
* 当我从另一个终端去掉test.txt文件的读权限时，程序仍照常运行
*/