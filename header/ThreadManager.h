//
// Created by zrf on 17-9-7.
//

#ifndef DIMONDPARKOUR_THREADMANAGER_H
#define DIMONDPARKOUR_THREADMANAGER_H

#include <vector>
#include <thread>
class ThreadManager
{
private:
    std::vector<std::thread*> m_threads;

public:
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
};

#endif //DIMONDPARKOUR_THREADMANAGER_H
