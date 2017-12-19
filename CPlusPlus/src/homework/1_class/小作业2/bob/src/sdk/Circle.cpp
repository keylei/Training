#include "Circle.hpp"

using namespace SSDK;


SSDK::Circle::Circle(double xPos, double yPos, double radius):Shape(xPos,yPos)
{
    try
    {
        this->m_radius = radius;
    }
    catch(...)
    {
        THROW_EXCEPTION("Circle的构造函数错误!");
    }
}

double SSDK::Circle::calcArea()
{
    try
    {
        return (3.14 * this->m_radius * this->m_radius);
    }
    catch(...)
    {
        THROW_EXCEPTION("圆形框计算面积错误!");
    }
}

bool Circle::isContained(double originX, double originY, double sizeX, double sizeY)
{
    try
    {
        if(this->point().xPos() - this->m_radius - originX < 0 ||
           this->point().xPos() + this->m_radius - sizeX -originX > 0 ||
           this->point().yPos() - this->m_radius - originY < 0 ||
           this->point().yPos() + this->m_radius - sizeY - originY > 0)
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
        THROW_EXCEPTION("判断圆形框是否在区域范围内错误!");
    }
}

Circle::~Circle()
{

}
