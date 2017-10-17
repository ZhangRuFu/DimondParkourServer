//
// Created by zrf on 17-9-5.
//
#include "../header/Convert.h"
#include "../header/Encoding.h"

int Convert::StringToInt(std::u16string str)
{
    int num;
    std::string u8Str = Encoding::ToBytes(str.data());
    sscanf(u8Str.data(), "%d", &num);
    return num;
}

float Convert::StringToFloat(std::u16string str)
{
    float num;
    std::string u8Str = Encoding::ToBytes(str.data());
    sscanf(u8Str.data(), "%f", &num);
    return num;
}

double Convert::StringToDouble(std::u16string str)
{
    double num;
    std::string u8Str = Encoding::ToBytes(str.data());
    sscanf(u8Str.data(), "%lf", &num);
    return num;
}

std::u16string Convert::ToU16String(int num)
{
    char buffer[10];
    sprintf(buffer, "%d", num);
    std::u16string str = Encoding::FromBytes(buffer);
    return str;
}

std::u16string Convert::ToU16String(float num)
{
    char buffer[10];
    sprintf(buffer, "%f", num);
    std::u16string str = Encoding::FromBytes(buffer);
    return str;
}

std::u16string Convert::ToU16String(double num)
{
    char buffer[10];
    sprintf(buffer, "%lf", num);
    std::u16string str = Encoding::FromBytes(buffer);
    return str;
}


std::string Convert::ToU8String(int num)
{
    char buffer[10];
    sprintf(buffer, "%d", num);
    return std::string(buffer);
}

std::string Convert::ToU8String(float num)
{
    char buffer[10];
    sprintf(buffer, "%f", num);
    return std::string(buffer);
}

std::string Convert::ToU8String(double num)
{
    char buffer[10];
    sprintf(buffer, "%lf", num);
    return std::string(buffer);
}