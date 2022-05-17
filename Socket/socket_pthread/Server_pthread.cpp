#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <pthread.h>

void *Work(void *arg);

// 套接字信息结构体，用来作Work的参数传入套接字信息
struct SockInfo
{
    struct sockaddr_in addr;
    int fd;
};
struct SockInfo inFos[512]; //套接字结构体数组，用来存储最多512个客户端的连接信息

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
    saddr.sin_port = htons(10000);      // 最好设置5000以上
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

    // 初始化结构体数组
    int length = sizeof(inFos) / sizeof(inFos[0]);
    for (int i = 0; i < length; ++i)
    {
        memset(&inFos[i], 0, sizeof(inFos[i]));
        inFos[i].fd = -1; //初始化文件描述符为-1,代表空闲可用
    }

    // 4.阻塞并等待客户端连接
    socklen_t addrlen = sizeof(struct sockaddr_in);
    while (1)
    {
        struct SockInfo *pInfo;
        for (int i = 0; i < length; ++i)
        {
            if (inFos[i].fd == -1)
            {
                pInfo = &inFos[i];
                break;
            }
        }
        int cfd = accept(lfd, (struct sockaddr *)&pInfo->addr, &addrlen);
        pInfo->fd = cfd;
        if (ret == -1)
        {
            perror("accept");
            break;
        }

        // 创建子线程
        pthread_t tid;
        pthread_create(&tid, nullptr, Work, pInfo);
        pthread_detach(tid);
    }
    close(lfd);

    return 0;
}
void *Work(void *arg)
{
    struct SockInfo *pInfo = (struct SockInfo *)arg;

    // 连接成功，打印客户端ip和端口信息
    char ip[32];
    const char *cip = inet_ntop(AF_INET, &pInfo->addr.sin_addr.s_addr, ip, sizeof(ip));
    std::cout <<"客户端IP: " << cip << "  "
              << "端口: " << ntohs(pInfo->addr.sin_port) <<"   已启动....."<< std::endl;

    // 5.通信
    while (1)
    {
        // 接收数据
        char buff[1024];
        int len = recv(pInfo->fd, buff, sizeof(buff), 0);
        if (len > 0)
        {
            std::cout <<"端口 ["<<ntohs(pInfo->addr.sin_port)<< "] 客户端信息：" << buff << std::endl;
            send(pInfo->fd, buff, len, 0);
        }
        else if (len == 0)
        {
            std::cout <<"端口 ["<<ntohs(pInfo->addr.sin_port)<< "] 客户端已经断开了连接..." << std::endl;
            break;
        }
        else
        {
            perror("recv");
            break;
        }
    }

    // 关闭套接字
    close(pInfo->fd);
    pInfo->fd = -1;

    return nullptr;
}