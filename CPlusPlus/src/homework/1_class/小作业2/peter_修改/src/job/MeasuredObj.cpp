#include "MeasuredObj.hpp"

using namespace std;

using namespace Job;
using namespace SSDK;

//>>>---------------------------------------------------------------------------
// constructor & destructor
MeasuredObj::MeasuredObj()
{
    try
    {

    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor \"MeasuredObj\" error!");
}

MeasuredObj::MeasuredObj(string name, Shape *pShape)
{
    try
    {
        this->m_name = name;
        this->m_pShape = pShape;
    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor \"MeasuredObj\" error!");
}


MeasuredObj::~MeasuredObj()
{
    try
    {
        if(nullptr != this->m_pShape)
        {
            delete this->m_pShape;
            this->m_pShape = nullptr;
        }
        if(nullptr != this->m_pShape)
        {
            THROW_EXCEPTION("Delete error!");
        }
    }
    CATCH_AND_RETHROW_EXCEPTION("Destructor \"MeasuredObj\" error!")
}
//<<<---------------------------------------------------------------------------
