#include "Circle.hpp"

using namespace SSDK;

Circle::Circle()
{

}

Circle::Circle(double radius, double posX, double posY)
{
    this->m_radius = radius;
    this->m_centerPoint.setPosX(posX);
    this->m_centerPoint.setPosY(posY);
}

Circle::~Circle()
{

}

double Circle::calcArea()
{
    double pi = 3.14; //π的近似值
    return pi * this->m_radius * this->m_radius;
}

bool Circle::canContain(Point &point)
{
    if(this->centerPoint().calcDistanceTo(point) < this->m_radius)
    {
        return true;
    }

    return false;
}

void Circle::findLimitPoints()
{
    if(this->m_radius <= 0 || this->m_limitPoints.size() != 0)
    {
        return;
    }

    this->m_limitPoints.push_back(
                Point(this->centerPoint().posX() + this->m_radius,
                      this->centerPoint().posY()));

    this->m_limitPoints.push_back(
                Point(this->centerPoint().posX() - this->m_radius,
                      this->centerPoint().posY()));

    this->m_limitPoints.push_back(
                Point(this->centerPoint().posX(),
                      this->centerPoint().posY() + this->m_radius));

    this->m_limitPoints.push_back(
                Point(this->centerPoint().posX(),
                      this->centerPoint().posY() - this->m_radius));

}
