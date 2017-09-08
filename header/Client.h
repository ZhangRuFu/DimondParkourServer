//
// Created by zrf on 17-9-7.
//

#ifndef DIMONDPARKOUR_CLIENT_H
#define DIMONDPARKOUR_CLIENT_H

#include "Message.h"
#include "Player.h"

//抽象客户端
//封装发送数据、接收数据以及需要的客户端数据信息
//包含套接字操作，不符合职责单一原则
class Client
{
private:
    int m_clientSocket = 0;             //与客户端通信的套接字
    Player *m_player;               //客户端逻辑信息数据
    static const int BUFFERSIZE = 256;
    char m_buffer[BUFFERSIZE];             //数据缓冲

public:
    Client(int clientSocket) : m_clientSocket(clientSocket){}
    ~Client(void);

    int GetClientSocket(void){return m_clientSocket;}

    //主循环
    void Update(void);

    void Init(JoinMessage &message);
};

#endif //DIMONDPARKOUR_CLIENT_H