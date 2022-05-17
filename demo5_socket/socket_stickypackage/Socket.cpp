#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include"Socket.h"

int CreateSocket()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        return -1;
    }
    std::cout << "socket create successfully....." << std::endl;
    return fd;
}

// 绑定本地IP和端口+设置监听
int SetListen(int lfd, unsigned short port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(lfd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("bind");
        return -1;
    }
    std::cout << "socket bind successfully....." << std::endl;

    // 设置监听
    ret = listen(lfd, 128);
    if (ret == -1)
    {
        perror("listen");
        return -1;
    }
    std::cout << "socket listen successfully....." << std::endl;
    std::cout << "wait for communication....." << std::endl;

    return ret;
}

// 阻塞并等待客户端连接
int AcceptConnect(int lfd, struct sockaddr_in *addr)
{
    int cfd = -1;
    if (addr == nullptr)
    {
        cfd == accept(lfd, nullptr, nullptr);
    }
    else
    {
        socklen_t addrlen = sizeof(struct sockaddr_in);
        cfd = accept(lfd, (struct sockaddr *)&addr, &addrlen);
    }

    if (cfd == -1)
    {
        perror("accept");
        return -1;
    }
    std::cout << "socket accept successfully....." << std::endl;
    return cfd;
}

// 连接服务器
int ConnectToHost(int fd, const char *ip, unsigned short port)
{
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &saddr.sin_addr.s_addr);
    int ret = connect(fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("connect");
        return -1;
    }
    std::cout << "socket connect successfully....." << std::endl;
    return ret;
}

// 关闭套接字
int CloseSocket(int fd)
{
    int ret = close(fd);
    if (ret = -1)
    {
        perror("close");
    }
    return ret;
}

// 接收数据
/* 这样会粘包
int RecvMsg(int cfd, char *msg, int size)
{
    int len = recv(cfd, msg, size, 0);
    if (len == 0)
    {
        std::cout << "client has been disconnected....." << std::endl;
        close(cfd);
    }
    else if (len == -1)
    {
        perror("recv");
        close(cfd);
    }
    return len;
} */
/*
函数描述: 接收带数据头的数据包
函数参数:
    - cfd: 通信的文件描述符(套接字)
    - msg: 一级指针的地址，函数内部会给这个指针分配内存，用于存储待接收的数据，这块内存需要使用者释放
函数返回值: 函数调用成功返回接收的字节数, 发送失败返回-1
*/
int RecvMsg(int cfd, char **msg)
{
    // 读数据头
    int len = 0;
    ReadData(cfd, (char *)&len, 4);
    len = ntohl(len);
    std::cout << "数据块大小：" << len << std::endl;

    // 根据读出的长度分配内存，+1 -> 这个字节存储\0
    char *data = (char *)malloc(len + 1);
    int length = ReadData(cfd, data, len);
    if (length != len)
    {
        std::cout << "数据接收失败....." << std::endl;
        close(cfd);
        free(data);
        return -1;
    }
    data[len] = '\0';
    *msg = data;

    return length;
}

// 发送数据
/* 这样会粘包
int SendMsg(int fd, const char *msg, int len)
{
    int ret = send(fd, msg, len, 0);
    if(ret==-1)
    {
        perror("send");
        close(fd);
    }
    return ret;
} */
/*
函数描述: 发送带有数据头的数据包
函数参数:
    - cfd: 通信的文件描述符(套接字)
    - msg: 待发送的原始数据
    - len: 待发送的原始数据的总字节数
函数返回值: 函数调用成功返回发送的字节数, 发送失败返回-1
*/
int SendMsg(int cfd, const char *msg, int len)
{
    if (msg == NULL || len <= 0 || cfd <= 0)
    {
        return -1;
    }

    // 申请内存空间: 数据长度 + 包头4字节(存储数据长度)
    char *data = (char *)malloc(len + 4);
    int bigLen = htonl(len);

    // 表示从存储区biglen复制n个字节到存储区data
    memcpy(data, &bigLen, 4);
    memcpy(data + 4, msg, len);

    // 发送数据
    int ret = WriteData(cfd, data, len + 4);
    if (ret == -1)
    {
        close(cfd);
        free(data);
    }
    return ret;
}

/////////////////////////////// TCP粘包处理 //////////////////////////////
/*
函数描述: 发送指定的字节数
函数参数:
    - fd: 通信的文件描述符(套接字)
    - msg: 待发送的原始数据
    - size: 待发送的原始数据的总字节数
函数返回值: 函数调用成功返回发送的字节数, 发送失败返回-1
*/
int WriteData(int fd, const char *msg, int size)
{
    const char *buf = msg;
    int count = size; // 剩余发送的字节数
    while (count > 0)
    {
        int len = send(fd, buf, count, 0); // len为当前发送的字节数
        if (len == -1)
        {
            close(fd);
            return -1;
        }
        else if (len == 0)
        {
            continue;
        }
        buf += len;   // 重新记录buf指针发送位置
        count -= len; // 重新记录剩余字节数
    }
    return size;
}

/*
函数描述: 接收指定的字节数
函数参数:
    - fd: 通信的文件描述符(套接字)
    - buf: 存储待接收数据的内存的起始地址
    - size: 指定要接收的字节数
函数返回值: 函数调用成功返回发送的字节数, 发送失败返回-1
*/
int ReadData(int fd, char *buf, int size)
{
    char *pt = buf; // 辅助指针，记录接收数据位置
    int count = size;
    while (count > 0)
    {
        int len = recv(fd, pt, count, 0);
        if (len == -1)
        {
            return -1;
        }
        else if (len == 0)
        {
            return size - count;
        }
        pt += len;
        count -= len;
    }
    return size;
}
