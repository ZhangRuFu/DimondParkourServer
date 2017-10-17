//
// Created by zrf on 17-9-7.
//

#ifndef DIMONDPARKOUR_GAMELOBBY_H
#define DIMONDPARKOUR_GAMELOBBY_H

#include <set>
#include <vector>
#include <map>
#include <poll.h>
#include <list>
#include <queue>
#include <thread>
#include "../header/Client.h"
#include "GameRoom.h"
//游戏大厅
//登录游戏后都将加入大厅
class GameLobby
{
private:
    //游戏房间
    std::list<GameRoom*> m_gameRooms;
    std::map<GameRoom*, std::thread*> m_roomThreads;

    //准备开始游戏队列
    std::queue<Client*> m_readyGame;

    //新成员队列
    std::queue<Client*> m_newCommer;
    //大厅队列
    std::vector<pollfd> m_pollVector;
    std::map<int, Client*> m_lobby;
    static GameLobby* m_instance;

    //清理队列
    std::vector<Client*> m_leaveClient;

    //线程间通信
    int m_conSock;

private:
    GameLobby();
    void CreateGameRoom(Client *c1, Client *c2);

public:
    //游戏大厅循环
    void Update(void);

    void JoinLobby(Client *newPlayer);
    void StartGame(Client *client);
    void Leave(Client *client);
    void Dissolve(GameRoom *client);

    int Count(void) {return m_lobby.size();}

    //单例
    static GameLobby* Instance(void){return m_instance;}
    static void GameThread(GameRoom *room);

private:
    static GameLobby* Init(void);

};

#endif //DIMONDPARKOUR_GAMELOBBY_H
