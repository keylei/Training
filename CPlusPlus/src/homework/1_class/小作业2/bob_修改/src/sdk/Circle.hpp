#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <math.h>

#include "Shape.hpp"


namespace SSDK
{
    /**
     *  @brief Circle
     *          表示一个圆形框,可以操作圆形框的基本属性,例如:中心点坐标,半径等
     *  @author bob
     *  @version 1.00 2017-12-17 bob
     *                note:create it
     */
    class Circle : public Shape
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief  构造函数
        *  @param  N/A
        *  @return N/A
        */
        Circle();

        /**
        *  @brief  Circle
        *          初始化圆形框的成员变量,设置圆形框的中心点x,y坐标,及圆形框的半径
        *  @param  xPos: 圆形框中心点x轴坐标
        *          yPos: 圆形框中心点y轴坐标
        *          radius: 圆形框的半径
        *  @return  N/A
        */
        Circle(double xPos,double yPos,double radius);

        /**
        *  @brief  析构函数
        *  @param  N/A
        *  @return N/A
        */
        virtual ~Circle();
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        // get & set functions

        double radius() {return this->m_radius;}
        void setRadius(double radius) {this->m_radius = radius;}
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        //virtual functions

        /**
        *  @brief  calcArea
        *           计算圆形的面积
        *  @param   N/A
        *  @return  圆形的面积
        */
        virtual double calcArea() override;

        /**
        *  @brief  contains
        *           判断圆形框中是否包含形状(形状类型如圆形,矩形等)
        *  @param  N/A
        *  @return  返回一个bool变量值,如果不在圆形框范围内,返回false,否则返回true
        */
        virtual bool contains(Shape *pShape) override;

        //<<<----------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //comment variants

        double m_radius{0.0};               //圆形框的半径
        //<<<----------------------------------------------------------------------------------------------------------------------------
    };
} //End of namespace SSDK

#endif // CIRCLE_HPP
