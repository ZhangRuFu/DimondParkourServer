//
// Created by zrf on 17-9-5.
//

#ifndef DIMONDPARKOUR_CONVERT_H
#define DIMONDPARKOUR_CONVERT_H
#include <string>
//数字-字符串转换和字符串格式化
class Convert
{
public:
    static int StringToInt(std::u16string str);
    static float StringToFloat(std::u16string str);
    static double StringToDouble(std::u16string str);

    static std::u16string ToU16String(int num);
    static std::u16string ToU16String(float num);
    static std::u16string ToU16String(double num);

    static std::string ToU8String(int num);
    static std::string ToU8String(float num);
    static std::string ToU8String(double num);
};

#endif //DIMONDPARKOUR_CONVERT_H
