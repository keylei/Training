#include "NumRandom.hpp"

using namespace std;
using namespace SSDK;

NumRandom::NumRandom()
{

}

NumRandom::~NumRandom()
{

}

double NumRandom::randomDouble(double min, double max)
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


int NumRandom::generateRandomInt(int min, int max)
{
    if(max >= min)
    {
        // 调用随机数引擎类，用于生成随机整数，设置时间函数为随机种子
        static default_random_engine random(time(NULL));
        // 调用浮点型分布类，用于设置随机数范围
        uniform_int_distribution<int>range(min, max);
        // 返回生成的随机数
        return range(random);
    }
    else
    {
         THROW_EXCEPTION("生成随机数异常:最大值小于最小值!")
    }
}

double NumRandom::generateRandomReal(double min, double max)
{
    if(max >= min)
    {
        // 调用随机数引擎类，用于生成随机浮点数，设置时间函数为随机种子
        static default_random_engine random(time(NULL));
        // 调用浮点型分布类，用于设置随机数范围
        uniform_real_distribution<double>range(min, max);
        // 返回生成的随机数
        return range(random);
    }
    else
    {
         THROW_EXCEPTION("生成随机数异常:最大值小于最小值!")
    }
}

