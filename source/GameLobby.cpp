//
// Created by zrf on 17-9-7.
//

#include <unistd.h>
#include "../header/GameLobby.h"
#include "../header/Debug.h"
#include "../header/SerializeStream.h"
#include "../header/Message.h"

GameLobby* GameLobby::Init()
{
    if(m_instance == nullptr)
        m_instance = new GameLobby();
    return m_instance;
}

void GameLobby::JoinLobby(Client *newPlayer)
{
    if(newPlayer == nullptr)
        return;

    //新玩家加入大厅
    pollfd pf;
    pf.fd = newPlayer->GetClientSocket();
    pf.events = POLLRDNORM;
    pf.revents = 0;
    m_lobby[pf.fd] = newPlayer;
    m_pollVector.push_back(pf);
    Debug::Log("新客户端加入");
}

void GameLobby::Update()
{
    //监听游戏大厅中所有客户端的可读消息，进行其他场景切换
    char buffer[1024];
    while(true)
    {
        int readableCount = poll(m_pollVector.data(), m_pollVector.size(), -1);
        for(int i = 0; i < m_pollVector.size(); ++i)
        {
            if(m_pollVector[i].revents == 0)
                continue;


            int res = read(m_pollVector[i].fd, buffer, 1024);
            buffer[res] = 0;

            //===================================无可重用性============================
            SerializeStream ss(buffer, res);
            int mType = ss.GetFlag();

            //==============================是否可以使用状态机模式？======================
            //加入游戏消息
            if(mType == Message::MessageType::Join)
            {

            }
            --readableCount;
            if(readableCount == 0)
                break;

        }



    }
}

GameLobby *GameLobby::m_instance = GameLobby::Init();