//
// Created by zrf on 17-9-8.
//

#ifndef DIMONDPARKOUR_CHECKLOBBY_H
#define DIMONDPARKOUR_CHECKLOBBY_H

#include <vector>
#include <map>
#include <poll.h>
#include "Client.h"

//对新加入的客户端进行身份审核和初始化
class CheckLobby
{
private:
    std::vector<pollfd> m_pollfdVector;
    std::map<int, Client*> m_clientMap;
    int m_conSock;                      //线程间通信套接字

    static CheckLobby *m_instance;

private:
    CheckLobby();
    static CheckLobby* Init(void);

public:
    void Update(void);
    void Add(Client *newClient);
    static CheckLobby* Instance(void){return m_instance;}
};

#endif //DIMONDPARKOUR_CHECKLOBBY_H
