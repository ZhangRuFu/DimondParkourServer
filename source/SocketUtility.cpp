//
// Created by zrf on 17-9-12.
//

#include "../header/SocketUtility.h"
#include "../header/Encoding.h"
#include "../header/Convert.h"
#include <unistd.h>

void SocketUtility::SendMessage(int socket, Message &m)
{
    std::string buffer = m.Serialize();
    int len = buffer.size();
    buffer = Convert::IntToU8String(len) + " " + buffer;
    write(socket, buffer.data(), buffer.size());
}