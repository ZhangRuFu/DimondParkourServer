//
// Created by zrf on 9/5/17.
//

#include "../header/Encoding.h"

using namespace std;
string Encoding::ToBytes(const char16_t *utf16Str)
{
    return m_converter.to_bytes(utf16Str);
}

u16string Encoding::FromBytes(const char *utf8Str)
{
    return m_converter.from_bytes(utf8Str);
}

wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t > Encoding::m_converter;