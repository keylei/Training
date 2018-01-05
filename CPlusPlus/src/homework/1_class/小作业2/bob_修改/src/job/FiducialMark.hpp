#ifndef FIDUCIALMARK_HPP
#define FIDUCIALMARK_HPP

#include <iostream>

#include "../sdk/Shape.hpp"
#include "../job/measuredobj.hpp"
#include "../sdk/Circle.hpp"
#include "../sdk/Rectangle.hpp"
#include "../sdk/numrandom.hpp"

namespace Job
{
    /**
     *  @brief FiducialMark
     *          操作检测程式的基准点,例如设置基准点的形状,基准点的名字等
     *
     *         基准点:任意一块PCB板都会有基准点,其作用是通过基准点的坐标,
     *               可以获取PCB板任意一个检测对象的相对坐标
     *  @author bob
     *  @version 1.00 2017-12-17 bob
     *                note:create it
     */
    class FiducialMark : public MeasuredObj
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
         * @brief FiducialMark
         *          初始化基准点的名称,及形状
         * @param name:pad的名称
         * @param shape:pad的形状,为枚举类型,圆形则为0,矩形则为1
         */
        FiducialMark(std::string name,SSDK::ShapeType shapeType);

        /**
        *  @brief  析构函数
        *  @param  N/A
        *  @return N/A
        */
        virtual ~FiducialMark();
        //>>>----------------------------------------------------------------------------------------------------------------------------
    };
}   //End of namespace Job

#endif // FIDUCIALMARK_HPP
