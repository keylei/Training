#include "Rectangle.hpp"


SSDK::Rectangle::Rectangle(double xPos,
                           double yPos,
                           double width,
                           double height,
                           double angle) : Shape(xPos,yPos)
{
    try
    {
        this->m_width = width;
        this->m_height = height;
        this->m_angle = angle;
    }
    catch(...)
    {
        THROW_EXCEPTION("Rectangle构造函数错误!");
    }
}


SSDK::Rectangle::~Rectangle()
{

}

double SSDK::Rectangle::calcArea()
{
    try
    {
        return (this->m_width * this->m_height);
    }
    catch(...)
    {
        THROW_EXCEPTION("矩形框计算面积错误!");
    }
}

bool SSDK::Rectangle::isContained(double originX, double originY, double sizeX, double sizeY)
{
    try
    {
        if(this->point().xPos() - this->m_width/2 - originX < 0 ||
           this->point().xPos() + this->m_width/2 - sizeX -originX > 0 ||
           this->point().yPos() - this->m_height/2 - originY < 0 ||
           this->point().yPos() + this->m_height/2 - sizeY - originY > 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    catch(...)
    {
        THROW_EXCEPTION("判断矩形是否在区域内错误!");
    }

}
