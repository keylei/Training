#include "FiducialMark.hpp"

using namespace Job;

FiducialMark::FiducialMark()
{
    try
    {

    }
    catch(...)
    {
        THROW_EXCEPTION("构造函数出错");
    }
}

FiducialMark::FiducialMark(SSDK::Shape* pShape):MeasuredObject(pShape)
{
    try
    {

    }
    catch(...)
    {
        THROW_EXCEPTION("构造函数出错");
    }
}

FiducialMark::~FiducialMark()
{

}
