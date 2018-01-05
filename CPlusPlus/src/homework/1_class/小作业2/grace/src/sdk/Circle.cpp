#include "Circle.hpp"


using namespace std;

using namespace SSDK;


Circle::Circle()
{

}

Circle::Circle(double radius, double centerX, double centerY)//rime 构造函数和析钩函数都需要异常保护的，别忘了
{
    this->m_radius = radius;
    this->m_pt.setXPos(centerX);//rime 在类内部直接对成员变量赋值就可以，为什么还要调用访问函数，多一层跳转
    this->m_pt.setYPos(centerY);
}

Circle::~Circle()
{

}

double Circle::calcArea() const
{
    return M_PI * this->m_radius * this->m_radius;
}

bool Circle::isContained(double xLeft,
                         double xRight,
                         double yTop,
                         double yBottom) const
{
    //rime 直接用成员变量，不需要在通过调用函数再走一道
    if(xLeft < (getXPos() - this->m_radius) &&
       xRight > (getXPos() + this->m_radius) &&
       yTop < (getYPos() - this->m_radius) &&
       yBottom > (getYPos() + this->m_radius))
    {
        return true;
    }
    return false;
}
