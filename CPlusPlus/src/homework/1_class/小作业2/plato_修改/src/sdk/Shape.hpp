#ifndef SHAPE_HPP
#define SHAPE_HPP

namespace SSDK
{

    // 被测对象的形状类型
    enum class ShapeType
    {
        RECTANGLE,
        CIRCLE
    };
    /**
     *  @brief Shape
     *              抽象类：
     *                  1.计算面积的纯虚函数
     *                  2.判断对象是否在板子内的纯虚函数
     *                  3.包含被测对象中心点坐标
     *  @author plato
     *  @version 1.00 2017-12-18 plato
     *                note:create it
     */
    class Shape
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //构造 & 析构函数

        Shape();
        virtual ~Shape();

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        virtual double calcArea() = 0;

        virtual bool isContained(Shape *pShape) = 0;

        double centerX() const { return this->m_centerX; }
        void setCenterX(double centerX) { this->m_centerX = centerX; }

        double centerY() const { return this->m_centerY; }
        void setCenterY(double centerY) { this->m_centerY = centerY; }

        ShapeType& shapeType() { return this->m_shapeType; }

    protected:
        double m_centerX{0};    // 被测对象中心点X坐标
        double m_centerY{0};    // 被测对象中心点Y坐标
        ShapeType m_shapeType;  // 被测对象的形状类型
    };


}//End of namespace SSDK

#endif // SHAPE_HPP
