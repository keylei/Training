#include "Circle.hpp"

using namespace SSDK;

Circle::Circle()
{

}

Circle::Circle(double centerX, double centerY, double radius)
{
    this->m_centerX = centerX;
    this->m_centerY = centerY;
    this->m_radius = radius;
}

Circle::~Circle()
{

}

bool Circle::contains(double originX,
                      double originY,
                      double sizeX,
                      double sizeY)
{
    // 基板坐标最大值
    double maxPosX = originX + sizeX;
    double maxPosY = originY + sizeY;

    // 判断圆形的外切正方形的一条对角线上的两点的坐标是否在基板坐标范围之内
    if (maxPosX >= centerX() + radius() &&
        originX <= centerX() - radius() &&
        maxPosY >= centerY() + radius() &&
        originY <= centerY() - radius())
    {
        return true;
    }
    else
    {
        return false;
    }
}


