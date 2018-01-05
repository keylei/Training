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
                     double angle,
                     ShapeType shapeType)//rime 矩形的话就不需要让其传形状了, 万一别人传入的是Circle怎么办
{
    m_pt.setXPos(xPos);
    m_pt.setYPos(yPos);
    this->m_width = width;
    this->m_height = height;
    this->m_angle = angle;
    this->m_shapeType = shapeType;
}


Rectangle::~Rectangle()
{

}

double Rectangle::calcArea() const
{
    return this->m_height * this->m_width;
}

bool Rectangle::contains(Shape *pShape) const
{
    //rime 这里直接用switch...case罗列出来比较好, 这样还是显得乱
    //rime 没有判断指针是否为null
    if(ShapeType::CIRCLE != pShape->shapeType() &&
            ShapeType::RECTANGLE != pShape->shapeType())
    {
        THROW_EXCEPTION("暂不支持判断包含除圆形和矩形之外的其他类型！");
    }
    else if(ShapeType::CIRCLE == pShape->shapeType())
    {
        Circle *circle = dynamic_cast<Circle *>(pShape);
        if((this->m_pt.xPos() - this->m_width/2 < circle->pt().xPos() - circle->radius()) &&
           (this->m_pt.xPos() + this->m_width/2 > circle->pt().xPos() + circle->radius()) &&
           (this->m_pt.yPos() - this->m_height/2 < circle->pt().yPos() - circle->radius()) &&
           (this->m_pt.yPos() + this->m_height/2 > circle->pt().yPos() + circle->radius()))
            return true;
        else
            return false;
    }
    else
    {
        Rectangle *rectangle = dynamic_cast<Rectangle *>(pShape);
        if((this->m_pt.xPos() - this->m_width/2 < rectangle->pt().xPos() - rectangle->width()/2) &&
           (this->m_pt.xPos() + this->m_width/2 > rectangle->pt().xPos() + rectangle->width()/2) &&
           (this->m_pt.yPos() - this->m_height/2 < rectangle->pt().yPos() - rectangle->height()/2) &&
           (this->m_pt.yPos() + this->m_height/2 > rectangle->pt().yPos() + rectangle->height()/2))
            return true;
        else
            return false;
    }
}
