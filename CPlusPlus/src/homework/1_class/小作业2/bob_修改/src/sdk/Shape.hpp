#ifndef IAREA_HPP
#define IAREA_HPP

#include <iostream>
#include <vector>

#include "Point.hpp"
#include "customexception.hpp"

namespace SSDK
{
    /**
     * @brief ShapeType
     *          形状类型,0为圆形,1为矩形
     */
    enum ShapeType
    {
        CIRCLE = 0,
        RECTANGLE
    };

    /**
     *  @brief Shape
     *          操作任何形状的接口
     *              (例如计算圆形,矩形的中心点坐标等)
     *  @author bob
     *  @version 1.00 2017-12-17 bob
     *                note:create it
     */

    class Shape
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief 构造函数
        *  @param  N/A
        *  @return N/A
        */
        Shape();

        /**
        *  @brief  Shape
        *           初始化成员变量,该形状x,y轴坐标
        *  @param  xPos: 形状x轴坐标
        *          yPos:形状y轴坐标
        *  @return N/A
        */
        Shape(double xPos,double yPos);

        /**
        *  @brief  析构函数
        *  @param  N/A
        *  @return N/A
        */
        virtual ~Shape();
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        // get & set functions

        Point& point(){return this->m_point;}

        ShapeType shapeType(){ return this->m_shapeType;}
        void setShapeType(ShapeType shapeType){this->m_shapeType = shapeType;}
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        //virtual functions

        /**
        *  @brief calcArea
        *           虚函数,计算任意形状的面积
        *  @param  N/A
        *  @return 任意形状面积的值
        */
        virtual double calcArea() = 0;

        /**
        *  @brief  contains
        *           判断形状内是否包含形状
        *  @param  pShape: 形状内包含的形状的指针
        *  @return 返回一个bool变量值,如果不在形状范围内,返回false,否则返回true
        */
        virtual bool contains(Shape * pShape) = 0;

        //<<<----------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //member variants

        Point m_point;                             //形状的中心点坐标
        ShapeType m_shapeType;                     //形状的类型
        //<<<----------------------------------------------------------------------------------------------------------------------------
    };
}  //End of namespace SSDK

#endif // IAREA_HPP
