#include "NumRandom.hpp"


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
        //rime 这里最好的做法是把最大值和最小值也显示出来
         THROW_EXCEPTION("生成随机数异常:最大值小于最小值!")
    }
}

unsigned char NumRandom::randomByte(int max, int min)
{
    unsigned char byte = (unsigned char)rand()%(max-min)+min;
    return byte;
}


