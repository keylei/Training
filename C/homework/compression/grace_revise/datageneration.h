#ifndef DATAGENERATION_H
#define DATAGENERATION_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
/*
*  @brief 随机生成所有像素点高度信息  //grace171108 增加函数介绍，参数以及返回值说明以及返回值
*  @param pImgLen：每张图片高度
*         maxHeight：高度的最大值 0 //rime 这里就不应该标示参数的范围, 本身参数就是传进来的, 你怎么知道参数是多大的
*         minHeight：高度的最小值 5000
*         maxImgLen:最大数组长度 5000
*         minImgLen:最小数组长度 2048
*         imgCnt:数组个数(1000)
*  @return pHeightData：所有的图片高度数据
*/
float* generateHighData(int* pImgLen, //rime 既然是底层函数, 你就不应该注明是高度数据, 倒是可以说明是怎么声明的, 何况高度还拼错了
                        int maxHeight,
                        int minHeight,
                        int maxImgLen,
                        int minImgLen,
                        int imgCnt);

#endif // DATAGENERATION_H
