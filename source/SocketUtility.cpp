//
// Created by zrf on 17-9-12.
//

#include "../header/SocketUtility.h"
#include "../header/Encoding.h"
#include "../header/Convert.h"
#include <unistd.h>
#include <iostream>

void SocketUtility::SendMessage(int socket, Message &m)
{
    std::string buffer = m.Serialize();
    std::cout << "回送消息" << buffer << std::endl;
    int len = buffer.size();
    buffer = Convert::ToU8String(len) + " " + buffer;
    write(socket, buffer.data(), buffer.size());
}