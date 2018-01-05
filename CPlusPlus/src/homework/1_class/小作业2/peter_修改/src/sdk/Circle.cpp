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
    CATCH_AND_RETHROW_EXCEPTION("Constructor error!");
}

Circle::Circle( double xPos,double yPos,double radius )
{
    try
    {
        this->setXPos(xPos);
        this->setYPos(yPos);
        this->m_radius = radius;
    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor error!");
}

Circle::~Circle()
{
    try
    {

    }
    CATCH_AND_RETHROW_EXCEPTION("Destructor error!");
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// override
double Circle::calArea()
{
    return PI * m_radius * m_radius;
}

bool Circle::contains(Shape* shape)
{
    cout<<"暂不支持该类型!"<<endl;
}

std::string Circle::type()
{
    return VAR_TO_STR(ShapeType::CIRCLE);
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

