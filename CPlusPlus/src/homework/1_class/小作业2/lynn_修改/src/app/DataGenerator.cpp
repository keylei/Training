#include "DataGenerator.hpp"

using namespace std;
using namespace App;
using namespace Job;
using namespace SSDK;


DataGenerator::DataGenerator()
{
    try
    {

    }
    catch(...)
    {
        THROW_EXCEPTION("构造函数出错");
    }
}

DataGenerator::~DataGenerator()
{

}

void DataGenerator::generateByteData(int length, unsigned char *&pData)
{
    for (int i = 0; i < length; ++i)
    {
        pData[i] = RANDOM_UNSIGNED_CHAR;
    }
}

void DataGenerator::generateBoardData(Board &board, int padCnt, int fiducialMarkCnt)
{
    try
    {
        srand((unsigned)time(NULL));    //初始化随机数

        std::string boardName = "iphone";

        //定义基板x,y原点坐标为0,长、宽均为100(单位:mm,下同)
        double boardOriginX = 0,boardOriginY = 0,
               boardSizeX = 100,boardSizeY = 100;

        //圆形pad或者fiducimalMark的最大、最小半径
        double objectMinRadius = 0.5,objectMaxRadius = 10;

        //矩形检测对象的尺寸最大值为10,最小值为0.5
        double maxSize = 10 , minSize = 0.5;

        //检测对象的最大位置坐标和最小位置坐标
        double minPos = 0, maxPos = 100;

        //检测对象的角度最大值与最小值
        double maxAngle = 360,minAngle = 0;

        string objectName;              //要生成的检测对象的名称
        int shapeTypeCnt = 2;           //检测对象可能有的形状种类数量
        Shape* pBody{nullptr};          //指向要生成的检测对象的形状信息

        //设置基板的信息：
        board.setName(boardName);
        board.setOriginX(boardOriginX);
        board.setOriginY(boardOriginY);
        board.setSizeX(boardSizeX);
        board.setSizeY(boardSizeY);

        for(int i = 0; i < padCnt + fiducialMarkCnt; i++)
        {
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //1.生成检测对象的形状及尺寸

            switch ( (SSDK::ShapeType)(rand()%shapeTypeCnt) )  //随机生成形状
            {
            case SSDK::ShapeType::CIRCLE:      //形状为圆形，生成随机尺寸的圆形
                pBody = new SSDK::Circle
                        (NumRandom::randomDouble(objectMaxRadius,objectMinRadius),
                         NumRandom::randomDouble(maxPos,minPos),
                         NumRandom::randomDouble(maxPos,minPos));


                break;

            case SSDK::ShapeType::RECTANGLE:   //形状为矩形，生成随机尺寸的矩形
                pBody = new Rectangle(
                            NumRandom::randomDouble(maxPos,minPos),
                            NumRandom::randomDouble(maxPos,minPos),
                            NumRandom::randomDouble(maxSize,minSize),
                            NumRandom::randomDouble(maxSize,minSize),
                            0);

                if(nullptr == pBody)
                {
                    THROW_EXCEPTION("new函数开辟空间出错");
                }

                break;

            default:
                THROW_EXCEPTION("传入不支持的形状类型");
                break;
            }   //end of switch (shape)

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //2.生成并设置设置检测对象名称

            if( i < padCnt)
            {
                //向board加入检测对象
                board.pMeasuredObjects().push_back( new Pad( pBody ) );

                objectName = "pad" + FormatConvertion::intToString(i+1);
            }
            else
            {
                //向board加入检测对象
                board.pMeasuredObjects().push_back( new FiducialMark( pBody ) );

                objectName = "fiducialMark"
                        + FormatConvertion::intToString( i + 1 - padCnt);
            }

            if( nullptr == board.pMeasuredObjects().back() )
            {
                THROW_EXCEPTION("new函数开辟空间出错");
            }

            board.pMeasuredObjects().back()->name() = objectName;

        }   //end of for(int i = 0; i < padCnt + fiducialMarkCnt; i++)
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("生成board数据出错");
}
