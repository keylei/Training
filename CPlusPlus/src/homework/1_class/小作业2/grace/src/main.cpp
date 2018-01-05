#include <iostream>
#include <vector>


#include "./job/Board.hpp"
#include "./app/DataGenerator.hpp"


using namespace std;

using namespace Job;

int main()
{
    try
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step1 生成board数据

        Job::Board board;
        int padCnt{8};
        int fiducialMarkCnt{2};
        //rime 这里的App也可以像Job一样，在一开始using，后面就不需要再加这个前缀了
        App::DataGenerator::generateBoard(board,fiducialMarkCnt,padCnt);
        //rime 不同的step之间多空一行以示区别
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step2 计算总面积 & 判断测量目标是否包含在基板里

        bool isContained; //判断是否包含在基板中，true表示包含，false表示不包含
        double allMeasuredObjArea = 0.0; //所有测量对象的面积

        //基板的四边极限值
        double boardLeftLimit = board.pt().xPos() - board.sizeX()/2;
        double boardRightLimit = board.pt().xPos() + board.sizeX()/2;
        double boardTopLimit = board.pt().yPos() - board.sizeY()/2;
        double boardBottomLimit = board.pt().yPos() + board.sizeY()/2;

        //rime 这个输出注释是不合理的，不仅仅是测量对象在基板之外，还有计算总面积的功能
        cout << "测量对象基板外：" << endl;
        for (unsigned int i = 0; i < board.pObj().size(); ++i) //遍历测量对象
        {
            //计算总面积
            allMeasuredObjArea += board.pObj()[i]->pBody()->calcArea();
            //判断是否在基板中
            isContained = board.pObj()[i]->pBody()->isContained(boardLeftLimit,
                                                                boardRightLimit,
                                                                boardTopLimit,
                                                                boardBottomLimit);
            if(!isContained) //不包含在基板中
            {
                cout << "  " << board.pObj()[i]->name()<< endl;
            }
        }
        cout << "所有测量对象的面积：" << allMeasuredObjArea << endl;
    }
    //rime 追加的异常不应该就如此粗暴，如果发生异常本来就应该输出出错函数的，而追加
    //         的信息应该是进一步能够描述的，如果不确定，都可以不用追加，追加一个“main.cpp出错！”
    //         没有任何意义
    //rime  main函数中需要处理异常，已经是最上层了，接着throw只会引发程序奔溃
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("main.cpp出错！");

    return 0;
}
