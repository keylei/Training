#include "Circle.hpp"

using namespace SSDK;

Circle::Circle()
{

}

SSDK::Circle::Circle(double xPos, double yPos, double radius):Shape(xPos,yPos)
{
    try
    {
        this->m_radius = radius;
        this->setShapeType(ShapeType::CIRCLE);
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

bool Circle::contains(Shape *pShape)
{
    THROW_EXCEPTION("暂不支持圆形框内包含任何形状");
}

Circle::~Circle()
{

}
