#ifndef FIDUCIALMARK_HPP
#define FIDUCIALMARK_HPP

#include "MeasuredObj.hpp"
#include "sdk/Rectangle.hpp"
#include "sdk/Circle.hpp"

namespace Job
{
    /**
     *  @brief FiducialMark
     *              基准点:
     *                  继承MeasuredObj类
     *  @author plato
     *  @version 1.00 2017-12-18 plato
     *                note:create it
     */
    class FiducialMark: public MeasuredObj
    {
    public:
        FiducialMark();
        virtual ~FiducialMark();
    };

}//End of namespace Job



#endif // FIDUCIALMARK_HPP
