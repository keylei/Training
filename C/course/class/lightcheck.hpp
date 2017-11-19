#ifndef LIGHTCHECK_HPP
#define LIGHTCHECK_HPP

#include <iostream>

#include "fov.hpp"
#include "datahelper.hpp"

namespace APP
{
    class LightCheck
    {
    public:
        LightCheck();
        ~LightCheck();

        int snap( int* exposureTime, int exposureCnt);

    private:
        Job::Fov fov;
    };
}//End of namespace APP



#endif // LIGHTCHECK_HPP
