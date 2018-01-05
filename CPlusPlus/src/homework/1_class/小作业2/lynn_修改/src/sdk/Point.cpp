#include "Point.hpp"

using namespace SSDK;

Point::Point()
{
    try
    {
    }
    catch(...)
    {
        THROW_EXCEPTION("构造函数出错");
    }
}

Point::Point(double posX, double posY)
{
    try
    {
        this->m_posX = posX;
        this->m_posY = posY;
    }
    catch(...)
    {
        THROW_EXCEPTION("构造函数出错");
    }
}

Point::~Point()
{

}

double Point::calcDistanceTo(Point &point)
{
    return sqrt( (point.posX() - this->posX()) * (point.posX() - this->posX()) +
                (point.posY() - this->posY()) * (point.posY() - this->posY()) );
}
