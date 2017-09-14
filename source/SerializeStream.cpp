//
// Created by zrf on 9/5/17.
//

#include "../header/SerializeStream.h"
#include "../header/Encoding.h"
#include "../header/Convert.h"
#include "../header/Message.h"

using std::vector;

void SerializeStream::AcceptStream(char *buffer, int size)
{
    Clear();
    m_buffer = buffer;
    m_size = size;
    m_buffer[m_size] = 0;
    DisposeMessage();
}

void SerializeStream::DisposeMessage()
{
    //FIN消息
    if(m_size == 0)
    {
        Message *m = new Message(Message::MessageType::Quit);
        m_messages.push_back(m);
        return;
    }
    //多个消息可能会叠加到一起，根据长度进行
    int start = 0, end = 0;
    std::pair<int, int> pos;
    while(end < m_size)
    {
        pos = GetLength(start);
        start = pos.first;
        end = start + pos.second;
        m_info = Encoding::FromBytes(m_buffer + start, m_buffer + end);
        Split();
        m_messages.push_back(GenerateMessage());
        start = end;
    }
}

void SerializeStream::Split()
{
    vector<int> spacePos;
    //找空格的位置
    for(int i = 0; i < m_info.size(); ++i)
        if(m_info[i] == u' ')
            spacePos.push_back(i);

    //Split
    if(spacePos.size() == 0)
        m_splitInfo.push_back(std::make_pair(0, m_info.size() - 1));
    else {//防止Message类无空格消息
        if (spacePos[0] != 0)
            m_splitInfo.push_back(std::make_pair(0, spacePos[0] - 1));
        for (int i = 0; i < spacePos.size() - 1; ++i)
            m_splitInfo.push_back(std::make_pair(spacePos[i] + 1, spacePos[i + 1] - 1));
        if (spacePos[spacePos.size() - 1] != m_info.size() - 1)
            m_splitInfo.push_back(std::make_pair(spacePos[spacePos.size() - 1] + 1, m_info.size() - 1));
    }
}

std::u16string SerializeStream::GetString(int index)
{
    return m_info.substr(m_splitInfo[index].first, m_splitInfo[index].second);
}

int SerializeStream::GetFlag()
{
    if(m_info.size() != 0)
        return m_info[0] - u'0';
}

std::pair<int, int> SerializeStream::GetLength(int start)
{
    int spaceIndex = start;
    for(; spaceIndex < m_size; ++spaceIndex)
        if(m_buffer[spaceIndex] == ' ')
            break;
    ++spaceIndex;
    int len = Convert::StringToInt(Encoding::FromBytes(m_buffer + start, m_buffer + spaceIndex));
    return std::make_pair(spaceIndex, len);
}

Message* SerializeStream::GenerateMessage()
{
    //根据type系列化消息
    Message *m = nullptr;
    int type = GetFlag();
    switch(type)
    {
        case Message::MessageType ::StartGame:
        case Message::MessageType ::GameWin:
        case Message::MessageType ::GameOver:
        case Message::MessageType ::StartShop:
            m = new Message((Message::MessageType)type);
            return m;
        case Message::MessageType ::Join:
            m = new JoinMessage();
            break;
        case Message::MessageType ::Chat:
            m = new ChatMessage();
            break;
        case Message::MessageType ::Position:
            m = new PositionMessage();
            break;
        case Message::MessageType ::Fight:
            m = new FightMessage();
            break;
    }
    m->Deserialize(*this);
    return m;
}

void SerializeStream::Clear()
{
    m_buffer = nullptr;
    m_size = 0;
    m_info.clear();
    m_splitInfo.clear();
    for(int i = 0; i < m_messages.size(); ++i)
    {
        delete m_messages[i];
        m_messages[i] = nullptr;
    }
    m_messages.clear();
}