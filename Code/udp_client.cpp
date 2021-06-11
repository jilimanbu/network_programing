#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#define BUFFER_SIZE 1024 //缓冲区大小
int main()
{
    SOCKET sock_Client; //客户端用于通信的Socket
    WSADATA WSAData;
    char receBuf[BUFFER_SIZE]; //发送数据的缓冲区
    char sendBuf[BUFFER_SIZE]; //接受数据的缓冲区
    if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0)
    {
        printf("初始化失败!");
        return -1;
    }
    sock_Client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //创建客户端用于通信的Socket
    SOCKADDR_IN addr_server;                            //服务器的地址数据结构
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(4567);                        //端口号为4567
    addr_server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //127.0.0.1为本电脑IP地址
    SOCKADDR_IN sock;
    int len = sizeof(sock);
    while (true)
    {
         cout << "请输入要传送的数据:";
         cin >> sendBuf;
         sendto(sock_Client, sendBuf, strlen(sendBuf), 0, (SOCKADDR *)&addr_server, sizeof(SOCKADDR));
         int last = recv(sock_Client, receBuf, BUFFER_SIZE, 0); // (调用recv和recvfrom都可以)
         // int last = recvfrom(sock_Client, receBuf, strlen(receBuf), 0, (SOCKADDR *)&sock, &len);
         if (last > 0)
        {
            receBuf[last] = '\0'; //给字符数组加一个'\0'，表示结束了。不然输出有乱码
            if(strcmp(receBuf, "bye") == 0)
            {
                   cout << "服务器不跟我聊天了..." << endl; //当服务器发来bye时，关闭socket
                   closesocket(sock_Client);
                   break;
                  
            }
              else 
            {
                   printf("接收到数据：%s\n", receBuf);
            }
        }
    }
    closesocket(sock_Client);
    WSACleanup();
    return 0;
}