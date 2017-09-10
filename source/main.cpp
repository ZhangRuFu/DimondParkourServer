#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include "../header/Encoding.h"
#include "../header/SerializeStream.h"
#include "../header/Client.h"
#include "../header/ThreadManager.h"
#include <thread>

#define PORT 8888
typedef unsigned char byte;

int main() {
    //using namespace std;
    int res = 0;

    ThreadManager tm;

    int serSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in serAddr;
    serAddr.sin_addr.s_addr = 0;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(PORT);

    res = bind(serSocket, (sockaddr *) &serAddr, sizeof(serAddr));
    if (res == -1)
    {
        std::cout << "套接字绑定出错!" << std::endl;
        return 1;
    }
    listen(serSocket, 10);
    while (true) {
        sockaddr_in clientAddr;
        socklen_t sockLen = sizeof(clientAddr);
        int clientSock = accept(serSocket, (sockaddr *) &clientAddr, &sockLen);

        //新玩家加入
        std::cout << "新玩家加入，客户端IP:" << inet_ntoa(clientAddr.sin_addr) << " 端口号:" << ntohs(clientAddr.sin_port)
                  << std::endl;

        //套接字资源属主转移
        Client *newClient = new Client(clientSock);

        //加入审核大厅
        CheckLobby::Instance()->Add(newClient);
    }
    close(serSocket);
    //自动释放线程资源
    return 0;
}