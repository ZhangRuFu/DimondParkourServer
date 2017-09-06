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

    static std::u16string IntToU16String(int num);
    static std::u16string FloatToU16String(float num);
    static std::u16string DoubleToU16String(double num);

    static std::string IntToU8String(int num);
    static std::string FloatToU8String(float num);
    static std::string DoubleToU8String(double num);
};

#endif //DIMONDPARKOUR_CONVERT_H
