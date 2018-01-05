#ifndef DATAGENERATION_HPP
#define DATAGENERATION_HPP

#include <time.h>

#include "../job/Pad.hpp"
#include "../job/FiducialMark.hpp"
#include "../job/InspectionData.hpp"
#include "../sdk/FormatConvertion.hpp"
#include "../sdk/NumRandom.hpp"

using namespace std;

using namespace Job;
using namespace SSDK;

namespace App
{
    /**
     *  @brief  DataGeneration
     *          随机生成一笔检测程式的数据
     *  @author bob
     *  @version 1.00 2017-11-30 bob
     *                note:create it
     */
    class DataGenerator
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //构造 & 析构函数

        /**
        *  @brief   默认构造函数
        *  @param   N/A
        *  @return  N/A
        */
        DataGenerator();

        /**
        *  @brief   析构函数
        *  @param   N/A
        *  @return  N/A
        */
        virtual ~DataGenerator();

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        /*
        *  @brief   generateImgData
        *           生成随机的图片数据
        *  @param
        *  @return
        */
        static void generateByteData(int length, unsigned char*& pData);

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        /*
        *  @brief   generateObjectOf
        *           生成board的元件
        *  @param   board:要生成元件的board
        *           padCnt:要生成的pad的数量
        *           fiducialMarkCnt:要生成的fiducialMark的数量
        *  @return  N/A
        */
        static void generateBoardData(Board& board,int padCnt,int fiducialMarkCnt);

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    };
}//End of namespace App

#endif // DATAGENERATION_HPP
