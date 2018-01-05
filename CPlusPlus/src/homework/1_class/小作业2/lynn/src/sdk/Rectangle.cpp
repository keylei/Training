#include "Rectangle.hpp"

SSDK::Rectangle::Rectangle()
{

}

SSDK::Rectangle::Rectangle(double xPos,
                     double yPos,
                     double width,
                     double height,
                     double angle)
{
    this->centerPoint().setPosX(xPos);
    this->centerPoint().setPosY(yPos);
    this->m_width = width;
    this->m_height = height;
    this->m_angle = angle;          //2017.12.02 bob 添加成员变量rectangle的角度
}


SSDK::Rectangle::~Rectangle()
{

}

bool SSDK::Rectangle::canContain(Point &point)
{
    if(point.posX() < this->centerPoint().posX() + this->width()/2 &&
       point.posX() > this->centerPoint().posX() - this->width()/2 &&
       point.posY() < this->centerPoint().posY() + this->height()/2 &&
       point.posY() > this->centerPoint().posY() - this->height()/2)
    {
        return true;
    }
    return false;
}

double SSDK::Rectangle::calcArea()
{
    return this->m_width * this->m_height;
}

void SSDK::Rectangle::findLimitPoints()
{
    if(0 != this->m_angle || this->m_limitPoints.size() != 0)
    {
        return;
    }

    this->m_limitPoints.push_back(
                Point(this->centerPoint().posX()-this->m_width/2,
                      this->centerPoint().posY()-this->m_height));

    this->m_limitPoints.push_back(
                Point(this->centerPoint().posX()+this->m_width/2,
                      this->centerPoint().posY()+this->m_height));

    this->m_limitPoints.push_back(
                Point(this->centerPoint().posX()-this->m_width/2,
                      this->centerPoint().posY()+this->m_height));

    this->m_limitPoints.push_back(
                Point(this->centerPoint().posX()+this->m_width/2,
                      this->centerPoint().posY()-this->m_height));
}
