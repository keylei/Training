#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iostream>

#include "Circle.hpp"
#include "CustomException.hpp"
#include "FormatConvertor.hpp"

namespace SSDK
{
    /**
     *  @brief  Rectangle
     *      Rectangle类表示矩形，包含一般矩形的基本属性.
     *  @author lynn
     *  @version 1.00 2017-11-20 lynn
     *                note:create it
     */
    class Rectangle:public Shape
    {
    public:
        //>>>-------------------------------------------------------------------
        // constructor & destructor
        Rectangle();
        /**
         * @brief Rectangle
         *      带参构造函数,根据参数,将其赋值给成员变量
         * @param xPos
         *      矩形中心点横坐标
         * @param yPos
         *      矩形中心点纵坐标
         * @param width
         *      矩形宽度
         * @param height
         *      矩形高度
         */
        Rectangle( double xPos,
                   double yPos,
                   double width,
                   double height);
        /**
         * @brief Rectangle
         *      带参构造函数,根据参数,将其赋值给成员变量
         * @param xPos
         *      矩形中心点横坐标
         * @param yPos
         *      矩形中心点纵坐标
         * @param width
         *      矩形宽度
         * @param height
         *      矩形高度
         * @param angle
         *      矩形与水平线之间的夹角角度
         */
        Rectangle( double xPos,
                   double yPos,
                   double width,
                   double height,
                   double angle );
        virtual~Rectangle();

        //>>>-------------------------------------------------------------------
        // set & get function
        double width() { return this->m_width; }
        void setWidth(double width) { this->m_width = width; }

        double height() { return this->m_height; }
        void setHeight(double height) { this->m_height = height; }

        double angle() { return this->m_angle; }
        void setAngle(double angle) { this->m_angle = angle; }

        //>>>-------------------------------------------------------------------
        // override
        /**
         * @brief calArea
         *      重写计算面积的函数
         *  通过类内的成员变量计算出矩形的面积,以double类型返回.
         * @param N/A
         * @return
         *      返回double类型的圆形面积
         */
        virtual double calArea() override;
        /**
         * @brief isContains
         *      判断当前的矩形区域是否在传入的矩形区域内
         * @param xPos
         *      传入的矩形区域原点的横坐标
         * @param yPos
         *      传入的矩形区域原点的纵坐标
         * @param sizeX
         *      传入的矩形区域宽度
         * @param sizeY
         *      传入的矩形区域高度
         * @return
         *      返回为true:当前圆形区域在传入的矩形区域内部
         *      返回为false:当前圆形区域不在传入的矩形区域内部
         */
        virtual bool contains(Shape* shape ) override;
        /**
         * @brief type
         *      返回当前图形的形状
         * @return
         *      返回类型为string类型的矩形
         */
        virtual std::string type() override;
        //<<<-------------------------------------------------------------------


    private:
        //>>>-------------------------------------------------------------------
        // member function
        double m_width {0};        // 矩形的宽度
        double m_height {0};       // 矩形的高度
        double m_angle {0};        // 矩形的旋转角度
        //<<<-------------------------------------------------------------------
    };

}

#endif // RECTANGLE_HPP
