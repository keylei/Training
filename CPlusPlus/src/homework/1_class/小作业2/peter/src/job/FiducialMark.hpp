#ifndef FIDUCIALMARK_HPP
#define FIDUCIALMARK_HPP

#include <iostream>

#include "MeasuredObj.hpp"
#include "../sdk/Shape.hpp"

namespace Job
{
    /**
     * @brief FiducialMark
     *      FiducialMark类是表示被检测的mark点的类
     */
    class FiducialMark:public MeasuredObj
    {
    public:
        //>>>-------------------------------------------------------------------
        // constructor & destructor
        FiducialMark( std::string name, SSDK::Shape* pShape );
        virtual~FiducialMark();
        //<<<-------------------------------------------------------------------
    };

}//End of namespace Job

#endif // FIDUCIALMARK_HPP
