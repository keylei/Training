#ifndef JOBGENERATOR_HPP
#define JOBGENERATOR_HPP

#include "job/Board.hpp"
#include "sdk/NumRandom.hpp"

namespace App
{
    /**
     *  @brief  JobGenerator
     *              生成被测对象的数据结构
     *  @author bob
     *  @version 1.00 2017-11-30 bob
     *                note:create it
     *                2017-12-18 plato
     *                note:rewrite it
     */
    class JobGenerator
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //构造 & 析构函数

        JobGenerator();
        virtual ~JobGenerator();

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        /**
         * @brief generateJob
         *          生成程式：
         *              1.基板的原点坐标和长宽
         *              2.基准点和焊盘的名称、形状、中心点坐标
         *              3.矩形的长宽、圆形的半径随机生成
         *              4.形状、中心点坐标随机生成
         * @param board
         *          基板对象
         * @param fiducialMarkCnt
         *          基准点数量
         * @param measuredObjCnt
         *          被测对象总数量
         */
        static void generateJob(Job::Board& board, int fiducialMarkCnt, int measuredObjCnt);
    };
}//End of namespace App

#endif // JOBGENERATOR_HPP
