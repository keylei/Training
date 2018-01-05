#include <iostream>
#include <vector>


#include "./job/Board.hpp"
#include "./app/DataGenerator.hpp"


using namespace std;

using namespace Job;
using namespace App;

int main()
{
    try
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step1 生成board数据

        Board board;
        int padCnt{8};
        int fiducialMarkCnt{2};
        DataGenerator::generateBoard(board,fiducialMarkCnt,padCnt);

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step2 计算总面积 & 判断测量目标是否包含在基板里

        bool isContained; //判断是否包含在基板中，true表示包含，false表示不包含
        double allMeasuredObjArea = 0.0; //所有测量对象的面积

        for (unsigned int i = 0; i < board.pMeasuredObjs().size(); ++i) //遍历测量对象
        {
            //计算总面积
            allMeasuredObjArea += board.pMeasuredObjs()[i]->pBody()->calcArea();
            //判断是否在基板中
            isContained = board.pShape()->contains(board.pMeasuredObjs()[i]->pBody());

            if(!isContained) //不包含在基板中
            {
                cout << board.pMeasuredObjs()[i]->name()<< endl;
            }
        }
        cout << "\n" << "以上是在基板外的测量目标" << "\n" << "如果没有表示都在板子内部" << endl;
        cout << "\n" << "所有测量对象的面积：" << allMeasuredObjArea << endl;
    }
    catch(const CustomException& ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
}
