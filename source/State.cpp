//
// Created by zrf on 17-9-11.
//

#include "../header/State.h"
#include "../header/Message.h"
#include "../header/Player.h"
#include "../header/Client.h"
#include "../header/GameLobby.h"
#include "../header/SocketUtility.h"
#include "../header/Debug.h"

//等待校验状态
void CheckState::Enter()
{
    Debug::Log("进入Check状态");
    if(m_client->GetServerPosition() != Client::ServerPosition::GameLobby)
    {
        GameLobby::Instance()->JoinLobby(m_client);
        m_client->SetServerPosition(Client::ServerPosition::GameLobby);
    }
}

State* CheckState::Execute(Message &message)
{
    Debug::Log("CheckState执行");
    //接受JoinMessage进行校验，通过则转移到JoinState
    if(message.GetMessageType() == Message::MessageType::Join)
    {
        JoinMessage &joinMessage = dynamic_cast<JoinMessage&>(message);

        //======================向数据库查询玩家信息====================
        Player *p = new Player(joinMessage.GetUID());
        p->SetName(u"John");
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
    Debug::Log("进入JoinState");
    if(m_client->GetServerPosition() != Client::ServerPosition::GameLobby)
    {
        GameLobby::Instance()->JoinLobby(m_client);
        m_client->SetServerPosition(Client::ServerPosition::GameLobby);
    }
}

State* JoinState::Execute(Message &message)
{
    //接收StartGameMessage，收到进入排队大厅
    if(message.GetMessageType() == Message::MessageType::StartGame)
    {
        //转入游戏匹配队列
        GameLobby::Instance()->StartGame(m_client);
    }//接收到FightMessage转游戏状态
    else if(message.GetMessageType() == Message::MessageType::Fight) {
        m_client->FeedBackMessage(message);
        GameState *gameState = new GameState(m_client);
        return gameState;
    }//接收ShopMessage，收到进入商城
    else if(message.GetMessageType() == Message::MessageType::StartShop)
    {
        //...
    }
    return nullptr;
}

void JoinState::Quit()
{

}

//游戏状态
void GameState::Enter()
{
    Debug::Log("进入GameSate");
    m_client->SetServerPosition(Client::ServerPosition::GameRoom);
}

State* GameState::Execute(Message &message)
{
    //接收位置信息，告知游戏房间进行同步
    if(message.GetMessageType() == Message::MessageType::Position)
    {
        PositionMessage m = dynamic_cast<PositionMessage&>(message);
        m_room->SynchronizePosition(m, m_client);
        return nullptr;
    }
        //我方胜利
    else if(message.GetMessageType() == Message::MessageType::GameWin)
        m_client->FeedBackMessage(message);
        //我方失败
    else if(message.GetMessageType() == Message::MessageType::GameOver)
        m_room->GameOver(m_client);
    else
        return nullptr;

    //移动到游戏大厅
    JoinState *js = new JoinState(m_client);
    return js;
}

void GameState::Quit()
{

}