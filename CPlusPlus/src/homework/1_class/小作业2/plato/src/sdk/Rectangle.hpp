#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.hpp"

namespace SSDK
{
    /**
     *  @brief  Rectangle
     *              矩形：
     *                  继承Shape类
     *                  包含矩形长宽、角度信息、计算面积功能、判断是否在基板之内功能
     *  @author lynn
     *  @version 1.00 2017-11-20 lynn
     *                note:create it
     *                2017-12-18 plato
     *                note:rewrite it
     */
    class Rectangle: public Shape
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //构造 & 析构函数

        Rectangle();
        Rectangle(double centerX, double centerY, double width, double height);
        virtual ~Rectangle();

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        double width() { return this->m_width; }
        void setWidth(double width) { this->m_width = width; }

        double height() { return this->m_height; }
        void setHeight(double height) { this->m_height = height; }

        double angle() { return this->m_angle; }
        void setAngle(double angle) { this->m_angle = angle; }

        virtual double calcArea() override
        {
            return (this->m_width * this->m_height);
        }

        virtual bool contains(double originX,
                              double originY,
                              double sizeX,
                              double sizeY) override;

    private:
        double m_width{0};        //矩形的宽度
        double m_height{0};       //矩形的高度
        double m_angle{0};        //矩形的旋转角度
    };

}

#endif // RECTANGLE_H
