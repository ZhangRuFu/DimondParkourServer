//
// Created by zrf on 17-9-5.
//

#include "../header/Message.h"
#include "../header/Convert.h"
#include "../header/SerializeStream.h"
#include "../header/Encoding.h"
#include <string>

using std::u16string;

//===========================Message==========================

std::string Message::Serialize(void)
{
    return Convert::IntToU8String(m_type);
}

int Message::Deserialize(SerializeStream &stream)
{
    m_type = (MessageType)Convert::StringToInt(stream.GetString(0));
    return 0;
}


//===========================JoinMessage======================
std::string JoinMessage::Serialize(void)
{
    return Message::Serialize() + " " + Encoding::ToBytes(m_uid.data());
}

int JoinMessage::Deserialize(SerializeStream &stream)
{
    int index = Message::Deserialize(stream);
    ++index;
    m_uid = stream.GetString(index);
    return index;
}


//===========================ChatMessage======================
std::string ChatMessage::Serialize(void)
{
    return Message::Serialize() + " " + Encoding::ToBytes(m_chatInfo.data());
}

int ChatMessage::Deserialize(SerializeStream &stream)
{
    int index = Message::Deserialize(stream);
    ++index;
    m_chatInfo = stream.GetString(index);
    return index;
}

//==========================FightMessage=======================
std::string FightMessage::Serialize()
{
    return Message::Serialize() + " " + Encoding::ToBytes(m_uid.data()) + " " + Encoding::ToBytes(m_name.data());
}

int FightMessage::Deserialize(SerializeStream &stream)
{
    int index = Message::Deserialize(stream);
    ++index;
    m_uid = stream.GetString(index);
    ++index;
    m_name = stream.GetString(index);
    return index;
}
