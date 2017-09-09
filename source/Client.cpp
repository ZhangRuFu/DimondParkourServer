//
// Created by zrf on 17-9-7.
//

#include "../header/Client.h"
#include "../header/Encoding.h"
#include "../header/Message.h"
#include "../header/SerializeStream.h"
#include <unistd.h>
#include <iostream>
#include <string>

void Client::Init(JoinMessage &message)
{
    //建立Player
    //==================================根据UID查用户信息========================
    m_player = new Player(message.GetUID());
}

//资源释放
Client::~Client()
{
    //===========================Player应该进行数据持久化===============================
    delete m_player;
    close(m_clientSocket);
}