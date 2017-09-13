//
// Created by zrf on 9/5/17.
//

#ifndef DIMONDPARKOUR_SERIALIZESTREAM_H
#define DIMONDPARKOUR_SERIALIZESTREAM_H
#include <string>
#include <utility>
#include <vector>

class Message;

//接收网络字节流并进行转码
class SerializeStream
{
private:
    char *m_buffer = nullptr;
    int m_size = 0;
    std::u16string m_info;
    std::vector<std::pair<int, int>> m_splitInfo;
    std::vector<Message*> m_messages;

public:
    int GetFieldCount(void){return m_splitInfo.size();}
    std::pair<int, int> GetPair(int index){return m_splitInfo[index];}
    std::u16string GetString(int index);
    int GetFlag(void);
    std::vector<Message*>& GetMessages(void){return m_messages;}

    void AcceptStream(char *buffer, int size);

private:
    std::pair<int, int> GetLength(int start);   //获取消息长度，第一个为长度后开始位置，第二个为消息长度
    void DisposeMessage(void);
    Message* GenerateMessage(void);
    void Split(void);
    void Clear(void);

};

#endif //DIMONDPARKOUR_SERIALIZESTREAM_H
