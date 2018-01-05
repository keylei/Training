#include "Board.hpp"

using namespace Job;

using namespace std;

Board::Board()
{

}

Board::Board(SSDK::Shape *pShape)
{
    this->m_pShape = pShape;
}

Board::~Board()
{
    for (vector<MeasuredObj *>::iterator tmp = this->m_pMeasuredObjs.begin();
         tmp != this->m_pMeasuredObjs.end();
         tmp ++) //遍历动态数组
    {
        if (nullptr != *tmp) //删除动态数组元素
        {
            delete *tmp;
            *tmp = nullptr;
        }
    }
    this->m_pMeasuredObjs.clear();

    if(nullptr != this->m_pShape)
    {
        delete this->m_pShape;
        this->m_pShape = nullptr;
    }
}

