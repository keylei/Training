#include "Rectangle.hpp"

using namespace SSDK;

Rectangle::Rectangle()
{
    this->m_shapeType = ShapeType::RECTANGLE;
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

bool Rectangle::isContained(Shape *pShape)
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

    // 判断矩形的一条对角线上的两点的坐标是否在基板坐标范围之内
    if (maxBoardPosX >= centerX() + width() / 2 &&
        minBoardPosX <= centerX() - width() / 2 &&
        maxBoardPosY >= centerY() + height() / 2 &&
        minBoardPosY <= centerY() - height() / 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
