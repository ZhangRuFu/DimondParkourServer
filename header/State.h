//
// Created by zrf on 17-9-11.
//

#ifndef DIMONDPARKOUR_STATE_H
#define DIMONDPARKOUR_STATE_H

class Client;
class Message;

//状态基类
class State
{
protected:
    Client *m_client;

public:
    State(Client *client) : m_client(client){}
    virtual void Enter(void) = 0;
    virtual State* Execute(Message &message) = 0;
    virtual void Quit(void) = 0;
};


//等待审核状态(JoinMessage)
class CheckState : public State
{
public:
    CheckState(Client *client) : State(client){}
    virtual void Enter(void);
    virtual State* Execute(Message &message);
    virtual void Quit(void);
};

//加入游戏状态（等待StartGame或者ShopMessage消息）
class JoinState : public State
{
public:
    JoinState(Client *client) : State(client){}
    virtual void Enter(void);
    virtual State* Execute(Message &message);
    virtual void Quit(void);
};

//游戏状态
class GameState : public State
{
public:
    GameState(Client *client) : State(client){}
    virtual void Enter(void);
    virtual State* Execute(Message &message);
    virtual void Quit(void);
};
#endif //DIMONDPARKOUR_STATE_H
