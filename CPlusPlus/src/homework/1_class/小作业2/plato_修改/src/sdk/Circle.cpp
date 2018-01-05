#include "Circle.hpp"

using namespace SSDK;

Circle::Circle()
{
    this->m_shapeType = ShapeType::CIRCLE;
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

bool Circle::isContained(Shape *pShape)
{
    if (ShapeType::RECTANGLE != pShape->shapeType())
    {
        THROW_EXCEPTION("此版本暂不支持除矩形外其他形状的判断！")
    }
    // 基板坐标最大值
    double maxBoardPosX = pShape->centerX() + dynamic_cast<Rectangle *>(pShape)->width() / 2;
    double minBoardPosX = pShape->centerX() - dynamic_cast<Rectangle *>(pShape)->width() / 2;
    double maxBoardPosY = pShape->centerY() + dynamic_cast<Rectangle *>(pShape)->height() / 2;
    double minBoardPosY = pShape->centerY() - dynamic_cast<Rectangle *>(pShape)->height() / 2;

    // 判断圆形的外切正方形的一条对角线上的两点的坐标是否在基板坐标范围之内
    if (maxBoardPosX >= centerX() + radius() &&
        minBoardPosX <= centerX() - radius() &&
        maxBoardPosY >= centerY() + radius() &&
        minBoardPosY <= centerY() - radius())
    {
        return true;
    }
    else
    {
        return false;
    }
}


