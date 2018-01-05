#include "Point.hpp"

using namespace SSDK;

Point::Point()
{

}

Point::Point(double posX, double posY)
{
    this->m_posX = posX;
    this->m_posY = posY;
}

Point::~Point()
{

}

double Point::calcDistanceTo(Point &point)
{
    return sqrt( (point.posX() - this->posX()) * (point.posX() - this->posX()) +
                (point.posY() - this->posY()) * (point.posY() - this->posY()) );
}
