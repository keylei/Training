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

void DataGenerator::generateBoardData(int objCnt,
                                      Board& board)
{
    try
    {
         srand((unsigned)time(NULL));                    //初始化随机数

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step1
        //生成基板数据信息

        //定义基板x,y原点坐标为10,长和宽均为100(单位:mm,下同) //rime 这里把单位注明了，值得表扬
        double originalX = 0, originalY = 0, sizeX = 100, sizeY = 100;

        //生成board数据(基板名称,x,y原点坐标,基板的长和宽)
        board.setName("iphone");
        board.originalPoint().setXPos(originalX); //rime 上次说了改成origX，original是原始的意思，这里标示原点，是origin的缩写
        board.originalPoint().setYPos(originalY);
        board.setSizeX(sizeX);
        board.setSizeY(sizeY);

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step2
        //生成指定数量的检测对象,其中Mark为2个,Pad 为8个,
        //形状类型随机产生(0代表圆形,1代表矩形),将生成的检测对象添加到board的vector中

        for (int i = 0; i < objCnt; ++i)
        {
            string namePrefix;                  //检测对象的前缀
            string nameIndex;                   //检测对象的索引号
            string name;                        //检测对象的名称
            //生成形状类型的索引号,索引号"0"代表圆形,1代表矩形
            unsigned char indexMax = 1;
            //rime 形状的索引好，为什么是index，这谁能看出来，应该是定义枚举的
            //rime min的m大写
            unsigned char indexmin = 0;

            //rime 到底多少个Mark，还是多少个Pad不应该在这里定义，应该上上层传递过来，
            //同时也不应该在for循环中定义这些变量
            int markCnt = 2;                    //生成Mark点的个数为2

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.1
            //随机生成形状类型的索引号

            unsigned char shapeIndex = NumRandom::randomByte(indexmin,indexMax);

            MeasuredObj *pMeasuredObj{nullptr};        //检测对象的指针,生成检测对象

            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.2
            //生成2个基准点个8个Pad

            if(i < markCnt )
            {
                namePrefix = "mark";                            //元件名的前缀
                nameIndex = FormatConvertion::intToString(i+1); //当前元件的索引号
                name = namePrefix + nameIndex;

                pMeasuredObj = new FiducialMark(name,ShapeType(shapeIndex));
            }
            else
            {
                namePrefix = "pad";
                nameIndex = FormatConvertion::intToString(i - markCnt + 1);
                name = namePrefix + nameIndex;

                pMeasuredObj = new Pad(name,ShapeType(shapeIndex));
            }
            //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            //step2.3
            //将新创建的检测对象添加到board的vector中

            board.pMeasuredObj().push_back(pMeasuredObj);
        }
     }
     CATCH_AND_RETHROW_EXCEPTION("生成board数据错误!");
}


