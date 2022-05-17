#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>

int main()
{
    // 1.创建通信套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket"); // 将上一个函数发生错误的原因输出到标准设备，并先打印参数“socket”
        return -1;
    }

    // 2.连接服务器的ip地址和端口号
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(10000); // 最好设置5000以上
    inet_pton(AF_INET, "192.168.177.129", &saddr.sin_addr.s_addr);
    int ret = connect(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("connect");
        return -1;
    }

    // 3.通信
    int number = 1;
    while (1)
    {
        // 发送数据
        char buff[1024];
        // 将格式化字符串输出到目的字符串中
        sprintf(buff, "what are you doing guys?......状态码：%d...\n",number++);
        send(fd, buff, strlen(buff) + 1, 0);
        // strlen()是函数，运行时计算实际长度，参数只能是字符型指针，遇到\0结束，长度大小不包括'\0'.
        // sizeof()是运算符，编译时计算预分配长度，不能用于动态分配的内存空间，用于计算内存的字节数.

        // 接受数据
        memset(buff, 0, sizeof(buff));
        int len = recv(fd, buff, sizeof(buff), 0);
        if (len > 0)
        {
            std::cout <<"服务器反馈信息：" << buff << std::endl;
        }
        else if (len == 0)
        {
            std::cout << "服务器已经断开了连接..." << std::endl;
            break;
        }
        else
        {
            perror("recv");
            break;
        }
        sleep(2);
    }

    // 6.关闭套接字
    close(fd);

    return 0;
}