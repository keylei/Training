#include "Pad.hpp"

using namespace std;

using namespace Job;
using namespace SSDK;

//>>>---------------------------------------------------------------------------
//
Pad::Pad( string name,Shape *pShape ):MeasuredObj(name,pShape)
{
    try
    {

    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor error!");
}

Pad::~Pad()
{
    try
    {

    }
    CATCH_AND_RETHROW_EXCEPTION("Destructor error!");
}
//<<<---------------------------------------------------------------------------

