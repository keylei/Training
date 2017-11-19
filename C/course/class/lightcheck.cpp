#include "lightcheck.hpp"

using namespace APP;

LightCheck::LightCheck()
{

}

LightCheck::~LightCheck()
{

}

int LightCheck::snap(int* exposureTime, int exposureCnt)
{
    return fov.snap(exposureTime, exposureCnt);
}
