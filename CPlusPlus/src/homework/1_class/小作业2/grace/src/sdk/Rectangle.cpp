#include "Rectangle.hpp"


using namespace std;

using namespace SSDK;


Rectangle::Rectangle()
{

}

Rectangle::Rectangle(double xPos,
                     double yPos,
                     double width,
                     double height,
                     double angle)
{
    m_pt.setXPos(xPos);
    m_pt.setYPos(yPos);
    this->m_width = width;
    this->m_height = height;
    this->m_angle = angle;
}


Rectangle::~Rectangle()
{

}

double Rectangle::calcArea() const
{
    return this->m_height * this->m_width;
}

bool Rectangle::isContained(double xLeft,
                            double xRight,
                            double yTop,
                            double yBottom) const
{
    if(xLeft < (getXPos() - this->m_width/2) &&
        xRight > (getXPos() + this->m_width/2) &&
        yTop < (getYPos() - this->m_height/2) &&
        yBottom > (getYPos() + this->m_height/2))
    {
        return true;
    }
    else
    {
        return false;
    }
}
