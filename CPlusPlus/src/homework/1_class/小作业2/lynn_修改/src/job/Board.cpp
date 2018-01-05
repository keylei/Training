#include "Board.hpp"

using namespace Job;
using namespace SSDK;

Board::Board()
{
    try
    {

    }
    catch(...)
    {
        THROW_EXCEPTION("构造函数出错");
    }
}

Board::~Board()
{
}

bool Board::canContains(MeasuredObject *pObject)
{
    Rectangle rectangle(this->originX() + this->sizeX()/2,
                        this->originY() + this->sizeY()/2,
                        this->sizeX(),this->sizeY(),0);   //生成符合board尺寸的矩形

    if(true == rectangle.canContain(pObject->pBody()))
    {
        return true;
    }
    return false;
}
