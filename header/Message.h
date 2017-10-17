//
// Created by zrf on 9/5/17.
//

#ifndef DIMONDPARKOUR_MESSAGE_H
#define DIMONDPARKOUR_MESSAGE_H
#include <string>

class SerializeStream;

//消息基类
class Message
{
public:
    Message(MessageType type) : m_type(type){}

    MessageType GetMessageType(void){return m_type;}

    virtual int Deserialize(SerializeStream &stream);
    virtual std::string Serialize(void);


};

//加入游戏消息
class JoinMessage : public Message
{
private:
    std::u16string m_uid;

public:
    JoinMessage(void) : Message(Message::MessageType::Join){}

    void SetUID(const char16_t *uid) {m_uid = uid;}
    std::u16string GetUID(void) {return m_uid;}

    virtual int Deserialize(SerializeStream &stream);
    virtual std::string Serialize(void);
};


//聊天消息
class ChatMessage : public Message
{
private:
    std::u16string m_chatInfo;

public:
    ChatMessage(void) : Message(Message::MessageType::Chat){}

    void SetChatInfo(const char16_t *chatInfo) {m_chatInfo = chatInfo;}
    std::u16string GetChatInfo(void) {return m_chatInfo;}

    virtual int Deserialize(SerializeStream &stream);
    virtual std::string Serialize(void);
};

//对战消息
class FightMessage : public Message
{
private:
    std::u16string m_uid;       //对手UID
    std::u16string m_name;      //对手姓名
    int m_playerX, m_playerZ;   //我方坐标
    int m_enemyX, m_enemyZ;     //地方坐标
    int m_seed;

public:
    FightMessage(void) : Message(Message::MessageType::Fight){}

    void SetFightInfo(std::u16string uid, std::u16string name) {m_uid = uid, m_name = name;}
    void SetPlayerX(int x) {m_playerX = x;}
    void SetPlayerZ(int z) {m_playerZ = z;}
    void SetEnemyX(int x) {m_enemyX = x;}
    void SetEnemyZ(int z) {m_enemyZ = z;}
    void SetSeed(int seed) {m_seed = seed;}

    std::u16string GetFightUID(void){return m_uid;}
    std::u16string GetFightName(void) {return m_name;}
    int GetSeed(void) {return m_seed;}


    virtual int Deserialize(SerializeStream &stream);
    virtual std::string Serialize(void);
};

//游戏逻辑消息（位置同步-操作同步）
class PositionMessage : public Message
{
private:
    char m_operation;       //左还是右

public:
    PositionMessage(void) : Message(Message::MessageType::Position){}

    void SetOperation(char operation){m_operation = operation;}
    int GetOperation(void) { return m_operation; }

    virtual int Deserialize(SerializeStream &stream);
    virtual std::string Serialize(void);
};

#endif //DIMONDPARKOUR_MESSAGE_H
