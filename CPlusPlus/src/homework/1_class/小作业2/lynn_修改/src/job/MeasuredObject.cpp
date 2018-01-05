#include "MeasuredObject.hpp"

using namespace Job;

MeasuredObject::MeasuredObject()
{
    try
    {

    }
    catch(...)
    {
        THROW_EXCEPTION("构造函数出错");
    }
}

MeasuredObject::MeasuredObject(SSDK::Shape *pShape)
{
    try
    {
        this->m_pBody = pShape;
    }
    catch(...)
    {
        THROW_EXCEPTION("构造函数出错");
    }
}

MeasuredObject::~MeasuredObject()
{
}
