//
// Created by zrf on 17-9-9.
//

#include <unistd.h>
#include <poll.h>
#include "../header/GameRoom.h"
#include "../header/SerializeStream.h"
#include "../header/Encoding.h"
#include "../header/Message.h"
#include "../header/Debug.h"

GameRoom::GameRoom(Client *c1, Client *c2)
{
    Debug::Log("新房间创建");
    m_client[0] = c1;
    m_client[1] = c2;

    //发送房间信息
    char buffer[128];
    FightMessage fm;
    Player *p = m_client[0]->GetPlayer();
    int cSocket = m_client[1]->GetClientSocket();
    fm.SetFightInfo(p->GetUID(), p->GetName());
    //发送对手信息
    write(cSocket, buffer, sizeof(buffer));

    p = m_client[1]->GetPlayer();
    cSocket = m_client[0]->GetClientSocket();
    fm.SetFightInfo(p->GetUID(), p->GetName());
    write(cSocket, buffer, sizeof(buffer));
}

void GameRoom::Update()
{
    //游戏房间逻辑
    pollfd pfd[2];
    for(int i = 0; i < 2; ++i)
    {
        pfd[i].fd = m_client[i]->GetClientSocket();
        pfd[i].events = POLLRDNORM;
        pfd[i].revents = 0;
    }

    //同步玩家操作信息
    while(true)
    {
        int readyCount = poll(pfd, 2, -1);
        for(int i = 0; i < 2; ++i)
        {
            if(pfd[i].revents == 0)
                continue;

            //接收操作信息
            int recvCount = read(pfd[i].fd, m_buffer, BUFFSIZE);
            m_buffer[readyCount] = 0;

            int another = i == 0 ? 1 : 0;
            //校验信息
            SerializeStream ss(m_buffer, recvCount);
            int mType = ss.GetFlag();
            if(mType == Message::MessageType::Position)
            {
                //操作同步到另一玩家
                write(pfd[another].fd, m_buffer, recvCount);
            }
            else if(mType == Message::MessageType::GameOver)
            {
                //一方玩家游戏结束
                Message m(Message::MessageType::GameWin);
                std::string data = m.Serialize();
                write(pfd[another].fd, data.data(), data.size());
            }

            --readyCount;
            if(readyCount == 0)
                break;
        }
    }

}

void GameRoom::GameRoomThread(GameRoom *room)
{
    room->Update();
}