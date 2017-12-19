#include "FiducialMark.hpp"

using namespace std;

using namespace Job;
using namespace SSDK;

//>>>---------------------------------------------------------------------------
// constructor & destructor
FiducialMark::FiducialMark( string name,Shape *pShape ):MeasuredObj(name,pShape)
{
    try
    {

    }
    CATCH_AND_RETHROW_EXCEPTION("Constructor FiducialMark error!");
}

FiducialMark::~FiducialMark()
{
    try
    {

    }
    CATCH_AND_RETHROW_EXCEPTION("Destructor FiducialMark error!");
}
//<<<---------------------------------------------------------------------------

