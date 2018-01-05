#ifndef FIDUCIALMARK_HPP
#define FIDUCIALMARK_HPP


#include "./job/MeasuredObj.hpp"
#include "../sdk/Shape.hpp"


namespace Job
{
/**
 *  @brief FiducialMark
 *         基准点信息
 *
 *  @author grace
 *  @version 1.00 2017-12-19 grace
 *                note:create it
 */
class FiducialMark:public MeasuredObj
{
public:
    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    FiducialMark();
    virtual ~FiducialMark();

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};
}//End of namespace App


#endif // FIDUCIALMARK_HPP
