#include "numrandom.hpp"

using namespace SSDK;

NumRandom::NumRandom()
{

}

NumRandom::~NumRandom()
{

}

double NumRandom::randomDouble(double max, double min)
{
    if(max >= min)
    {
        double randomNum = (rand() / (double)RAND_MAX) * (max - min);
        return randomNum;
    }
    else
    {
        THROW_EXCEPTION("生成随机数异常:最大值小于最小值!")
    }
}

unsigned char NumRandom::randomByte(unsigned char min, unsigned char max)
{
    if(max >= min)
    {
        unsigned char randomNum = (rand() % (max - min + 1))+ min;
        return randomNum;
    }
    else
    {
        THROW_EXCEPTION("生成随机数异常:最大值小于最小值!")
    }
}


