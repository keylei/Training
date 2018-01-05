#include "MeasuredObj.hpp"

using namespace Job;

MeasuredObj::MeasuredObj()
{

}


MeasuredObj::~MeasuredObj()
{
    try
    {
        delete this->m_pShape;
    }
    catch(...)
    {

    }
}


