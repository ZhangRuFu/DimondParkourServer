//
// Created by zrf on 17-9-7.
//

#include <unistd.h>
#include <thread>
#include <sys/eventfd.h>
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
    Debug::Log("新客户端加入游戏大厅");
    pollfd pf;
    pf.fd = newPlayer->GetClientSocket();
    pf.events = POLLRDNORM;
    pf.revents = 0;
    m_lobby[pf.fd] = newPlayer;
    m_pollVector.push_back(pf);

    //中断poll
    uint64_t buffer = 1;
    write(m_conSock, &buffer, sizeof(uint64_t));

}

void GameLobby::Update()
{
    //监听游戏大厅中所有客户端的可读消息，进行其他场景切换
    char buffer[1024];
    SerializeStream ss;

    while(true)
    {
        if(m_pollVector.size() == 0)
            continue;
        int readableCount = poll(m_pollVector.data(), m_pollVector.size(), -1);

        std::vector<pollfd>::iterator i = m_pollVector.begin();
        while(i < m_pollVector.end())
        {
            if(i->revents == 0)
                continue;

            //线程通信
            if(i->fd == m_conSock)
            {
                uint64_t buffer;
                read(i->fd, &buffer, sizeof(uint64_t));
                --readableCount;
                ++i;
                continue;
            }

            //处理消息
            int res = read(i->fd, buffer, 1024);
            buffer[res] = 0;

            ss.AcceptStream(buffer, res);
            std::vector<Message*> &m = ss.GetMessages();
            Client *client = m_lobby[i->fd];
            client->AcceptMessage(m);

            --readableCount;
            if(readableCount == 0)
                break;
        }

        //剔除离开的客户端
        for(std::vector<Client*>::iterator i = m_leaveClient.begin(); i < m_leaveClient.end(); ++i)
        {
            std::vector<pollfd>::iterator j = m_pollVector.begin();
            while(j != m_pollVector.end())
            {
                if((*i)->GetClientSocket() == j->fd)
                {
                    j = m_pollVector.erase(j);
                    m_lobby.erase(j->fd);
                }
            }
        }
    }
}

void GameLobby::StartGame(Client *client)
{
    if(m_readyGame.size() > 1)
    {
        //匹配成功
        Debug::Log("匹配成功");
        Client *c2 = m_readyGame.front();
        //创建游戏房间
        CreateGameRoom(client, c2);

        //从大厅剔除
        m_readyGame.pop();
        Leave(client);
        Leave(c2);

        //告知客户端

    }
    else
    {
        //没有可匹配玩家，入队列等待
        Debug::Log("加入队列等候匹配");
        m_readyGame.push(client);
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

void GameLobby::Leave(Client *client)
{
    //标记客户端，下次一并移出
    m_leaveClient.push_back(client);
}

GameLobby::GameLobby()
{
    m_conSock = eventfd(0, 0);
    pollfd conFd;
    conFd.fd = m_conSock;
    conFd.events = POLLRDNORM;
    m_pollVector.push_back(conFd);
}

GameLobby *GameLobby::m_instance = GameLobby::Init();