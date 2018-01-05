#ifndef RECTANGLE_H
#define RECTANGLE_H


#include <iostream>
#include <math.h>

#include "Shape.hpp"


namespace SSDK
{
/**
 *  @brief  表示矩形框，一般矩形框的基本属性
 *  @author grace
 *  @version 1.00 2017-11-20 grace
 *                note:create it
 */
class Rectangle:public Shape
{
public:
    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    Rectangle();

    /**
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

    virtual ~Rectangle();

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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

    /**
     * @brief calcArea 计算矩形面积（重写纯虚函数）
     * @return 矩形的面积
     */
    virtual double calcArea() const override;

    /**
     * @brief isContained 判断形状是否被包含在参数构成的矩形内（重写纯虚函数）
     * @param xLeft 矩形左边
     * @param xRight 矩形右边
     * @param yTop 矩形上边
     * @param yBottom 矩形下边
     * @return 有两种返回形式
     *         true:包含
     *         false:不包含
     */
    virtual bool isContained(double xLeft,
                             double xRight,
                             double yTop,
                             double yBottom) const override;

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private:
    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //member variant

    double m_width{0};   //矩形的宽度
    double m_height{0};  //矩形的高度
    double m_angle{0};   //矩形的旋转角度

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};
}//End of namespace SSDK


#endif // RECTANGLE_H
