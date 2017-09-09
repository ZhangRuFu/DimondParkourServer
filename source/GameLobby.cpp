//
// Created by zrf on 17-9-7.
//

#include <unistd.h>
#include <thread>
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
        std::vector<pollfd>::iterator i = m_pollVector.begin();
        while(i < m_pollVector.end())
        {
            if(i->revents == 0)
                continue;

            int res = read(i->fd, buffer, 1024);
            buffer[res] = 0;

            //===================================无可重用性============================
            SerializeStream ss(buffer, res);
            int mType = ss.GetFlag();

            //==============================是否可以使用状态机模式？======================
            //加入游戏消息
            if(mType == Message::MessageType::StartGame)
            {
                //转入游戏匹配队列
                Client *c = m_lobby[i->fd];
                m_lobby.erase(i->fd);
                if(m_readyGame.size() > 1)
                {
                    //匹配成功
                    Client *c2 = m_readyGame.front();
                    //创建游戏房间
                    CreateGameRoom(c, c2);

                    //从大厅剔除
                    m_readyGame.pop();
                    m_lobby.erase(i->fd);
                    i = m_pollVector.erase(i);
                }
                else
                {
                    //没有可匹配玩家，入队列等待
                    m_readyGame.push(c);
                    ++i;
                }
            }//进入商店消息
            else if(mType == Message::MessageType::StartShop)
            {
                //...
            }
            --readableCount;
            if(readableCount == 0)
                break;
        }
    }
}

void GameLobby::CreateGameRoom(Client *c1, Client *c2)
{
    //创建游戏房间
    GameRoom *room = new GameRoom(c1, c2);
    m_gameRooms.push_back(room);
    std::thread *t = new std::thread(GameRoom::GameRoomThread, room);
    m_roomThreads.push_back(t);
}

GameLobby *GameLobby::m_instance = GameLobby::Init();