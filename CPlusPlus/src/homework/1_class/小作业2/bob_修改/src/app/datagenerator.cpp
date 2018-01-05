#include "datagenerator.hpp"

using namespace std;
using namespace App;
using namespace Job;
using namespace SSDK;


DataGenerator::DataGenerator()
{

}

DataGenerator::~DataGenerator()
{

}

void DataGenerator::generateBoardData(int padCnt,int markCnt,Board& board)
{
    try
    {
         srand((unsigned)time(NULL));                    //初始化随机数

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step1
        //生成指定数量的检测对象,其中Mark为2个,Pad 为8个,
        //形状类型随机产生(0代表圆形,1代表矩形),将生成的检测对象添加到board的vector中

        for (int i = 0; i < (padCnt + markCnt); ++i)
        {
            string namePrefix;                  //检测对象的前缀
            string nameIndex;                   //检测对象的索引号
            string name;                        //检测对象的名称

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.1
            //随机生成形状类型的索引号

            unsigned char shapeType = NumRandom::randomByte(
                                         (unsigned char )ShapeType::CIRCLE,
                                         (unsigned char)ShapeType::RECTANGLE);

            MeasuredObj *pMeasuredObj{nullptr};    //检测对象的指针,生成检测对象

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.2
            //生成2个基准点个8个Pad

            if(i < markCnt )
            {
                namePrefix = "mark";                            //元件名的前缀
                nameIndex = FormatConvertion::intToString(i+1); //当前元件的索引号
                name = namePrefix + nameIndex;

                pMeasuredObj = new FiducialMark(name,ShapeType(shapeType));
            }
            else
            {
                namePrefix = "pad";
                nameIndex = FormatConvertion::intToString(i - markCnt + 1);
                name = namePrefix + nameIndex;

                pMeasuredObj = new Pad(name,ShapeType(shapeType));
            }

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.3
            //将新创建的检测对象添加到board的vector中

            board.pMeasuredObjs().push_back(pMeasuredObj);
        }
     }
     CATCH_AND_RETHROW_EXCEPTION("生成board数据错误!");
}


