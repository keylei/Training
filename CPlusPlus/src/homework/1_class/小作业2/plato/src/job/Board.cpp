#include "Board.hpp"

using namespace Job;

Board::Board()
{

}


Board::~Board()
{
    // 释放动态数组vector开辟的内存空间
    try
    {
        for(size_t i = 0; i < this->m_pMeasuredObjs.size(); ++i)
        {
           delete this->m_pMeasuredObjs[i];
        }
    }
    catch(...)
    {

    }
}






