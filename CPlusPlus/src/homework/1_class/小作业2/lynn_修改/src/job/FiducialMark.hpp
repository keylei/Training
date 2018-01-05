#ifndef FIDUCIALMARK_HPP
#define FIDUCIALMARK_HPP

#include "../sdk/Shape.hpp"
#include "MeasuredObject.hpp"

namespace Job
{

class FiducialMark:public MeasuredObject
{
public:

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    /**
    *  @brief   默认构造函数
    *  @param   N/A
    *  @return  N/A
    */
    FiducialMark();

    /**
    *  @brief   将传入的形状设置为fiducialMark的形状
    *  @param   pShape:指向要设置的形状
    *  @return  N/A
    */
    explicit FiducialMark(SSDK::Shape *pShape);

    /**
    *  @brief   默认析构函数
    *  @param   N/A
    *  @return  N/A
    */
    virtual ~FiducialMark();

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};

}//End of namespace Job

#endif // FIDUCIALMARK_HPP
