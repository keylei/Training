#include <iostream>

#include "./app/datagenerator.hpp"

#define BYTE_MAX_VALUE 255
#define BYTE_MIN_VALUE 0

using namespace std;

using namespace App;
using namespace Job;
using namespace SSDK;


int main()
{
    try
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step1
        //实例化一个board对象,并随机生成board中检测对象的数据

        //定义基板x,y原点坐标为10,长和宽均为100(单位:mm,下同)
        double origX = 0, origY = 0, sizeX = 100, sizeY = 100;
        string boardName = "Iphone";

        Board board{origX,origY,sizeX,sizeY,boardName};

        int padCnt = 8;
        int markCnt = 2;
        DataGenerator::generateBoardData(padCnt,markCnt,board);


        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step2
        //计算所有检测对象的总面积

        double totalArea{0.0};

        for (int i = 0; i < (padCnt + markCnt) ; ++i)
        {
            std::cout<< board.pMeasuredObjs()[i]->name() <<"(面积):"<<"\t"
                     << board.pMeasuredObjs()[i]->pShape()->calcArea()<<"\t"
                     <<endl;
            totalArea += board.pMeasuredObjs()[i]->pShape()->calcArea();
        }
        cout << "所有检测对象的总面积:" << "\t" << totalArea << endl;


        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step3
        //判断所有检测对象的顶点是否在board范围内(即检测对象是否在board范围内)
        //如果不在,则将检测对象名称打印到终端上

        std::cout <<"\n" "检测基板外的检测对象如下:"<<endl;

        bool isContained;           //判断检测对象是否被包含在board范围内

        for (int i = 0; i < (padCnt + markCnt); ++i)
        {
            isContained = board.pShape()->contains(board.pMeasuredObjs()[i]->pShape());

            if(!isContained)
            {
                std::cout <<board.pMeasuredObjs()[i]->name() <<"\t"
                          <<std::endl;
            }
        }
    }
    catch(SSDK::CustomException &ex)
    {
        PRINT_EXCEEPTION();
    }

    return 0;
}
