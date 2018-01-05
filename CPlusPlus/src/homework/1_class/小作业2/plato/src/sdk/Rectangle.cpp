#include "Rectangle.hpp"

using namespace SSDK;

Rectangle::Rectangle()
{

}

Rectangle::Rectangle(double centerX, double centerY, double width, double height)
{
    this->m_centerX = centerX;
    this->m_centerY = centerY;
    this->m_width = width;
    this->m_height = height;
}

Rectangle::~Rectangle()
{

}

bool Rectangle::contains(double originX,
                         double originY,
                         double sizeX,
                         double sizeY)
{
    // 基板坐标最大值
    double maxPosX = originX + sizeX;
    double maxPosY = originY + sizeY;

    // 判断矩形的一条对角线上的两点的坐标是否在基板坐标范围之内
    if (maxPosX >= centerX() + width() / 2 &&
        originX <= centerX() - width() / 2 &&
        maxPosY >= centerY() + height() / 2 &&
        originY <= centerY() - height() / 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
