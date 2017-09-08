//
// Created by zrf on 9/5/17.
//

#ifndef DIMONDPARKOUR_SERIALIZESTREAM_H
#define DIMONDPARKOUR_SERIALIZESTREAM_H
#include <string>
#include <utility>
#include <vector>
//接收网络字节流并进行转码
class SerializeStream
{
private:
    std::u16string m_info;
    std::vector<std::pair<int, int>> m_splitInfo;

public:
    SerializeStream(char *buffer, int size);

    int GetFieldCount(void){return m_splitInfo.size();}
    std::pair<int, int> GetPair(int index){return m_splitInfo[index];}
    std::u16string GetString(int index);
    int GetFlag(void);

private:
    void Split(void);
};

#endif //DIMONDPARKOUR_SERIALIZESTREAM_H
