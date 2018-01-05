#ifndef RANDOMNUM_HPP
#define RANDOMNUM_HPP

#include <cstdlib>
#include <random>
#include <ctime>
#include <functional>

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
        //构造 & 析构函数
        NumRandom();

        ~NumRandom();
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //成员函数
        /*
        *  @brief  randomInt
        *          随机生成区间(min,max)区间的浮点数
        *  @param  max:随机数的最大值
        *          min:随机数的最小值
        *  @return 随机生成的double形浮点数
        */
        static double randomDouble(double min, double max);

        /**
         * @brief generateRandomInt
         *              随机生成指定范围的整数
         * @param min
         * @param max
         * @return
         */
        static int generateRandomInt(int min, int max);

        /**
         * @brief generateRandomReal
         *              随机生成指定范围的实数
         * @param min
         * @param max
         * @return
         */
        static double generateRandomReal(double min, double max);

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    };
}   //End of namespace SSDK

#endif // RANDOMNUM_HPP
