#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.hpp"

namespace SSDK
{
    /**
     *  @brief  Rectangle
     *            表示矩形框，可操作矩形框的基本属性,(例如设置矩形框的中心点坐标,长,宽等)
     *  @author lynn
     *  @version 1.00 2017-11-20 lynn
     *                note:create it
     */
    class Rectangle:public Shape
    {
    public:
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief   类的构造函数
        *  @param   N/A
        *  @return  N/A
        */
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

        /**
        *  @brief   类的析构函数
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
        //virtual functions

        /**
        *  @brief  calcArea
        *           计算矩形框的面积,并将值返回
        *  @param  N/A
        *  @return 矩形框的面积
        */
        virtual double calcArea() override;

        /**
        *  @brief  isContained
        *           重写虚函数,判断圆形是否在区域范围内
        *  @param  originX:区域原点的x轴坐标
        *          originY:区域原点的y轴坐标
        *          sizeX:区域的X轴坐标
        *          sizeY:区域的Y轴坐标
        *  @return
        */
        virtual bool isContained(double originX,
                                 double originY,
                                 double sizeX,
                                 double sizeY) override;
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //member variants

        double m_width{0.0};        //矩形的宽度
        double m_height{0.0};       //矩形的高度
        double m_angle{0.0};        //矩形的旋转角度
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   };
}   //End of namespace SSDK

#endif // RECTANGLE_H
