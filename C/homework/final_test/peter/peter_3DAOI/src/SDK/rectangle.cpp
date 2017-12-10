#include "rectangle.hpp"


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & destructor

using namespace SDK;

Rectangle::Rectangle()
{

}

Rectangle::Rectangle( double xPos,
                      double yPos,
                      double width,
                      double height )
{
    this->m_xPos = xPos;
    this->m_yPos = yPos;
    this->m_width = width;
    this->m_height = height;
}

Rectangle::Rectangle( double xPos,
                      double yPos,
                      double angle,
                      double width,
                      double height )
{
    this->m_xPos = xPos;
    this->m_yPos = yPos;
    this->m_angle = angle;
    this->m_width = width;
    this->m_height = height;
}

Rectangle::~Rectangle()
{

}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


