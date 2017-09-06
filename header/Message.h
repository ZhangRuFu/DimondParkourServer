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
    enum MessageType{Join, Chat};

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
#endif //DIMONDPARKOUR_MESSAGE_H
