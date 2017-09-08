//
// Created by zrf on 17-9-7.
//

#ifndef DIMONDPARKOUR_GAMELOBBY_H
#define DIMONDPARKOUR_GAMELOBBY_H

#include <set>
#include "../header/Client.h"

class Player;

//游戏大厅
//登录游戏后都将加入大厅
class GameLobby
{
private:
    std::set<Client*> m_lobby;

    static GameLobby* m_instance;

private:
    GameLobby(){}

public:
    void JoinLobby(Client *newPlayer);
    int Count(void) {return m_lobby.size();}

    static GameLobby* Instance(void){return m_instance;}

private:
    static GameLobby* Init(void);

};

#endif //DIMONDPARKOUR_GAMELOBBY_H