#include "Rectangle.hpp"

using namespace SSDK;

SSDK::Rectangle::Rectangle()
{

}

SSDK::Rectangle::Rectangle(double xPos,
                           double yPos,
                           double width,
                           double height,
                           double angle) : Shape(xPos,yPos)
{
    try
    {
        this->m_width = width;
        this->m_height = height;
        this->m_angle = angle;

        this->setShapeType(ShapeType::RECTANGLE);
    }
    catch(...)
    {
        THROW_EXCEPTION("Rectangle构造函数错误!");
    }
}

SSDK::Rectangle::~Rectangle()
{

}

double SSDK::Rectangle::calcArea()
{
    try
    {
        return (this->m_width * this->m_height);
    }
    catch(...)
    {
        THROW_EXCEPTION("矩形框计算面积错误!");
    }
}

bool SSDK::Rectangle::contains(Shape *pShape)
{
    try
    {
        if(nullptr != pShape)    //判断传入形状是否为nullptr,如果不为nullptr,则继续
        {
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //step1
            //获取形状的类型

            ShapeType shapeType = pShape->shapeType();

            if(shapeType == ShapeType::CIRCLE)
            {
                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //step1.1
                //判断形状是否是圆形,如果为圆形,则形状类型指针强转为Rectangle
                //并判断圆形的边界是否在矩形范围内,如果在则返回true,否则返回false

                Circle * pCircle = dynamic_cast<Circle *>(pShape);

                if (nullptr != pCircle)
                {
                    if((pCircle->point().xPos() - pCircle->radius()) > (this->point().xPos() - (this->m_width / 2)) &&
                       (pCircle->point().xPos() + pCircle->radius()) < (this->point().xPos() + (this->m_width / 2)) &&
                       (pCircle->point().yPos() - pCircle->radius()) > (this->point().yPos() - (this->m_height/ 2)) &&
                       (pCircle->point().yPos() + pCircle->radius()) < (this->point().yPos() + (this->m_height/ 2)))
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
                     THROW_EXCEPTION("将形状类型转换成圆形错误!");
                }
            }
            else if (shapeType == ShapeType::RECTANGLE)
            {
                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //step1.2
                //判断形状是否是矩形,如果为矩形,则形状类型指针强转为Rectangle
                //并判断矩形的边界是否在矩形范围内,如果在则返回true,否则返回false

                Rectangle * pRect = dynamic_cast<Rectangle *>(pShape);

                if(nullptr != pRect)
                {
                    if((pRect->point().xPos() - pRect->width()/2) > (this->point().xPos() - (this->m_width / 2)) &&
                       (pRect->point().xPos() + pRect->width()/2) < (this->point().xPos() + (this->m_width / 2)) &&
                       (pRect->point().yPos() - pRect->height()/2)> (this->point().yPos() - (this->m_height/ 2)) &&
                       (pRect->point().yPos() + pRect->height()/2)< (this->point().yPos() + (this->m_height/ 2)))
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
                    THROW_EXCEPTION("将形状类型转换成矩形错误!");
                }
            }
            else
            {
                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //step1.3
                //如果形状不是圆形,也不是矩形,则抛出异常提示

                THROW_EXCEPTION("矩形框中暂不支持包含此形状");
            }
        }
        else                         //如果传入的对象为nullptr,则抛出异常
        {
            THROW_EXCEPTION("输入对象的形状不存在!");
        }
    }
    catch(...)
    {
        if(nullptr != pShape)
        {
            delete pShape;
            pShape = nullptr;
        }
        THROW_EXCEPTION("矩形框中包含形状错误");
    }
}

