#ifndef PAD_HPP
#define PAD_HPP

#include "MeasuredObj.hpp"
#include "sdk/Rectangle.hpp"
#include "sdk/Circle.hpp"

namespace Job
{
    /**
     *  @brief Pad
     *            焊盘：
     *              继承MeasuredObj类
     *  @author plato
     *  @version 1.00 2017-12-18 plato
     *                note:create it
     */
    class Pad: public MeasuredObj
    {
    public:
        Pad();
        virtual ~Pad();
    };

}//End of namespace Job


#endif // PAD_HPP
