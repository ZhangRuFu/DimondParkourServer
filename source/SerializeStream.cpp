//
// Created by zrf on 9/5/17.
//

#include "../header/SerializeStream.h"
#include "../header/Encoding.h"

using std::vector;

//接收UTF-8字节流进行解码
SerializeStream::SerializeStream(char *buffer, int size)
{
    buffer[size] = 0;
    m_info = Encoding::FromBytes(buffer);
    Split();
}

void SerializeStream::Split()
{
    vector<int> spacePos;
    //找空格的位置
    for(int i = 0; i < m_info.size(); ++i)
        if(m_info[i] == u' ')
            spacePos.push_back(i);

    //Split
    if(spacePos[0] != 0)
        m_splitInfo.push_back(std::make_pair(0, spacePos[0] - 1));
    for(int i = 0; i < spacePos.size() - 1; ++i)
        m_splitInfo.push_back(std::make_pair(spacePos[i] + 1, spacePos[i + 1] - 1));
    if(spacePos[spacePos.size() - 1] != m_info.size() - 1)
        m_splitInfo.push_back(std::make_pair(spacePos[spacePos.size() - 1], m_info.size() - 1));
}

std::u16string SerializeStream::GetString(int index)
{
    return m_info.substr(m_splitInfo[index].first, m_splitInfo[index].second);
}