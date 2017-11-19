#ifndef DATAHELPER_HPP
#define DATAHELPER_HPP

namespace SDK
{
    class DataHelper
    {
    public:
        DataHelper();
        virtual ~DataHelper();

        int findMax( int* arr, int arrLen );
    };
}//End of namespace SDK


#endif // DATAHELPER_HPP
