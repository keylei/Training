#ifndef PAD_HPP
#define PAD_HPP

#include <iostream>

#include "MeasuredObj.hpp"
#include "../sdk/Shape.hpp"

namespace Job
{
    /**
     * @brief Pad
     *      Pad类是是表示被检测的焊盘的类
     */
    class Pad:public MeasuredObj
    {
    public:
        //>>>-------------------------------------------------------------------
        // constructor & destructor
        Pad( std::string name,SSDK::Shape* pShape );
        virtual~Pad();
        //<<<-------------------------------------------------------------------
    };

}//End of namespace Job

#endif // PAD_HPP
