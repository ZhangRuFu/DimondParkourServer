//
// Created by zrf on 17-9-8.
//

#include "../header/CheckLobby.h"
#include "../header/SerializeStream.h"
#include "../header/GameLobby.h"
#include "../header/Debug.h"
#include <unistd.h>
#include <sys/eventfd.h>

CheckLobby::CheckLobby()
{
    //初始化线程通信套接字
    m_conSock = eventfd(0, 0);
    pollfd conFd;
    conFd.fd = m_conSock;
    conFd.events = POLLIN | POLLERR;
    m_pollfdVector.push_back(conFd);
}

CheckLobby* CheckLobby::Init(void)
{
    if(m_instance == nullptr)
        m_instance = new CheckLobby();
    return m_instance;
}

//其他线程调用
void CheckLobby::Add(Client *newClient)
{
    if(newClient == nullptr)
        return;

    Debug::Log("新客户端加入审核大厅");
    pollfd fd;
    fd.fd = newClient->GetClientSocket();
    fd.events = POLLRDNORM;
    fd.revents = 0;
    m_pollfdVector.push_back(fd);
    m_clientMap[fd.fd] = newClient;

    //中断poll
    uint64_t buffer = 1;
    int res = write(m_conSock, &buffer, sizeof(uint64_t));
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
            std::cout << "接收到消息" << m_pollfdVector.size();

            if(i->revents == 0)
            {
                Debug::Log("a");
                ++i;
                continue;
            }

            if(i->fd == m_conSock)
            {
                //线程通信
                uint64_t buffer;
                read(i->fd, &buffer, sizeof(uint64_t));
                --readCount;
                ++i;
                std::cout << "CheckLobby接收到线程同步消息-" << m_pollfdVector.size() << std::endl;
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
                Debug::Log("接收到JoinMessage，移动到游戏大厅");
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

CheckLobby *CheckLobby::m_instance = CheckLobby::Init();
