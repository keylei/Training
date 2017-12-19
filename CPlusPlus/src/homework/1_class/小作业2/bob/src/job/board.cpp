#include "board.hpp"

using namespace std;

using namespace Job;
using namespace SSDK;

Board::Board()
{

}

Board::Board(double originX,
             double originY,
             double sizeX,
             double sizeY,
             std::string name)
{
    this->m_originalPoint.setXPos(originX);
    this->m_originalPoint.setYPos(originY);
    this->m_sizeX = sizeX;
    this->m_sizeY = sizeY;
    this->m_name = name;
}


Board::~Board()
{
    //定义一个临时变量,默认指向动态数组中起始点的位置
    //依次找出动态数组中每个元素,并将其销毁
    for (vector<MeasuredObj *>::iterator tmp = this->m_pMeasuredObj.begin();
         tmp != this->m_pMeasuredObj.end(); tmp ++)
    {
        if (nullptr != *tmp)
        {
            delete *tmp;
            *tmp = nullptr;
        }
    }
    this->m_pMeasuredObj.clear();       //清空动态数组中所有元素的值
}
