#include "RandomNumber.hpp"

using namespace SDK;

RandomNumber::RandomNumber()
{

}

RandomNumber::~RandomNumber()
{

}

double RandomNumber::randomDouble(double min, double max)
{
    try
    {
        if(max >= min)
        {
            double randomNum = (rand() / (double)RAND_MAX) * (max - min) + min;
            return randomNum;
        }
        else
        {
            THROW_EXCEPTION("随机生成浮点数失败!");
        }
    }
    catch(...)
    {
        THROW_EXCEPTION("生成随机浮点数失败!");
    }
}

unsigned char RandomNumber::randomByte(unsigned char min, unsigned char max)
{
    try
    {
        if(max >= min)
        {
            double randomNum = (rand() % (max -min + 1)) + min;
            return randomNum;
        }
        else
        {
            THROW_EXCEPTION("生成随机数异常:最大值小于最小值!");
        }
    }
    catch(...)
    {
        THROW_EXCEPTION("随机生成byte数字失败!");
    }
}


