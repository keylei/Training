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
    //step2 定义随机生成基板及其基板上的元件数据的范围

    //step2.1 基板尺寸范围
    //定义基板x,y原点坐标为50,长和宽均为100(单位:mm,下同)
    double boardXPos = 50, boardYPos = 50, boardSizeX = 100, boardSizeY = 100, boardAngle = 0;

    //step2.2 检测元件尺寸范围
    //检测对象的尺寸最大值与最小值
    double objMaxSizeXAndY = 10 , objMinSizeXAndY = 0.5;
    //板子边缘距离(板边距离检测对象的距离)
    double boardMargin = 3;
    //计算出检测对象坐标的最大值与最小值
    double objMaxPosXAndY = boardSizeX - objMaxSizeXAndY - boardMargin;
    double objMinPosXAndY = objMinSizeXAndY + boardMargin;
    //检测对象的角度最大值与最小值
    double objMaxAngle = 360, objMinAngle = 0;
    //检测对象半径最大值与最小值
    double objMinRadius = 0.5, objMaxRadius = 5;

    //step2.3 设置基板数据
    pBody = new Rectangle(boardXPos,
                          boardYPos,
                          boardSizeX,
                          boardSizeY,
                          boardAngle,
                          ShapeType::RECTANGLE);
    board.setPShape(pBody);


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
                pBody = new Circle(NumRandom::randomDouble(objMaxRadius,objMinRadius),
                                   NumRandom::randomDouble(objMaxPosXAndY,objMinPosXAndY),
                                   NumRandom::randomDouble(objMaxPosXAndY,objMinPosXAndY),
                                   ShapeType::CIRCLE);
                break;

            case ShapeType::RECTANGLE:
                pBody = new Rectangle(NumRandom::randomDouble(objMaxPosXAndY,objMinPosXAndY),
                                      NumRandom::randomDouble(objMaxPosXAndY,objMinPosXAndY),
                                      NumRandom::randomDouble(objMaxSizeXAndY,objMinSizeXAndY),
                                      NumRandom::randomDouble(objMaxSizeXAndY,objMinSizeXAndY),
                                      NumRandom::randomDouble(objMaxAngle,objMinAngle),
                                      ShapeType::RECTANGLE);
                break;

            default:
                THROW_EXCEPTION("检测对象形状除了圆和矩形之外的形状不被支持");
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
            board.pMeasuredObjs().push_back( new MeasuredObj(pBody,measuredObjName) );
        }
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("生成数据有误！");
}

