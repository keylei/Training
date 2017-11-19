#include "datahelper.hpp"

using namespace SDK;

DataHelper::DataHelper()
{

}

DataHelper::~DataHelper()
{

}

int DataHelper::findMax(int* arr, int arrLen)
{
    int cnt = arrLen;
    int max = arr[0];
    for (int i = 1; i < cnt; ++i)
    {
        if(max <  arr[i])
        {
            max = arr[i];
        }
    }

    return max;
}
