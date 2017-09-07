//
// Created by zrf on 17-9-7.
//

#include "../header/GameLobby.h"
#include "../header/Debug.h"

GameLobby* GameLobby::Init()
{
    if(m_instance == nullptr)
        m_instance = new GameLobby();
    return m_instance;
}

void GameLobby::JoinLobby(Client *newPlayer)
{
    m_lobby.insert(newPlayer);
    Debug::Log("新客户端加入");
}

GameLobby *GameLobby::m_instance = GameLobby::Init();