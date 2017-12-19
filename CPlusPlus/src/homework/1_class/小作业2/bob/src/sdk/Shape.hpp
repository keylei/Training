#ifndef IAREA_HPP
#define IAREA_HPP

#include <iostream>

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
        *  @brief  isContained
        *           判断形状是否在某一区域范围内范围内
        *  @param  originX:区域原点的x轴坐标
        *          originY:区域原点的y轴坐标
        *          sizeX:区域的长
        *          sizeY:区域的宽
        *  @return 返回一个bool变量值,如果不在区域范围内,则返回false,否则返回true
        */
        virtual bool isContained(double originX, //rime 这个函数起名不合适
                                 double originY,
                                 double sizeX,
                                 double sizeY) = 0;
        //<<<----------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //member variants

        Point m_point;                          //形状的中心点坐标
        //<<<----------------------------------------------------------------------------------------------------------------------------
    };
}  //End of namespace SSDK

#endif // IAREA_HPP
