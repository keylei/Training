#ifndef DATAGENERATION_H
#define DATAGENERATION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config"

// 生成0.00到指定最大范围的随机数
#define RANDOM_DATA  (float)(rand() % (DATA_MAX * 100 + 1)) / 100

//lynn171101:a.参数arrLength改为arrLenArr
//           b.参数floatArr改为pData
//           c.函数名generateData改为generateRandomData(文件名为dataGeneration.c,
//             加个random以示区别更舒服)
/*
*  @brief   生成数据
*  @param   lenArr  :数组长度数组
*           pData   :存放数据的首地址
*  @return  N/A
*/
void generateRandomData(int arrLenArr[], float **pData);

#endif // DATAGENERATION_H

