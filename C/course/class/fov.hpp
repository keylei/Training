#ifndef FOV_HPP
#define FOV_HPP

#include "datahelper.hpp"

namespace Job
{
    class Fov
    {
    public:
        Fov();
        virtual ~Fov();

        int snap(int* exposureTime, int exposureCnt);

     private:
        SDK::DataHelper dataHelper;
    };
}//End of namespace Job



#endif // FOV_HPP
