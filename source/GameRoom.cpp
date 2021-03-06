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
#include "../header/SocketUtility.h"
#include "../header/Client.h"
#include "../header/GameLobby.h"

GameRoom::GameRoom(Client *c1, Client *c2) : m_gaming(true)
{
    Debug::Log("新游戏房间创建");
    m_client[0] = c1;
    m_client[1] = c2;

    //发送房间信息
    std::vector<Message*> ms;
    FightMessage fm;
    fm.SetSeed(random() % 100);
    int x1 = 3;
    int z = 4;
    int x2 = 4;

    //发送给0号玩家
    Player *p = m_client[1]->GetPlayer();
    Client *client = m_client[0];
    fm.SetFightInfo(p->GetUID(), p->GetName());
    fm.SetPlayerX(x1);
    fm.SetPlayerZ(z);
    fm.SetEnemyX(x2);
    fm.SetEnemyZ(z);

    ms.push_back(&fm);
    client->AcceptMessage(ms);
    client->EnterGameRoom(this);

    //发送给1号玩家
    p = m_client[0]->GetPlayer();
    client = m_client[1];
    fm.SetFightInfo(p->GetUID(), p->GetName());
    fm.SetPlayerX(x2);
    fm.SetEnemyX(x1);
    client->AcceptMessage(ms);
    client->EnterGameRoom(this);

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

    SerializeStream ss;
    //同步玩家操作信息
    while(m_gaming)
    {
        int readyCount = poll(pfd, 2, -1);
        for(int i = 0; i < 2; ++i)
        {
            if(pfd[i].revents == 0)
                continue;

            //接收操作信息
            int recvCount = read(pfd[i].fd, m_buffer, BUFFSIZE);
            m_buffer[recvCount] = 0;

            ss.AcceptStream(m_buffer, recvCount);
            std::vector<Message*> &m = ss.GetMessages();

            std::cout << "接收到操作信息" << i << std::endl;
            //同步信息
            m_client[i]->AcceptMessage(m);

            ++i;
            --readyCount;
            if(readyCount == 0)
                break;
        }
    }

    //游戏结束
}

//同步位置给其他玩家
void GameRoom::SynchronizePosition(PositionMessage &message, Client *client)
{
    Client *another = (client == m_client[0] ? m_client[1] : m_client[0]);
    SocketUtility::SendMessage(another->GetClientSocket(), message);
}

void GameRoom::GameOver(Client *client)
{
    //告知另一方游戏胜利
    Client *another = (client == m_client[0] ? m_client[1] : m_client[0]);
    Message message(Message::MessageType::GameWin);
    std::vector<Message*> ms;
    ms.push_back(&message);
    another->AcceptMessage(ms);

    //解散游戏房间
    m_gaming = false;
}

void GameRoom::GameRoomThread(GameRoom *room)
{
    room->Update();
    GameLobby::Instance()->Dissolve(room);
}