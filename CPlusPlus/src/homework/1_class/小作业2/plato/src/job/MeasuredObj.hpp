#ifndef MEASUREDOBJ_H
#define MEASUREDOBJ_H

#include <iostream>

#include "sdk/Shape.hpp"

namespace Job
{
    /**
     *  @brief  MeasuredObj
     *              被测对象：
     *                  1.被测对象名
     *                  2.被测对象形状信息
     *  @author lynn
     *  @version 1.00 2017-11-20 lynn
     *                note:create it
     *                2017-12-18 plato
     *                note:rewrite it
     */
    class MeasuredObj
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //构造 & 析构函数

        MeasuredObj();
        virtual ~MeasuredObj();

        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        std::string name() { return this->m_name; }
        void setName(std::string name) { this->m_name = name; }

        SSDK::Shape* pShape() const { return this->m_pShape; }
        void setPShape(SSDK::Shape *pShape) { this->m_pShape = pShape; }

    protected:
        std::string m_name{""};          // 被测对象名
        SSDK::Shape* m_pShape{nullptr};  // 被测对象形状信息
    };

}//End of namespace Job

#endif // MEASUREDOBJ_H
