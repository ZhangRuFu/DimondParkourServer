//
// Created by zrf on 17-9-7.
//

#ifndef DIMONDPARKOUR_CLIENT_H
#define DIMONDPARKOUR_CLIENT_H

#include "Message.h"
#include "Player.h"
#include "State.h"
#include <vector>

//抽象客户端
//封装发送数据、接收数据以及需要的客户端数据信息
//包含套接字操作，不符合职责单一原则
class Client
{
private:
    int m_clientSocket = 0;             //与客户端通信的套接字
    Player *m_player;                   //客户端逻辑信息数据
    State *m_state;                     //客户端状态

public:
    Client(int clientSocket) : m_clientSocket(clientSocket){}
    ~Client(void);

    int GetClientSocket(void){return m_clientSocket;}
    Player* GetPlayer(void) {return m_player;}

    void SetPlayer(Player *player) {
        if (player != nullptr)
            m_player = player;
    }

    void AcceptMessage(std::vector &messages);
    void ChangeState(State *newState);
};

#endif //DIMONDPARKOUR_CLIENT_H