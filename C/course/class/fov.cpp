#include "fov.hpp"

using namespace Job;

Fov::Fov()
{

}

Fov::~Fov()
{

}

int Fov::snap(int* exposureTime, int exposureCnt)
{
    return dataHelper.findMax(exposureTime,exposureCnt);
}

