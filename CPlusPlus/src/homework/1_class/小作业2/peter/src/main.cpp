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

int main()
{
    try
    {
        srand((unsigned)time(NULL));            // 初始化随机数

        //>>>-------------------------------------------------------------------
        // 1.检测对象数量和随机生成基板数据的范围(单位:mm)
        int objCnt = 10;                        // 检测对象个数
        //rime 如果标示板子的尺寸，请在命名上好好写，这样谁能看明白
        double xPos = 0, yPos = 0, size = 100;  // 基板原点坐标及尺寸
        double minSize = 1, maxSize = 10;       // 检测对象的尺寸
        //rime 既然前面分了x和y，这里仅仅是一个Pos，谁能明白
        double minPos = 0,maxPos = size;        // 检测对象的坐标
        double padRatio = 0.8;                  // Pad占的比率
        string name;                            // 检测对象名称

        //>>>-------------------------------------------------------------------//rime这个设置的和大家都一样
        // 2.随机生成检测对象数据,并存入board中
        Board board(xPos,yPos,size,size);       // 声明Board对象
        Shape* pShape = nullptr;
        MeasuredObj* pObj = nullptr;
        for(int i = 0; i < objCnt; ++i)
        {
            //rime 每次都定义一个这四个数浪费效率，完全可以写在外面
            double posX   {NumRandom::randomDouble(minPos,maxPos)};
            double posY   {NumRandom::randomDouble(minPos,maxPos)};
            double width  {NumRandom::randomDouble(minSize,maxSize)};
            double height {NumRandom::randomDouble(minSize,maxSize)};
            if( rand()%2 )  // 随机形状
            {
                pShape = new Rectangle( posX,posY,width,height);
            }
            else
            {
                pShape = new Circle( posX,posY,width);
            }
            //rime 这里不要挤在同一行写
            if(nullptr == pShape){THROW_EXCEPTION("New Rectangle error!");}

            if(i < padRatio*objCnt)  // Pad & FiducialMark 对象
            {
                name = "Pad" + FormatConvertion::intToString(i+1);
                pObj = new Pad(name,pShape);

            }
            else
            {
                name = "FiducialMark" + FormatConvertion::intToString(i+1);
                pObj = new FiducialMark(name,pShape);
            }
            if(nullptr == pObj){THROW_EXCEPTION("New Object error!");}
            board.objs().push_back(pObj);   // 将值存入board中
        }

        //>>>-------------------------------------------------------------------
        // 3.统计所有检测对象的面积,并判断当前对象是否在board中
        double areas {0};
        for( int i = 0; i < board.objs().size(); ++i )
        {
            //rime 该方法不合格，理由bob的作业讲过了
            if( !board.objs()[i]->shape()->isContains(xPos,yPos,size,size) )
            {
                // 当前检测对象不在board中时,打印出当前对象名称
                cout<<board.objs()[i]->name()<<" isn't in the Board!"<<endl;
            }
            areas += board.objs()[i]->shape()->calArea(); // 将对象的面积累加
        }
        cout << "\nArea:" <<areas << endl; // 打印所有对象的面积和

        if(nullptr != pShape)
        {
            delete pShape;
            pShape = nullptr;
        }
        if(nullptr != pShape){THROW_EXCEPTION("Delete pShape error!");}
        if(nullptr != pObj)
        {
            delete pShape; //rime 为什么又delete一次pShape
            pObj = nullptr;
        }
        if(nullptr != pObj){THROW_EXCEPTION("Delete pObj error!");}

        return 0;
    }
    CATCH_AND_PRINT_EXCEPTION();
}
