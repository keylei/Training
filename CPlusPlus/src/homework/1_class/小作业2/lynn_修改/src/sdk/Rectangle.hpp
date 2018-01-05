#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "CustomException.hpp"
#include "IAreaCalculatable.hpp"
#include "Shape.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Point.hpp"

namespace SSDK
{

/**
 *  @brief  表示矩形框，存有矩形框的位置和长宽
 *          具有计算矩形面积的功能
 *  @author lynn
 *  @version 1.00 2017-11-20 lynn
 *                note:create it
 */
class Rectangle:public Shape
{
public:

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    /*
    *  @brief   类的默认构造函数
    *  @param   N/A
    *  @return  N/A
    */
    Rectangle();

    /*
    *  @brief  Rectangle
    *          根据参数,将其赋值给成员变量m_xPos,m_yPos,m_angle,m_width,m_height
    *  @param  xPos: 设置rectangle的x坐标
    *          yPos: 设置rectangle的y坐标
    *          width:设置rectangle的宽度
    *         height:设置rectangle的高度
    *         angle: 设置rectangle的angle角度
    *  @return  N/A
    */
    Rectangle(double xPos,
              double yPos,
              double width,
              double height,
              double angle);

    /*
    *  @brief   析构函数
    *  @param   N/A
    *  @return  N/A
    */
    virtual ~Rectangle();

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //set & get function

    double width() { return this->m_width; }
    void setWidth(double width) { this->m_width = width; }

    double height() { return this->m_height; }
    void setHeight(double height) { this->m_height = height; }

    double angle() { return this->m_angle; }
    void setAngle(double angle) { this->m_angle = angle; }

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //member function

    /*
    *  @brief   判断一个图形是否在矩形内，当前矩形需角度为0
    *           支持判断的图形：
    *           1.角度为0的矩形
    *           ...
    *  @param   pShape :要判断的图形
    *  @return  true:在范围内
    *           false:不在范围内
    */
    virtual bool canContain(Shape *pShape) override;

    /*
    *  @brief   计算矩形的面积
    *  @param   N/A
    *  @return  矩形的面积
    */
    virtual double calcArea() override;

    /*
    *  @brief   找出矩形的临界点（不支持带角度的rectangle）
    *  @param   N/A
    *  @return  N/A
    */
    virtual void findBoundaryPoints() override;

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private:

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //member variant

    double m_width{0};        //矩形的宽度
    double m_height{0};       //矩形的高度
    double m_angle{0};        //矩形的旋转角度

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

};

}

#endif // RECTANGLE_H
