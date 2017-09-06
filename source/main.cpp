#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include "../header/Encoding.h"
#include "../header/SerializeStream.h"
#include "../header/Message.h"

#define PORT 8888
typedef unsigned char byte;

int main() {

    int res = 0;
    int serSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in serAddr;
    serAddr.sin_addr.s_addr = 0;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(PORT);

    res = bind(serSocket, (sockaddr*)&serAddr, sizeof(serAddr));
    if(res == -1)
        std::cout << "套接字绑定出错!" << std::endl;
    listen(serSocket, 10);
    while(true)
    {
        sockaddr_in clientAddr;
        socklen_t sockLen = sizeof(clientAddr);
        int clientSock = accept(serSocket, (sockaddr*)&clientAddr, &sockLen);
        std::cout << "客户端IP:" << inet_ntoa(clientAddr.sin_addr) << " 端口号:" << ntohs(clientAddr.sin_port) << std::endl;

        char buffer[2048];
        int ab = read(clientSock, buffer, 2048);
        buffer[ab] = 0;
        std::cout << "接收长度:" << ab << "内容:" << buffer << std::endl;


        close(clientSock);
    }
    close(serSocket);

    return 0;
}