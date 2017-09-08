//
// Created by zrf on 17-9-8.
//

#include "../header/CheckLobby.h"
#include "../header/SerializeStream.h"
#include "../header/GameLobby.h"
#include <unistd.h>

CheckLobby* CheckLobby::Init(void)
{
    if(m_instance == nullptr)
        m_instance = new CheckLobby();
    return m_instance;
}

void CheckLobby::Add(Client *newClient)
{
    if(newClient == nullptr)
        return;
    //新客户端添加近审核大厅
    pollfd fd;
    fd.fd = newClient->GetClientSocket();
    fd.events = POLLRDNORM;
    fd.revents = 0;
    m_pollfdVector.push_back(fd);
    m_clientMap[fd.fd] = newClient;
}

void CheckLobby::Update()
{
    char buffer[1024];
    //接收JoinMessage

    //定时清理长时间无反应的客户端
    while(true)
    {
        int readCount = poll(m_pollfdVector.data(), m_pollfdVector.size(), -1);
        for(std::vector<pollfd>::iterator i = m_pollfdVector.begin(); i != m_pollfdVector.end(); )
        {
            if(i->revents == 0)
            {
                ++i;
                continue;
            }

            int size = read(i->fd, buffer, 1024);
            SerializeStream ss(buffer, size);

            int mType = ss.GetFlag();
            if(mType == Message::MessageType::Join)
            {
                JoinMessage joinMessage;
                joinMessage.Deserialize(ss);
                Client *c = m_clientMap[i->fd];
                c->Init(joinMessage);

                //将该客户端移至游戏大厅
                m_clientMap.erase(i->fd);
                i = m_pollfdVector.erase(i);
                GameLobby::Instance()->JoinLobby(c);
            }

            --readCount;
            if(readCount == 0)
                break;
        }
    }
}

CheckLobby* CheckLobby::Instance(void)
{
    return m_instance;
}

CheckLobby *CheckLobby::m_instance = CheckLobby::Init();
