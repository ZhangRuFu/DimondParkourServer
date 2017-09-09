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
    enum MessageType{Join, Chat, StartGame, StartShop, Fight, Position, GameOver, GameWin};

private:
    MessageType m_type;

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

public:
    FightMessage(void) : Message(Message::MessageType::Fight){}

    void SetFightInfo(std::u16string uid, std::u16string name) {m_uid = uid, m_name = name;}
    std::u16string GetFightUID(void){return m_uid;}
    std::u16string GetFightName(void) {return m_name;}

    virtual int Deserialize(SerializeStream &stream);
    virtual std::string Serialize(void);
};

//游戏逻辑消息（位置同步）
class PositionMessage : public Message
{
private:
    int m_x, m_y;

public:
    PositionMessage(void) : Message(Message::MessageType::Position){}

    void SetPosition(int x, int y){m_x = x, m_y = y;}
    int GetX(void) { return m_x; }
    int GetY(void) { return m_y; }

    virtual int Deserialize(SerializeStream &stream);
    virtual std::string Serialize(void);
};

#endif //DIMONDPARKOUR_MESSAGE_H
