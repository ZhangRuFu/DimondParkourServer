//
// Created by zrf on 9/5/17.
//

#ifndef DIMONDPARKOUR_ENCODING_H
#define DIMONDPARKOUR_ENCODING_H
#include <codecvt>
#include <locale>
//编码转换-UTF-8与UTF-16的转换
class Encoding
{
private:
    static std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t > m_converter;
    Encoding(){}
public:
    static std::string ToBytes(const char16_t *utf16Str);    //UTF-16至UTF-8
    static std::u16string FromBytes(const char *utf8Str);    //UTF-8至UTF-16
    static std::u16string FromBytes(const char *strStart, const char *strEnd);
};

#endif //DIMONDPARKOUR_ENCODING_H
