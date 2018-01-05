#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "job/Board.hpp"
#include "sdk/Rectangle.hpp"
#include "sdk/Circle.hpp"
#include "app/DataGenerator.hpp"
#include "sdk/NumRandom.hpp"

using namespace std;

using namespace Job;
using namespace App;

int main()
{
    try
    {
        //>>>-------------------------------------------------------------------
        // 1.声明检测对象数量,board对象
        int measuredObjCnt {10};
        Board board;

        //>>>-------------------------------------------------------------------
        // 2.随机生成检测对3象数据,并存入board中
        DataGenerator::generateObjData(measuredObjCnt,board);

        //>>>-------------------------------------------------------------------
        // 3.统计所有检测对象的面积,并判断当前对象是否在board中
        double areas {0};
        Rectangle* rect = dynamic_cast<Rectangle*>(board.shape());
        for( int i = 0; i < board.pMeasuredObjs().size(); ++i )
        {
            if(rect->contains(board.pMeasuredObjs()[i]->shape()))
            {
                // 当前检测对象不在board中时,打印出当前对象名称
                cout<<board.pMeasuredObjs()[i]->name()<<" isn't in the Board!"<<endl;

            }
            // 将对象的面积累加
            areas += board.pMeasuredObjs()[i]->shape()->calArea();
        }
        cout << "\nArea:" <<areas << endl; // 打印所有对象的面积和

        return 0;
    }
    CATCH_AND_PRINT_EXCEPTION();
}
