#include "Board.hpp"

using namespace Job;
using namespace SSDK;

Board::Board()
{

}

Board::~Board()
{
}

bool Board::canContainObj(MeasuredObject *pObject)
{
    Rectangle rectangle(this->originX() + this->sizeX()/2,
                        this->originY() + this->sizeY()/2,
                        this->sizeX(),this->sizeY(),0);   //生成符合board尺寸的矩形

    //判断所有临界点是否有不在基板矩形范围之内的
    for(unsigned int i = 0;i < pObject->pBody()->limitPoints().size();++i)
    {
        if(false == rectangle.canContain(pObject->pBody()->limitPoints()[i]))
        {
            return false;
        }
    }

    return true;
}
