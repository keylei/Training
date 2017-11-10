#include "datageneration.h"

//lynn171102:对该函数内部的注释进行了优化 //rime arrLenArr[] 直接lenArr就可以了
void generateRandomData(int arrLenArr[], float **pData)
{
    srand(time(0));         // 设置随机数种子,若不设置rand函数随机出的值将会是一样的

    // 生成指定个数个数组：
    for ( int i = 0; i < FLOAT_ARR_CNT; ++i )
    {
        // 使用随机函数，生成指定范围的随机数作为数组长度
        arrLenArr[i] = rand() % (MAX_ARR_LENGTH - MIN_ARR_LENGTH + 1)\
                + MIN_ARR_LENGTH;

        // 在内存中开辟存放单个数组数据所需的空间，并将首地址记录在pData[i]
        pData[i] = malloc(sizeof(float) * arrLenArr[i]);

        //rime pData一开始就应该进行判断,每次在循环中进行判断浪费效率
        if ( pData != NULL && pData[i] != NULL )        // 若空间开辟成功
        {
            for ( int j = 0; j < arrLenArr[i]; ++j )    // 随机生成数组中的高度数据
            {
                // 使用随机宏函数，生成0.00到指定最大范围的随机数作为高度数据
                pData[i][j] = RANDOM_DATA;
            }
        }
    }
}
