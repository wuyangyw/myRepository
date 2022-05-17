#pragma once

//////////////服务器////////////////
// 绑定+监听
int SetListen(int lfd,unsigned short port);
int AcceptConnect(int lfd, struct sockaddr_in *addr);

//////////////客户端////////////////
int ConnectToHost(int fd, const char *ip, unsigned short port);

//////////////公用/////////////////
int CreateSocket();
int SendMsg(int fd, const char *msg, int len);
//int RecvMsg(int fd, char *msg, int size);
int RecvMsg(int fd, char **msg);
int CloseSocket(int fd);

//////////////粘包处理////////////
int ReadData(int fd, char *buf, int size);
int WriteData(int fd, const char *msg, int size);