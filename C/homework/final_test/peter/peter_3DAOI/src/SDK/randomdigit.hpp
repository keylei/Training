#ifndef RANDOMDIGIT_HPP
#define RANDOMDIGIT_HPP

#include <iostream>
#include <random>

namespace SDK
{
    /**
     *  @brief RandomDigit
     *
     *      RandomDigit类是生成随机数的类
     *
     *      包含静态成员函数randomDigit(),通过传入精度,最小值,最大值,生成指定
     *  精度的double型随机数.
     *
     *  @author peter
     *  @version 1.00 2017-12-05 peter
     *                note:create it
     */
    class RandomDigit
    {
    public:
        RandomDigit();
        virtual~RandomDigit();

        static double randomDigit( int precision,
                            int min,
                            int max )
        {
            int divisor = 1;            //除数,
            for ( int i = 0; i < precision; ++i )
            {
                min *= 10;              // 最小值*10
                max *= 10;              // 最大值*10
                divisor *= 10;          // 除数*10
            }
            std::random_device seed;    // 设置随机数种子
            std::default_random_engine engine = std::default_random_engine(seed());
            std::uniform_int_distribution<int> randomDigit(min,max);

            return randomDigit(engine)*1.0/divisor;
        }
    };

}//End of namespace SDK

#endif // RANDOMDIGIT_HPP

