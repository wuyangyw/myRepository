#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <fcntl.h>
#include "Socket.h"

int main()
{
    // 1.创建通信套接字
    int fd = CreateSocket();
    if (fd == -1)
    {
        return -1;
    }

    // 2.连接服务器的ip地址和端口号
    int ret = ConnectToHost(fd, "192.168.177.129", 9999);
    if (ret == -1)
    {
        return -1;
    }

    // 3.通信
    int fd1 = open("English.txt", O_RDONLY);
    int length = 0;
    char buff[1000];
    // 一次性最多从txt文件里面读100个字节
    while ((length = read(fd1, buff, rand()%1000)) > 0)
    {
        SendMsg(fd, buff, length);

        memset(buff, 0, sizeof(buff));
        usleep(10000);
    }

    sleep(10);
    // 6.关闭套接字
    CloseSocket(fd);

    return 0;
}