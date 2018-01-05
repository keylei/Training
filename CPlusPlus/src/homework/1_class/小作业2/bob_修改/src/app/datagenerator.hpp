#ifndef DATAGENERATION_HPP
#define DATAGENERATION_HPP

#include <time.h>

#include "../job/inspectiondata.hpp"
#include "../sdk/formatconvertor.hpp"
#include "../sdk/numrandom.hpp"
#include "../job/FiducialMark.hpp"
#include "../job/Pad.hpp"
#include "../sdk/Circle.hpp"
#include "../sdk/Rectangle.hpp"


namespace App
{
    /**
     *  @brief  DataGenerator
     *          数据生成器,例如生成一笔检测程式数据
     *  @author bob
     *  @version 1.00 2017-11-30 bob
     *                note:create it
     */
    class DataGenerator
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief  构造函数
        *  @param  N/A
        *  @return N/A
        */
        DataGenerator();

        /**
        *  @brief  析构函数
        *  @param  N/A
        *  @return N/A
        */
        ~DataGenerator();
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //member functions

        /*
        *  @brief   generateBoardData
        *           随机生成检测数据,具体信息如下:
        *               1.Board的原点坐标,长,宽
        *               2.生成2个mark点和8个pad,形状随机生成
        *                 2.1如果生成的是矩形,则生成元件名称,中心点坐标,及长,宽,角度
        *                 2.2如果生成的是圆形,则生成元件名称,中心点坐标,及半径
        *  @param   padCnt:board中pad的数量
        *           markCnt:board中mark点的数量
        *           board:生成board的数据
        *  @return  N/A
        */
        static void generateBoardData(int padCnt,int markCnt,Job::Board &board);

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    };
}//End of namespace App

#endif // DATAGENERATION_HPP
