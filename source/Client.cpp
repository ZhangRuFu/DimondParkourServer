//
// Created by zrf on 17-9-7.
//

#include "../header/Client.h"
#include "../header/Encoding.h"
#include "../header/Message.h"
#include "../header/SerializeStream.h"
#include "../header/SocketUtility.h"
#include "../header/GameRoom.h"
#include <unistd.h>
#include <iostream>
#include <string>

Client::Client(int clientSocket) : m_clientSocket(clientSocket)
{
    ChangeState(new CheckState(this));
}

//资源释放
Client::~Client()
{
    //===========================Player应该进行数据持久化===============================
    delete m_player;
    close(m_clientSocket);
}

void Client::AcceptMessage(std::vector<Message*> &messages)
{
    for(int i = 0; i < messages.size(); ++i)
    {
        State *s = m_state->Execute(*messages[i]);
        //状态迁移
        if(s != nullptr)
            ChangeState(s);
    }
}

void Client::ChangeState(State *newState)
{
    if(newState == nullptr)
        return;
    if(m_state != nullptr) {
        m_state->Quit();
        delete m_state;
    }
    m_state = newState;
    m_state->Enter();
}

void Client::FeedBackMessage(Message &message)
{
    SocketUtility::SendMessage(m_clientSocket, message);
}

void Client::EnterGameRoom(GameRoom *room)
{
    GameState *state = nullptr;
    if((state = dynamic_cast<GameState*>(m_state)) != nullptr)
        state->EnterRoom(room);
}