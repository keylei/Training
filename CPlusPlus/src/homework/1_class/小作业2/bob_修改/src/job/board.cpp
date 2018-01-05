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
    try
    {
        double defaultAngle{0.0};
        this->m_name = name;
        this->m_originalPoint.setXPos(originX);
        this->m_originalPoint.setYPos(originY);
        this->m_sizeX = sizeX;
        this->m_sizeY = sizeY;

        this->m_pShape = new Rectangle((originX + sizeX)/2,
                                       (originY + sizeY)/2,
                                        sizeX,
                                        sizeY,
                                        defaultAngle);
    }
    catch(...)
    {
        destoryShape();
        THROW_EXCEPTION("Board构造函数错误!");
    }
}


Board::~Board()
{
    try
    {
        //定义一个临时变量,默认指向动态数组中起始点的位置
        //依次找出动态数组中每个元素,并将其销毁
        for (vector<MeasuredObj *>::iterator tmp = this->m_pMeasuredObjs.begin();
             tmp != this->m_pMeasuredObjs.end(); tmp ++)
        {
            if (nullptr != *tmp)
            {
                delete *tmp;
                *tmp = nullptr;
            }
        }
        this->m_pMeasuredObjs.clear();       //清空动态数组中所有元素的值

        destoryShape();
    }
    catch(...)
    {
        THROW_EXCEPTION("Board析构函数错误!");
    }
}

void Board::createShape()
{
    try
    {
        double defaultAngle{0.0};
        this->m_pShape = new Rectangle(
                    (this->m_originalPoint.xPos() + this->m_sizeX)/2,
                    (this->m_originalPoint.yPos() + this->m_sizeY)/2,
                    this->m_sizeX,
                    this->m_sizeY,
                    defaultAngle);
    }
    catch(...)
    {
        destoryShape();
        THROW_EXCEPTION("基板创建形状失败!");
    }
}

void Board::destoryShape()
{
    try
    {
        if(nullptr != this->m_pShape)
        {
            delete this->m_pShape;
            this->m_pShape = nullptr;
        }
    }
    catch(...)
    {
        THROW_EXCEPTION("销毁基板形状失败!");
    }
}

