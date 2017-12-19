#include "Rectangle.hpp"

using namespace SSDK;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// constructor & destructor
Rectangle::Rectangle()
{

}

Rectangle::Rectangle(double xPos,
                     double yPos,
                     double width,
                     double height)
{
    this->setXPos(xPos);
    this->setYPos(yPos);
    this->m_width = width;
    this->m_height = height;
}

Rectangle::Rectangle(double xPos,
                     double yPos,
                     double width,
                     double height,
                     double angle)
{
    this->setXPos(xPos);
    this->setYPos(yPos);
    this->m_width = width;
    this->m_height = height;
    this->m_angle = angle;          //2017.12.02 bob 添加成员变量rectangle的角度
}

Rectangle::~Rectangle()
{

}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// override
double Rectangle::calArea()
{
    return m_height * m_width;
}

bool Rectangle::isContains( double xPos,
                            double yPos,
                            double sizeX,
                            double sizeY )
{
    if( this->xPos() - this->width()/2.0  > xPos &&
        this->yPos() - this->height()/2.0 > yPos &&
        this->xPos() + this->width()/2.0  < sizeX   &&
        this->yPos() + this->height()/2.0 < sizeY   )
    {
        return true;
    }
    else
    {
        return false;
    }

}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

