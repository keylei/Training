#include "circle.hpp"

Circle::Circle()
{

}

Circle::Circle(double radius)
{
    this->m_radius = radius;
}

void Circle::calcArea()
{
    m_area = 3.14 * m_radius * m_radius;
}

