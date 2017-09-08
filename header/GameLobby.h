//
// Created by zrf on 17-9-7.
//

#ifndef DIMONDPARKOUR_GAMELOBBY_H
#define DIMONDPARKOUR_GAMELOBBY_H

#include <set>
#include <vector>
#include <map>
#include <poll.h>
#include "../header/Client.h"

//游戏大厅
//登录游戏后都将加入大厅
class GameLobby
{
private:
    std::vector<pollfd> m_pollVector;
    std::map<int, Client*> m_lobby;
    static GameLobby* m_instance;

private:
    GameLobby(){}

public:
    void JoinLobby(Client *newPlayer);
    //游戏大厅循环
    void Update(void);
    int Count(void) {return m_lobby.size();}

    //单例
    static GameLobby* Instance(void){return m_instance;}


private:
    static GameLobby* Init(void);

};

#endif //DIMONDPARKOUR_GAMELOBBY_H
