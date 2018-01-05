#include <iomanip>
#include "app/Jobgenerator.hpp"

using namespace std;

using namespace App;
using namespace Job;
using namespace SSDK;

int main()
{
    try
    {
        int fiducialMarkCnt = 2;  // 基准点数量
        int padCnt = 8;  // 焊盘数量
        int measuredObjCnt = fiducialMarkCnt + padCnt;   // 被测对象总数量
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1 生成指定数量的FiducialMark和Pad对象,形状为矩形或圆形，并求出所有对象的总面积
        Board board;
        JobGenerator::generateJob(board, fiducialMarkCnt, measuredObjCnt);
        double sumArea = 0;   // 生成的所有被测对象的总面积
        cout << "生成的被测对象如下：" << endl;
        for (int i = 0; i < measuredObjCnt; ++i)
        {
            // 打印出生成的被测对象名称及其面积
            cout << fixed << setprecision(2)    // 精确到小数点后两位
                 << board.pMeasuredObjs().at(i)->name() << "\t"
                 << "Area: " << board.pMeasuredObjs().at(i)->pShape()->calcArea()
                 << endl;
            // 计算被测对象的总面积
            sumArea += board.pMeasuredObjs().at(i)->pShape()->calcArea();
        }
        cout << "所有被测对象的总面积为：" << sumArea << endl;

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2 打印出所有在板子之外的FiducialMark和Pad对象
        cout << "\n板子之外的被测对象有：" << endl;
        for (int i = 0; i < measuredObjCnt; ++i)
        {
            // 如果被测对象不在Board板子里面，打印出对象名
            if(!board.pMeasuredObjs().at(i)->pShape()->isContained(board.pShape()))
            {
                cout << board.pMeasuredObjs().at(i)->name() << endl;
            }

        }
    }
    catch(const CustomException& ex )
    {
        cout << ex.what() << endl;
    }

    return 0;
}
