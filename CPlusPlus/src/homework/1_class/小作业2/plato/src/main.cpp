#include <iomanip>
#include "app/Datagenerator.hpp"

using namespace std;

using namespace App;
using namespace Job;
using namespace SSDK;

int main()
{
    try
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1 生成指定数量的FiducialMark和Pad对象,形状为矩形或圆形，并求出所有对象的总面积
        Board board;
        //rime 其实这个叫DataGenerator也不合适,因为Data听上去就是生成的纯数据,叫JobGenerator更贴切写
        DataGenerator::generateData(board); //rime 生成的数据规模应该由外面传入
        //rime 感觉上total一般以可数的数量为主,对于面积这种用sum更好写
        double totalArea = 0;   // 生成的所有被测对象的总面积
        cout << "生成的被测对象如下：" << endl;
        for (int i = 0; i < OBJ_CNT; ++i)
        {
            // 打印出生成的被测对象名称及其面积
            cout << fixed << setprecision(2)    // 精确到小数点后两位
                 << board.pMeasuredObjs().at(i)->name() << "\t"
                 << "Area: " << board.pMeasuredObjs().at(i)->pShape()->calcArea()
                 << endl;
            // 计算被测对象的总面积
            totalArea += board.pMeasuredObjs().at(i)->pShape()->calcArea();
        }
        cout << "所有被测对象的总面积为：" << totalArea << endl;

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2 打印出所有在板子之外的FiducialMark和Pad对象
        cout << "\n板子之外的被测对象有：" << endl;
        for (int i = 0; i < OBJ_CNT; ++i)
        {
            // 如果被测对象不在Board板子里面，打印出对象名
            if(!board.pMeasuredObjs().at(i)->pShape()->contains(board.originX(),
                                                                 board.originY(),
                                                                 board.sizeX(),
                                                                 board.sizeY()))
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
