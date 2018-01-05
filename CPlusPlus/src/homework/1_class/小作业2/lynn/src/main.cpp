#include <iostream>

#include "./job/Pad.hpp"
#include "./job/Board.hpp"
#include "./app/DataGenerator.hpp"

//#include "app/config.hpp"
//#include "job/ImageSlot.hpp"
//#include "job/Image.hpp"

using namespace std;
using namespace App;
using namespace Job;

int main()
{
    Board board;

    try
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1.生成board和board上的所有检测对象及数据

        int padCnt{8};              //board上pad的数量
        int fiducialMarkCnt{2};     //board上FiducialMark的数量

        //调用生成基板数据函数生成基板数据及基板上的所有检测对象
        DataGenerator::generateBoardData(board,padCnt,fiducialMarkCnt);
        //rime 不同的step之间多空一行以示区别
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.计算并显示所有元件的总面积

        double measuredObjetsArea = 0;      //所有检测对象的总面积

        for(unsigned int i = 0;i < board.pMeasuredObjects().size();++i)
        {
            measuredObjetsArea += board.pMeasuredObjects()[i]->pBody()->calcArea();
        }
        cout << "所有元件的总面积:" << measuredObjetsArea << endl;

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //3.找出所有不在基板范围内的检测对象

        for(unsigned int i = 0;i < board.pMeasuredObjects().size();++i)
        {
            //rime Limit一般表示阈值，设定值，如果表示边界的话使用boundary/bounding比较好
            board.pMeasuredObjects()[i]->pBody()->findLimitPoints();

            //rime canContainObj还是使用contains比较好，另外如果后面函数的()内就是加的对象，
            //         obj就不需要再加上去了
            if(false == board.canContainObj(board.pMeasuredObjects()[i]))
            {
                cout << "元件" << board.pMeasuredObjects()[i]->name() << "出界" << endl;
            }
        }

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //4.回收存放board中用来存放检测对象及其形状信息的空间

        while(board.pMeasuredObjects().size() != 0)
        {
            //rime 这里对象的释放操作放在Board的析钩函数中会更好，当然前提是这些对象只会
            //        存在与Board之中

            //回收检测对象中存放形状信息的空间
            if (nullptr != board.pMeasuredObjects().back()->pBody())
            {
                delete board.pMeasuredObjects().back()->pBody();
                board.pMeasuredObjects().back()->pBody() = nullptr;
            }

            //回收存放board中用来存放检测对象的空间
            if( nullptr != board.pMeasuredObjects().back() )
            {
                delete board.pMeasuredObjects().back();
                board.pMeasuredObjects().back() = nullptr;
            }

            board.pMeasuredObjects().pop_back();
        }
    }
    catch(...)  //若捕获到异常，释放堆上的内存空间并显示异常信息
    {
        while(board.pMeasuredObjects().size() != 0)
        {
            if (nullptr != board.pMeasuredObjects().back()->pBody())
            {
                delete board.pMeasuredObjects().back()->pBody();
                board.pMeasuredObjects().back()->pBody() = nullptr;
            }

            if( nullptr != board.pMeasuredObjects().back() )
            {
                delete board.pMeasuredObjects().back();
                board.pMeasuredObjects().back() = nullptr;
            }

            board.pMeasuredObjects().pop_back();
        }

        throw;  //将捕获到的异常继续上抛以显示到终端
    }
}
