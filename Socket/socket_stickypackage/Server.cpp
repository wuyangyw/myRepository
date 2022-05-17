#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <pthread.h>
#include"Socket.h"

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
    int lfd = CreateSocket();
    if (lfd == -1)
    {
        return -1;
    }

    // 2.绑定本地的ip地址和端口号
    int ret = SetListen(lfd,9999);
    if (ret == -1)
    {
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
        pInfo->fd = AcceptConnect(lfd, &pInfo->addr);

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
        //char buff[4096];
        //memset(buff, 0, sizeof(buff));
        char *buf;
        int len = RecvMsg(pInfo->fd, &buf);
        std::cout << "接收数据: "<< len <<" ......"<<std::endl;
        if (len > 0)
        {
            std::cout << buf << std::endl;
            free(buf);
        }
        else
        {
            break;
        }
        sleep(1);
    }

    // 关闭套接字
    pInfo->fd = -1;

    return nullptr;
}