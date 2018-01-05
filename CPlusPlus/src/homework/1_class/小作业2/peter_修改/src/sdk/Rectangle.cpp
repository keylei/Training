#include "Rectangle.hpp"

using namespace SSDK;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// constructor & destructor
Rectangle::Rectangle()
{
    try
    {

    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor error!");
}

Rectangle::Rectangle(double xPos,
                     double yPos,
                     double width,
                     double height)
{
    try
    {
        this->setXPos(xPos);
        this->setYPos(yPos);
        this->m_width = width;
        this->m_height = height;
    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor error!");
}

Rectangle::Rectangle(double xPos,
                     double yPos,
                     double width,
                     double height,
                     double angle)
{
    try
    {
        this->setXPos(xPos);
        this->setYPos(yPos);
        this->m_width = width;
        this->m_height = height;
        this->m_angle = angle;
    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor error!");
}

Rectangle::~Rectangle()
{
    try
    {

    }
    CATCH_AND_RETHROW_EXCEPTION("Destructor error!");
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// override
double Rectangle::calArea()
{
    return m_height * m_width;
}

bool Rectangle::contains(Shape* shape)
{
    if(shape->type() == VAR_TO_STR(ShapeType::RECTANGLE))
    {
        Rectangle* rect = dynamic_cast<Rectangle*>(shape);

        if( this->xPos()-this->width()/2 < rect->xPos()-rect->width()/2 &&
            this->xPos()+this->width()/2 > rect->xPos()+rect->width()/2 &&
            this->yPos()-this->height()/2 < rect->yPos()-rect->height()/2 &&
            this->yPos()+this->height()/2 > rect->yPos()+rect->height()/2 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else if(shape->type() == VAR_TO_STR(ShapeType::CIRCLE))
    {
        Circle* circle = dynamic_cast<Circle*>(shape);

        if( this->xPos()-this->width()/2 < circle->xPos()-circle->radius() &&
            this->xPos()+this->width()/2 > circle->xPos()+circle->radius() &&
            this->yPos()-this->height()/2 < circle->yPos()-circle->radius() &&
            this->yPos()+this->height()/2 > circle->yPos()+circle->radius() )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        cout<<"暂不支持该类型"<<endl;
    }
}

std::string Rectangle::type()
{
    return VAR_TO_STR(ShapeType::RECTANGLE);
}
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

