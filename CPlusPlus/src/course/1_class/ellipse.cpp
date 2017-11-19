#include "ellipse.hpp"

Ellipse::Ellipse(double axis):
    m_longAxis(axis),
    m_shortAxis(axis)
{

}

Ellipse::Ellipse(double longAxis, double shortAxis):
    m_longAxis(longAxis),
    m_shortAxis(shortAxis)
{

}

//可以在子类中访问protect的成员
void Ellipse::calcArea()
{
    this->m_area = 3.14 * this->m_longAxis*this->m_shortAxis;
}
