#include "circle.hpp"

Circle::Circle()
{

}

Circle::Circle(double radius)
{
    this->m_radius = radius;
}

int Circle:: ID = 2;
void Circle::calcArea()
{
    m_area = 3.14 * m_radius * m_radius;
}
