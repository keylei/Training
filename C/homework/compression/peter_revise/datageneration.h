#ifndef DATAGENERATION_H
#define DATAGENERATION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/**
 * @brief generateLengthData 指定图片数并随机生成每张图片的长度
 * @param imgLength[]        存放所有图像长度的内存地址   //rime 数组用arr结尾
 * @param imageCount         所有图像的张数
 * @param minValue           图像长度的最小值
 * @param maxValue           图像长度的最大值
 * @return                   N/A
 */
void generateLengthData( int imgLength[],//rime 同样是生成数据, 为什么这里是数组,generateHeightData又变成指针了
                         int imageCount,//rime 这里是imageCount,generateHeightData又变成imageLength
                         int minValue,
                         int maxValue);

/**
 * @brief generateHeightData 指定图片数并生成每张图片的高度
 * @param pImageHeight       存放所有图像高度的内存地址
 * @param imgLength          所有图像的总长度
 * @param minValue           图像高度的最小值
 * @param maxValue           图像高度的最大值
 * @return                   N/A
 */
void generateHeightData( float* pImageHeight,
                         int    imageLength, //rime 这个注释不清楚, 完全看不出来是所有数组总长度的意思
                         float  minValue,
                         float  maxValue );

#endif // DATAGENERATION_H
