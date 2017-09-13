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
class GameRoom;
class Client
{
public:
    //客户端位置
    enum class ServerPosition{None, GameLobby, GameRoom};

private:
    int m_clientSocket = 0;             //与客户端通信的套接字
    Player *m_player;                   //客户端逻辑信息数据
    State *m_state;                     //客户端状态
    ServerPosition m_position = ServerPosition ::None;          //服务端位置


public:
    Client(int clientSocket);
    ~Client(void);

    //getter & setter
    int GetClientSocket(void){return m_clientSocket;}
    Player* GetPlayer(void) {return m_player;}
    State* GetState(void) { return m_state;}
    ServerPosition GetServerPosition(void) { return m_position;}

    void SetPlayer(Player *player) {
        if (player != nullptr)
            m_player = player;
    }
    void SetServerPosition(ServerPosition p) { m_position = p;}

    //状态
    void AcceptMessage(std::vector<Message*> &messages);
    void ChangeState(State *newState);
    void EnterGameRoom(GameRoom *room);

    //网络通信
    void FeedBackMessage(Message &message);


};

#endif //DIMONDPARKOUR_CLIENT_H