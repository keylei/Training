#ifndef RANDOMNUM_HPP
#define RANDOMNUM_HPP

#include <cstdlib>

#include "sdk/customexception.hpp"

namespace SSDK
{
    /**
     *  @brief RandomNum
     *         随机生成区间(min - max)的浮点数
     *  @author bob
     *  @version 1.00 2017-12-01 bob
     *                note:create it
     */
    class NumRandom
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
         * @brief NumRandom
         */
        NumRandom();

        /**
         * @brief ~NumRandom
         */
        ~NumRandom();
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        /**
        *  @brief  randomDouble
        *          随机生成区间(min,max)区间的浮点数
        *  @param  max:随机数的最大值
        *          min:随机数的最小值
        *  @return 随机生成的double形浮点数
        */
        static double randomDouble(double max , double min);

        /**
        *  @brief  randomByte
        *          随机生成区间(min,max)区间的浮点数
        *  @param  max:随机数的最大值
        *          min:随机数的最小值
        *  @return 随机生成unsigned char类型的随机数
        */
        static unsigned char randomByte(unsigned char min, unsigned char max);
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    };
}   //End of namespace SSDK

#endif // RANDOMNUM_HPP
