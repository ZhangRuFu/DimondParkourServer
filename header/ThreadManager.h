//
// Created by zrf on 17-9-7.
//

#ifndef DIMONDPARKOUR_THREADMANAGER_H
#define DIMONDPARKOUR_THREADMANAGER_H

#include <vector>
#include <thread>
#include "../header/GameLobby.h"

class ThreadManager
{
private:
    std::vector<std::thread*> m_threads;

public:
    ThreadManager(void)
    {
        //开辟游戏大厅线程
        std::thread *LobbyThread = new std::thread(GameLobbyThread);
        Add(LobbyThread);
    }

    void Add(std::thread *newThread){m_threads.push_back(newThread);}

    ~ThreadManager(void)
    {
        Release();
    }

private:
    void Release(void)
    {
        for(int i = 0; i < m_threads.size(); ++i)
            delete m_threads[i];
    }

    static void GameLobbyThread(void)
    {
        GameLobby::Instance()->Update();
    }
};

#endif //DIMONDPARKOUR_THREADMANAGER_H
