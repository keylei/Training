#include "Board.hpp"

using namespace Job;

using namespace std;

Board::Board()
{

}

Board::~Board()
{
    for (vector<MeasuredObj *>::iterator tmp = this->m_pObj.begin();
         tmp != this->m_pObj.end();
         tmp ++) //遍历动态数组
    {
        if (nullptr != *tmp) //删除动态数组元素
        {
            delete *tmp;
            *tmp = nullptr;
        }
    }
    this->m_pObj.clear();
}
