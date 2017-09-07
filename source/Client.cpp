//
// Created by zrf on 17-9-7.
//

#include "../header/Client.h"
#include "../header/Encoding.h"
#include "../header/Message.h"
#include "../header/SerializeStream.h"
#include "../header/GameLobby.h"
#include <unistd.h>
#include <iostream>
#include <string>

bool Client::Init()
{
    //JoinMessage
    int recvSize = read(m_clientSocket, m_buffer, BUFFERSIZE);
    m_buffer[recvSize] = 0;
    std::u16string str = Encoding::FromBytes(m_buffer);
    int messageType = str[0] - u'0';
    //Message校验
    if(messageType != Message::MessageType::Join)
    {
        std::cout << "消息错误" << std::endl;
        return false;
    }
    //建立Player
    JoinMessage jm;
    SerializeStream ss(m_buffer, recvSize);
    jm.Deserialize(ss);
    //==================================根据UID查用户信息========================
    m_player = new Player(jm.GetUID());

    //加入游戏大厅
    GameLobby::Instance()->JoinLobby(this);
    return true;
}

void Client::Update()
{
    //等待接收消息
    //1、商店消息
    //2、开始游戏消息
}

void Client::operator()(void)
{
    bool res = Init();
    if(!res)
        return;
    else
        Update();
}

//资源释放
Client::~Client()
{
    //===========================Player应该进行数据持久化===============================
    delete m_player;
    close(m_clientSocket);
}