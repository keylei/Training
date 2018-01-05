#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "Shape.hpp"

#define PI 3.14

namespace SSDK
{
    /**
     *  @brief Circle
     *              圆形：
     *                  继承Shape类
     *                  包含圆形半径信息、计算面积功能、判断是否在基板之内功能
     *  @author plato
     *  @version 1.00 2017-12-18 plato
     *                note:create it
     */
    class Circle: public Shape
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //构造 & 析构函数  //rime 这个是你新加的类, 整个大region没有按照规范写

        Circle();
        Circle(double centerX, double centerY, double radius);
        virtual ~Circle();

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        double radius() const { return this->m_radius; }
        void setRadius(double radius) { this->m_radius = radius; }

        virtual double calcArea() override
        {
            return (PI*this->m_radius*this->m_radius);
        }

        virtual bool contains(double originX,
                              double originY,
                              double sizeX,
                              double sizeY) override;

    private:
        double m_radius{0}; // 圆形的半径
    };


}//End of namespace SSDK

#endif // CIRCLE_HPP
