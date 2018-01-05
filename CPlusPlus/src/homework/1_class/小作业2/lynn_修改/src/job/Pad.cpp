#include "Pad.hpp"

using namespace Job;

#include "../sdk/Shape.hpp"

Pad::Pad()
{
    try
    {

    }
    catch(...)
    {
        THROW_EXCEPTION("构造函数出错");
    }
}

Pad::Pad(SSDK::Shape *pShape):MeasuredObject(pShape)
{
    try
    {

    }
    catch(...)
    {
        THROW_EXCEPTION("构造函数出错");
    }
}

Pad::~Pad()
{

}
