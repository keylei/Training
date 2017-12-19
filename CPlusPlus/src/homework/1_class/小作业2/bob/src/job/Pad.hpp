#ifndef PAD_HPP
#define PAD_HPP

#include <iostream>

#include "../sdk/Shape.hpp"
#include "./job/measuredobj.hpp"
#include "../sdk/Circle.hpp"
#include "../sdk/Rectangle.hpp"
#include "../sdk/numrandom.hpp"

namespace Job
{
    /**
     *  @brief Pad
     *          操作PCB板焊盘信息,例如设置焊盘名称,焊盘形状等
     *
     *          pad是PCB板和元器件引脚相互焊接的部份,通过在pad上印刷锡膏
     *          然后将元器件放在锡膏上,通过高温焊接则,则可完成元器件与引脚相互贴合
     *  @author bob
     *  @version 1.00 2017-12-18 bob
     *                note:create it
     */
    class Pad : public MeasuredObj
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
         * @brief Pad
         *          Pad的构造函数,初始化
         * @param name:pad的名称
         * @param shape:pad的形状,为枚举类型,圆形则为0,矩形则为1
         */
        Pad(std::string name,SSDK::ShapeType shape);

        /**
        *  @brief  析构函数
        *  @param  N/A
        *  @return N/A
        */
        virtual ~Pad();
        //>>>----------------------------------------------------------------------------------------------------------------------------
    };
}   //End of namespace Job

#endif // PAD_HPP
