#include "Datagenerator.hpp"

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

void DataGenerator::generateData(Board& board)
{
    try
    {
        // 设置随机种子，用于生成随机数
        srand(time(0));

        // 基板原点坐标、X/Y轴方向长度
        double originX = 0;
        double originY = 0;
        double sizeX = 100;
        double sizeY = 50;
        // 被测对象中心点坐标的范围
        double minCenterX = 0;
        double maxCenterX = 100;
        double minCenterY = 0;
        double maxCenterY = 50;
        // 矩形的长宽范围 //rime 既然上面用了SizeX/SizeY, 这里怎么又换成Width/Height了,请统一
        double minWidth = 1;
        double maxWidth = 10;
        double minHeight = 1;
        double maxHeight = 5;
        // 圆形的半径范围
        double minRadius = 1;
        double maxRadius = 5;

        // 设置基板信息
        board.setOriginX(originX);
        board.setOriginY(originY);
        board.setSizeX(sizeX);
        board.setSizeY(sizeY);

        char objName[10];
        for (int i = 0; i < OBJ_CNT; ++i)
        {
            MeasuredObj *pMeasuredObj = nullptr;
            if (i < FIDUCIALMARK_CNT)
            {
                sprintf(objName, "Mark_%02d", i + 1);
                pMeasuredObj = new FiducialMark();  // 创建基准点对象
            }
            else
            {
                sprintf(objName, "Pad_%02d", (i - FIDUCIALMARK_CNT) + 1);
                pMeasuredObj = new Pad();   // 创建焊盘对象
            }

            // 随机创建矩形或圆形
            Shape* pShape = nullptr;
            if (0 == rand() % 2)
            {
                // 创建矩形对象
                pShape = new Rectangle(NumRandom::generateRandomReal(minCenterX,maxCenterX),
                                       NumRandom::generateRandomReal(minCenterY,maxCenterY),
                                       NumRandom::generateRandomReal(minWidth,maxWidth),
                                       NumRandom::generateRandomReal(minHeight,maxHeight));
            }
            else
            {
                // 创建圆形对象
                pShape = new Circle(NumRandom::generateRandomReal(minCenterX,maxCenterX),
                                    NumRandom::generateRandomReal(minCenterY,maxCenterY),
                                    NumRandom::generateRandomReal(minRadius,maxRadius));
            }
            pMeasuredObj->setPShape(pShape);
            pMeasuredObj->setName(objName);
            board.pMeasuredObjs().push_back(pMeasuredObj);
        }
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("数据生成失败！");
}
