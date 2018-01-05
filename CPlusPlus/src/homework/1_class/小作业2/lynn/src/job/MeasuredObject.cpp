#include "MeasuredObject.hpp"

using namespace Job;

MeasuredObject::MeasuredObject()
{

}

MeasuredObject::MeasuredObject(SSDK::IShape *pShape)
{
    this->m_pBody = pShape;
}

MeasuredObject::~MeasuredObject()
{
}
