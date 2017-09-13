//
// Created by zrf on 17-9-9.
//

#ifndef DIMONDPARKOUR_GAMEROOM_H
#define DIMONDPARKOUR_GAMEROOM_H

class Client;
class PositionMessage;

//游戏房间
//对游戏进度进行管理
class GameRoom
{
private:
    Client* m_client[2];
    static const int BUFFSIZE = 128;
    char m_buffer[BUFFSIZE];        //房间缓冲区
    bool m_gaming = true;

public:
    GameRoom(Client *c1, Client *c2);
    void Update(void);
    void SynchronizePosition(PositionMessage &message, Client *client);
    void GameOver(Client *client);
    static void GameRoomThread(GameRoom *room);
};

#endif //DIMONDPARKOUR_GAMEROOM_H
