#ifndef RANDOMNUM_HPP
#define RANDOMNUM_HPP

#include <cstdlib>

#include "sdk/Customexception.hpp"

namespace SDK
{
    /**
     *  @brief NumRandom
     *         获取随机数
     *  @author bob
     *  @version 1.00 2017-12-01 bob
     *                note:create it
     */
    class RandomNumber
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        RandomNumber();

        ~RandomNumber();
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //member functions

        /*
        *  @brief  randomInt
        *          随机生成区间(min,max)区间的浮点数
        *  @param  max:随机数的最大值
        *          min:随机数的最小值
        *  @return 随机生成的double形浮点数
        */
        static double randomDouble(double min , double max);

        /*
        *  @brief  randomByte
        *          随机生成区间(min,max)区间的Byte数
        *  @param  max:随机数的最大值
        *          min:随机数的最小值
        *  @return 随机生成一个byte数
        */
        static unsigned char randomByte(unsigned char min, unsigned char max );
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    };
}   //End of namespace SSDK

#endif // RANDOMNUM_HPP
