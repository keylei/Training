#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"

#include "CustomException.hpp"

#define PI 3.14

namespace SSDK
{
    /**
     *  @brief Circle
     *      Circle类表示圆形，包含一般圆形的基本属性.
     *  @author peter
     *  @version 1.00 2017-12-17 peter
     *                note:create it
     */
    class Circle:public SSDK::Shape//rime 在SSDK内部就不需要再次写SSDK了
    {
    public:
        //>>>-------------------------------------------------------------------
        // constructor & destructor
        Circle();
        Circle(double xPos,double yPos,double radius);
        virtual~Circle();

        //>>>-------------------------------------------------------------------
        // set & get function
        double radius() { return this->m_radius; }
        void setRadius(double radius) { this->m_radius = radius; }

        //>>>-------------------------------------------------------------------
        // override
        /**
         * @brief calArea
         *      重写计算面积的函数
         *  通过类内的成员变量计算出圆形的面积,以double类型返回.
         * @param N/A
         * @return
         *      返回double类型的圆形面积
         */
        virtual double calArea() override;
        /**
         * @brief isContains
         *      判断当前的圆形区域是否在传入的矩形区域内
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
        virtual bool isContains( double xPos,
                                 double yPos,
                                 double sizeX,
                                 double sizeY ) override;
        //<<<-------------------------------------------------------------------


    private:
        //>>>-------------------------------------------------------------------
        // member variant
        double m_radius {0};       // 圆形的半径
        //<<<-------------------------------------------------------------------
    };
}// End of namespace SSDK


#endif // CIRCLE_HPP
