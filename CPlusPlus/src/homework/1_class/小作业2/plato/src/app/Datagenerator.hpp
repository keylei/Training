#ifndef DATAGENERATOR_HPP
#define DATAGENERATOR_HPP

#include "job/Board.hpp"
#include "sdk/NumRandom.hpp"

#define OBJ_CNT 10  // 被测对象总数量（这里包含基准点和焊盘）
#define FIDUCIALMARK_CNT 2  // 基准点数量
#define PAD_CNT (OBJ_CNT-FIDUCIALMARK_CNT)  // 焊盘数量

namespace App
{
    /**
     *  @brief  DataGenerator
     *              生成被测对象的数据结构
     *  @author bob
     *  @version 1.00 2017-11-30 bob
     *                note:create it
     *                2017-12-18 plato
     *                note:rewrite it
     */
    class DataGenerator
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //构造 & 析构函数

        DataGenerator();
        virtual ~DataGenerator();

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        /**
         * @brief generateData
         *          生成数据：
         *              1.基板的原点坐标和长宽
         *              2.基准点和焊盘的名称、形状、中心点坐标
         *              3.矩形的长宽、圆形的半径随机生成
         *              4.形状、中心点坐标随机生成
         * @param board
         *          基板对象
         */
        static void generateData(Job::Board& board);
    };
}//End of namespace App

#endif // DATAGENERATOR_HPP
