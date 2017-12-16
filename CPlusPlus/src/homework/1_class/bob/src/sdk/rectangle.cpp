#include "rectangle.hpp"

SSDK::Rectangle::Rectangle()
{

}

SSDK::Rectangle::Rectangle(double xPos,
                     double yPos,
                     double width,
                     double height,
                     double angle)
{
    this->m_xPos = xPos;
    this->m_yPos = yPos;
    this->m_width = width;
    this->m_height = height;
    this->m_angle = angle;          //2017.12.02 bob 添加成员变量rectangle的角度
}


SSDK::Rectangle::~Rectangle()
{

}
