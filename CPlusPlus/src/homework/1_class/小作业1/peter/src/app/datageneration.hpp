#ifndef DATAGENERATION_HPP
#define DATAGENERATION_HPP

#include <cstdlib>

#include "../job/inspectiondata.hpp"
#include "../sdk/formatconvertion.hpp"
#include "../sdk/numrandom.hpp"

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
    class DataGeneration
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //构造 & 析构函数
        DataGeneration();

        ~DataGeneration();
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        /*
        *  @brief   generateInspectionData
        *           随机生成检测数据,具体信息如下:
        *               1.检测程式的版本,最后依次编辑时间
        *               2.检测程式对应基板的名称,原点x ,y坐标,及长和宽
        *               3.基板中所有元件的名称,x,y轴坐标,及长,宽,角度
        *  @param   objCnt:检测对象的数量
        *           measuredObjArr:存放measuredObj对象的数组
        *           pInspectionData:存放inspectionData数据的头指针           
        *  @return  N/A
        */
        static void generateInspectionData(int objCnt,
                                    MeasuredObj measuredObjArr[],
                                    InspectionData *pInspectionData);
        static void generateRawImageData(unsigned char rawData[],int imgLength);
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    };
}//End of namespace App

#endif // DATAGENERATION_HPP
