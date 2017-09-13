//
// Created by zrf on 17-9-12.
//

#ifndef DIMONDPARKOUR_SOCKETUTILITY_H
#define DIMONDPARKOUR_SOCKETUTILITY_H

#include "Message.h"

class SocketUtility
{
public:
    static void SendMessage(int socket, Message &m);
};

#endif //DIMONDPARKOUR_SOCKETUTILITY_H
