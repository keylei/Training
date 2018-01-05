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

void DataGenerator::generateBoard(Board &board, int fiducialMarkCnt, int padCnt)
{
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //step1 定义测量对象的形状、名字等信息

    int shapeType = 2; //测量对象的形状个数
    Shape *pBody{nullptr}; //测量对象的形状
    string measuredObjName;//测量对象的名字

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //step2 定义随机生成基板数据的范围

    //rime step2这一片的命名做的很不好，之前讲过bob/peter，全部都白讲了

    //定义基板x,y原点坐标为10,长和宽均为100(单位:mm,下同)
    double originX = 0, originY = 0, sizeX = 100, sizeY = 100;//rime 上面的注释明明是10，下面怎么又是0了呢
    //生成board数据(原点x,y坐标,基板的长和宽)
    board.pt().setXPos(originX);//rime 到底是XPos还是originX
    board.pt().setYPos(originY);
    board.setSizeX(sizeX);
    board.setSizeY(sizeY);
    //检测对象的尺寸最大值与最小值
    //rime 上面的sizeX带有X/Y后缀，这里为什么又没有X，Y了，另外同样是大小，如果不说清楚哪些是board
    //         哪些是Obj的，谁能够看明白
    double maxSize = 10 , minSize = 0.5;
    //板子边缘距离(板边距离检测对象的距离)
    double boardMargin = 3;
    //计算出检测对象坐标的最大值与最小值
    double maxPos = sizeX - maxSize -boardMargin;
    double minPos = minSize + boardMargin;
    //检测对象的角度最大值与最小值
    double maxAngle = 360, minAngle = 0;
    //检测对象半径最大值与最小值
    double minRadius = 0.5, maxRadius = 5;

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //step3 确定形状和名字
    try
    {
        srand((unsigned)time(NULL));
        for (int i = 0; i < fiducialMarkCnt + padCnt; ++i)
        {
            //step3.1 随机生成测量对象的形状
            switch ((ShapeType)(rand()%shapeType))
            {
            case ShapeType::CIRCLE:
                pBody = new Circle(NumRandom::randomDouble(maxRadius,minRadius),
                                   NumRandom::randomDouble(maxPos,minPos),
                                   NumRandom::randomDouble(maxPos,minPos));
                //rime 这个c的malloc不一样，因为new是自己写的，同时new的构造函数中就应该会有异常处理了，
                //         中间层又有rethrow，所以通过判断pBody是否为null是没有意义的
                if(nullptr == pBody)
                {
                    cout << "pBody开辟内存失败" << endl;
                }
                break;

            case ShapeType::RECTANGLE:
                pBody = new Rectangle(NumRandom::randomDouble(maxPos,minPos),
                                      NumRandom::randomDouble(maxPos,minPos),
                                      NumRandom::randomDouble(maxSize,minSize),
                                      NumRandom::randomDouble(maxSize,minSize),
                                      NumRandom::randomDouble(maxAngle,minAngle));
                if(nullptr == pBody)
                {
                    cout << "pBody开辟内存失败" << endl;
                }
                break;

            default:
                //rime: default中的情况明显是告诉了当前case不被支持，说明出现了在CIRCLE/RECTANGLE
                //          之外的枚举类型，“switch 不符合要求!” 是没有任何意义的
                THROW_EXCEPTION("switch 不符合要求!");
                break;

            }

            //step3.2 生成测量元件的名字
            if(i < fiducialMarkCnt)
            {
                measuredObjName = "fiducialMark" + FormatConvertor::intToString(i);
            }
            else
            {
                measuredObjName = "pad" + FormatConvertor::intToString(i-fiducialMarkCnt);
            }

            //step3.3 把数据存入到动态数组中
            board.pObj().push_back( new MeasuredObj(pBody,measuredObjName) );
        }
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("生成数据有误！");
}

