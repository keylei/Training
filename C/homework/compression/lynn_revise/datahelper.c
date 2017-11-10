#include "datahelper.h"

//rime 有些地方使用array, 有些地方使用arr
short calcMin(int arrLength, float array[])
{
//    lynn:171030 此处的初始化不合理。
//    short min = DATA_MAXIMUM;
    short min = array[0];
    for ( int j = 1; j < arrLength; ++j )
    {
        if ( min > array[j] )
        {
            min = (short)array[j];
        }
    }
    return min;
}


short calcMax(int arrLength, float array[])
{
    short max = array[0];
    for ( int j = 1; j < arrLength; ++j )
    {
        if ( max < array[j] )
        {
            max = (short)array[j];
        }
    }
    return max;
}


void writeDataToFile(char *path,unsigned char dataArr[],int length)
{
    int pFile = open(path, O_WRONLY | O_CREAT,0777);
    write(pFile, dataArr, length);
    close(pFile);
}


unsigned char mapFloatToByte(float srcData, short min, short max)
{
    unsigned char mappedData;
    mappedData = MAPPING_MAX_VALUE * (srcData - min)\
            / (max - min);
    return mappedData;
}


float mapByteToFloat(unsigned char srcData, short min, short max)
{
    float mappedData;
    mappedData = min + (float)srcData * (max - min)\
            / MAPPING_MAX_VALUE;
    return mappedData;
}
