#include "DataGenerator.hpp"

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

        //rime 为什么你们几个人的命名都一样，是相互抄了还是怎么的，抄也要改改啊
        //         命名知道不好的东西有啥好抄的

        //定义基板x,y原点坐标为10,长和宽均为100(单位:mm,下同)
        double originX = 0, originY = 0, sizeX = 100, sizeY = 100;

        //圆形pad或者fiducimalMark的最大、最小半径
        double minRadius = 0.5,maxRadius = 10;

        //矩形检测对象的尺寸最大值为10,最小值为0.5
        double maxSize = 10 , minSize = 0.5;

        //检测对象的最大位置坐标和最小位置坐标
        double minPos = 0, maxPos = 100;

        //检测对象的角度最大值与最小值
        double maxAngle = 360,minAngle = 0;

        string objectName;              //要生成的检测对象的名称
        int shapeTypeCnt = 2;           //检测对象可能有的形状种类数量
        //rime Shape作为抽象类的话，不需要加I，这我已经在《代码规范》中纠正了
        IShape* pBody{nullptr};         //指向要生成的检测对象的形状信息

        //设置基板的信息：
        board.setName("iphone");
        board.setOriginX(originX);
        board.setOriginY(originY);
        board.setSizeX(sizeX);
        board.setSizeY(sizeY);

        for(int i = 0; i < padCnt + fiducialMarkCnt; i++)
        {
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //1.生成检测对象的形状及尺寸

            switch ( (SSDK::ShapeType)(rand()%shapeTypeCnt) )  //随机生成形状
            {
            case SSDK::ShapeType::CIRCLE:      //形状为圆形，生成随机尺寸的圆形
                pBody = new SSDK::Circle
                        (NumRandom::randomDouble(maxRadius,minRadius),
                         NumRandom::randomDouble(maxPos,minPos),
                         NumRandom::randomDouble(maxPos,minPos));

                //rime 这个c的malloc不一样，因为new是自己写的，同时new的构造函数中就应该会有异常处理了，
                //         中间层又有rethrow，所以通过判断pBody是否为null是没有意义的
                if(nullptr == pBody)
                {
                    THROW_EXCEPTION("new函数开辟空间出错");
                }

                //rime ShapeType类型应该在Circle的构造函数中就设定了，而且不能让外面修改
                pBody->setShapeType(ShapeType::CIRCLE);

                break;

            case SSDK::ShapeType::RECTANGLE:   //形状为矩形，生成随机尺寸的矩形
                pBody = new Rectangle(
                            NumRandom::randomDouble(maxPos,minPos),
                            NumRandom::randomDouble(maxPos,minPos),
                            NumRandom::randomDouble(maxSize,minSize),
                            NumRandom::randomDouble(maxSize,minSize),
                            NumRandom::randomDouble(maxAngle,minAngle));

                if(nullptr == pBody)
                {
                    THROW_EXCEPTION("new函数开辟空间出错");
                }

                pBody->setShapeType(ShapeType::RECTANGLE);

                break;

            default:
                //rime: default中的情况明显是告诉了当前case不被支持，说明出现了在CIRCLE/RECTANGLE
                //          之外的枚举类型，“传入参数错误!” 太笼统
                THROW_EXCEPTION("传入参数错误");
                break;
            }   //end of switch (shape)

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //2.向board加入检测对象

            board.pMeasuredObjects().push_back( new Pad( pBody ) );

            if( nullptr == board.pMeasuredObjects().back() )
            {
                THROW_EXCEPTION("new函数开辟空间出错");
            }

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //3.生成并设置设置检测对象名称

            if( i < padCnt)
            {
                objectName = "pad" + FormatConvertion::intToString(i+1);
            }
            else
            {
                objectName = "fiducialMark"
                        + FormatConvertion::intToString( i + 1 - padCnt);
            }

            board.pMeasuredObjects().back()->name() = objectName;

        }   //end of for(int i = 0; i < padCnt + fiducialMarkCnt; i++)
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("生成board数据出错");
}
