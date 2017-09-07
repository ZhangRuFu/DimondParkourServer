//
// Created by zrf on 17-9-7.
//

#ifndef DIMONDPARKOUR_PLAYER_H
#define DIMONDPARKOUR_PLAYER_H
#include <string>

//玩家信息
class Player
{
private:
    std::u16string m_uid;
    std::u16string m_name;
    int m_x, m_y;

public:
    Player(std::u16string uid) : m_uid(uid){m_x = m_y = 0;}
    int GetX(void) {return m_x;}
    int GetY(void) {return m_y;}
    void SetX(int x) { m_x = x;}
    void SetY(int y) { m_y = y;}
};

#endif //DIMONDPARKOUR_PLAYER_H
