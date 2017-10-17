//
// Created by zrf on 17-9-7.
//

#ifndef DIMONDPARKOUR_DEBUG_H
#define DIMONDPARKOUR_DEBUG_H
#include <iostream>

class Debug
{
public:
    static void Log(const char *info)
    {
        std::cout << info << std::endl;
    }

    static void Warning(const char *info)
    {
        std::cout << info << std::endl;
    }

    static void Error(const char *info)
    {
        std::cout << info << std::endl;
    }
};

#endif //DIMONDPARKOUR_DEBUG_H
