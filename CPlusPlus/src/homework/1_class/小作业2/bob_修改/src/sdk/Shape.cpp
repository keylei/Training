#include "Shape.hpp"


SSDK::Shape::Shape()
{

}

SSDK::Shape::Shape(double xPos, double yPos)
{
    try
    {
        this->m_point.setXPos(xPos);
        this->m_point.setYPos(yPos);
    }
    catch(...)
    {
        THROW_EXCEPTION("Shape构造函数错误!");
    }
}

SSDK::Shape::~Shape()
{

}
