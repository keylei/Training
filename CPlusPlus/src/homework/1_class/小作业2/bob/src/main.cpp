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

        Board board;
        int objCnt = 10;

        DataGenerator::generateBoardData(objCnt,board);
        //rime 不同模块可以多空一行，以示区别
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step2
        //计算所有检测对象的总面积

        double totalArea{0.0};

        for (int i = 0; i < objCnt; ++i)
        {
            std::cout<< board.pMeasuredObj()[i]->name() <<"(面积):"<<"\t"
                     << board.pMeasuredObj()[i]->pShape()->calcArea()<<"\t"
                     <<endl;
            totalArea += board.pMeasuredObj()[i]->pShape()->calcArea();
        }
        cout << "所有检测对象的总面积:" << "\t" << totalArea << endl;

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step3
        //判断所有检测对象是否在board范围内,如果不在,则将检测对象名称打印到终端上

        std::cout <<"\n" "检测基板外的检测对象如下:"<<endl;


        bool isContailed;//rime 单词拼错了
        for (int i = 0; i < objCnt; ++i)
        {
            isContailed =  board.pMeasuredObj()[i]->pShape()->isContained(
                                         board.originalPoint().xPos(),
                                         board.originalPoint().yPos(),
                                         board.sizeX(),
                                         board.sizeY());
            if(!isContailed)
            {
                std::cout <<board.pMeasuredObj()[i]->name() <<std::endl;
            }
        }
    }
    catch(SSDK::CustomException &ex)
    {
        PRINT_EXCEEPTION();
    }

    return 0;
}
