//
// Created by zrf on 17-9-11.
//

#include "../header/State.h"
#include "../header/Message.h"
#include "../header/Player.h"
#include "../header/Client.h"
#include "../header/GameLobby.h"

//等待校验状态
void CheckState::Enter()
{

}

State* CheckState::Execute(Message &message)
{
    //接受JoinMessage进行校验，通过则转移到JoinState
    if(message.GetMessageType() == Message::MessageType::Join)
    {
        JoinMessage &joinMessage = dynamic_cast<JoinMessage&>(message);

        //======================向数据库查询玩家信息====================
        Player *p = new Player(joinMessage.GetUID());
        m_client->SetPlayer(p);

        //状态转移至JoinState
        JoinState *newState = new JoinState(m_client);
        return  newState;
    }

    return nullptr;
}

void CheckState::Quit()
{

}


//游戏大厅状态
void JoinState::Enter()
{

}

State* JoinState::Execute(Message &message)
{
    //接收StartGameMessage，收到进入排队大厅
    if(message.GetMessageType() == Message::MessageType::StartGame)
    {
        //转入游戏匹配队列
        GameLobby::Instance()->StartGame(m_client);
    }//接收ShopMessage，收到进入商城
    else if(message.GetMessageType() == Message::MessageType::StartShop)
    {
        //...
    }

}

void JoinState::Quit()
{

}

//游戏状态
void GameState::Enter()
{

}

State* GameState::Execute(Message &message)
{
    //接收位置信息，同步到客户端
}

void GameState::Quit()
{

}