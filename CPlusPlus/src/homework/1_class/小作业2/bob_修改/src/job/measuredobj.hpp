#ifndef MEASUREDOBJ_H
#define MEASUREDOBJ_H

#include <iostream>

#include "../sdk/Rectangle.hpp"
#include "../sdk/Circle.hpp"
#include "../sdk/numrandom.hpp"

namespace Job
{
    /**
     *  @brief  MeasuredObj
     *           表示一个检测对象,操作检测对象的信息
     *              例如:设置检测对象的名称,检测对象的中心点坐标等
     *  @author bob
     *  @version 1.00 2017-11-20 bob
     *                note:create it
     */
    class MeasuredObj
    {
    public:
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /*
        *  @brief   类的构造函数
        *           初始化检测对象的名称,形状,及中心点坐标
        *              1)如果是矩形,则初始化矩形的,长,宽,及角度
        *              2)如果是圆形,则初始化圆的半径
        *  @param   name:检测对象的名称
        *           shape:检测对象的形状类型(0代表圆形,1代表矩形)
        *  @return  N/A
        */
        MeasuredObj(std::string name, SSDK::ShapeType shapeType);

        /*
        *  @brief   类的析构函数
        *           销毁创建的检测对象的形状,例如pad形状为圆形,创建mark点形状为矩形等
        *  @param   N/A
        *  @return  N/A
        */
        virtual ~MeasuredObj();        
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //set & get functions

        std::string name() { return this->m_name; }
        void setName(std::string name) { this->m_name = name; }

        SSDK::Shape *pShape(){return this->m_pShape;}
        void setShapePtr(SSDK::Shape *pShape){this->m_pShape = pShape;}

        //<<<----------------------------------------------------------------------------------------------------------------------------

    private:

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //member variants

        std::string m_name{""};                 //检测对象的名称
        SSDK::Shape *m_pShape{nullptr};         //指向检测对象形状的指针
        //<<<----------------------------------------------------------------------------------------------------------------------------
    };

}//End of namespace Job

#endif // MEASUREDOBJ_H
