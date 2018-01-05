#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "CustomException.hpp"

namespace SSDK
{
    enum class ShapeType
    {
        CIRCLE,     // 圆形
        RECTANGLE   // 矩形
    };

    /**
     *  @brief  Shape
     *      shape类是一个表达形状的类.
     *  Shape类中的成员变量包含当前形状的中心点坐标和计算该形状面积的函数.
     *  @author peter
     *  @version 1.00 2017-12-17 peter
     *                note:create it
     */
    class Shape
    {
    public:
        //>>>-------------------------------------------------------------------
        // constructor & destructor
        Shape();
        virtual~Shape();

        //>>>-------------------------------------------------------------------
        // get & set function
        double xPos() { return this->m_xPos; }
        void setXPos(double xPos) { this->m_xPos = xPos; }

        double yPos() { return this->m_yPos; }
        void setYPos(double yPos) { this->m_yPos = yPos; }

        //>>>-------------------------------------------------------------------
        // cal area & isContain
        virtual double calArea()=0;
        virtual bool contains(Shape* shape )=0;
        virtual std::string type() = 0;
        //<<<-------------------------------------------------------------------


    private:
        //>>>-------------------------------------------------------------------
        // member variant
        double m_xPos {0};
        double m_yPos {0};
        //<<<-------------------------------------------------------------------
    };

}//End of namespace SSDK

#endif // SHAPE_HPP
