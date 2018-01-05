#include "Circle.hpp"


using namespace std;

using namespace SSDK;


Circle::Circle()
{

}

Circle::Circle(double radius, double centerX, double centerY, ShapeType shapeType)
{
    try
    {
        this->m_radius = radius;
        this->m_pt.setXPos(centerX);
        this->m_pt.setYPos(centerY);
        this->m_shapeType = shapeType;
    }
    CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("Circle构造函数发生异常");
}

Circle::~Circle()
{

}

double Circle::calcArea() const
{
    return M_PI * this->m_radius * this->m_radius;
}

bool Circle::contains(Shape *pShape) const
{
    THROW_EXCEPTION("暂不支持判断圆形是否包含其他形状！");
}
