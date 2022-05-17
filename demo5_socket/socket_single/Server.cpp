#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>

int main()
{
    // 1.创建监听套接字
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1)
    {
        perror("socket"); // 将上一个函数发生错误的原因输出到标准设备，并先打印参数“socket”
        return -1;
    }

    // 2.绑定本地的ip地址和端口号
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(10000);       // 最好设置5000以上
    saddr.sin_addr.s_addr = INADDR_ANY; // 自动读取ip地址绑定
    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("bind");
        return -1;
    }

    // 3.设置监听
    ret = listen(lfd, 128);
    if (ret == -1)
    {
        perror("listen");
        return -1;
    }

    // 4.阻塞并等待客户端连接
    struct sockaddr_in caddr;
    socklen_t caddrlen = sizeof(caddr);
    int cfd = accept(lfd, (struct sockaddr *)&caddr, &caddrlen);
    if (ret == -1)
    {
        perror("accept");
        return -1;
    }

    // 连接成功，打印客户端ip和端口信息
    char ip[32];
    const char *cip = inet_ntop(AF_INET, &caddr.sin_addr.s_addr, ip, sizeof(ip));
    std::cout << "客户端IP: " << cip <<" " << "端口: " << ntohs(caddr.sin_port) << std::endl;

    // 5.通信
    while (1)
    {
        // 接收数据
        char buff[1024];
        int len = recv(cfd, buff, sizeof(buff), 0);
        if (len > 0)
        {
            std::cout << "客户端信息：" << buff << std::endl;
            send(cfd, buff, len, 0);
        }
        else if (len == 0)
        {
            std::cout << "客户端已经断开了连接..." << std::endl;
            break;
        }
        else
        {
            perror("recv");
            break;
        }
    }

     // 6.关闭套接字
        close(lfd);
        close(cfd);

    return 0;
}