#include "Circle.hpp"

using namespace SSDK;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// constructor & destructor
Circle::Circle()
{
    try
    {
        double radius = 0;
        this->m_radius = radius;
    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor Circle error!");
}

Circle::Circle( double xPos,double yPos,double radius )
{
    try
    {
        this->setXPos(xPos);
        this->setYPos(yPos);
        this->m_radius = radius;
    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor Circle error!");
}

Circle::~Circle()
{
    try
    {

    }
    CATCH_AND_RETHROW_EXCEPTION("Destructor Circle error!");
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// override
double Circle::calArea()
{
    return PI * m_radius * m_radius;
}

//rime is能加s作为单数？
bool Circle::isContains( double xPos,
                         double yPos,
                         double sizeX,
                         double sizeY )
{
    if( this->xPos() - this->m_radius > xPos  &&
        this->yPos() - this->m_radius > yPos  &&
        this->xPos() + this->m_radius < sizeX &&
        this->yPos() + this->m_radius < sizeY )
    {
        return true;
    }
    else
    {
        return false;
    }
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

