#ifndef DATACOMPRESSION_H
#define DATACOMPRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>

#include "datahelper.h"
#include "config"

// COMPRESSION_LIMIT为压缩下限,由于在存储文件时，即使小于4096B的文件存储时依然会占用4096B
// 的空间，故4096为压缩的界限，压缩后大小小于4096B的数据会被多个拼凑到足够4096B大小一起存储：
#define COMPRESSION_LIMIT 4096
#define HEADER_LENGTH 6                     // 压缩出的数据的表头长度

//rime 这种最好是需要把压缩的格式再讲解下
/*
*  @brief   将一个float数组压缩为byte数组
*  @param   destArr :压缩后的数据存储数组
*           srcArr  :要压缩的数组
*           length  :要压缩的数组的长度
*  @return  N/A
*/
void compressSingleArr(unsigned char destArr[],float srcArr[],int length);


//lynn171101:a.将函数名从compress改为compressAndExportData
//           b.将参数floatArr改为pData
//           c.将参数arrLength改为arrLenArr
/*
*  @brief   压缩数据并写入到文件中
*  @param   lenArr  :保存每个数组长度的数组
*           pData   :要压缩的数据
*  @return  N/A
*/
void compressAndExportData(int lenArr[], float **pData);


//lynn171101:a.将函数名从decompress改为importAndDecompressData
//           b.将变量名newArrLength改为lenArr
//           c.将变量名newFloatArr改为pDecompressionData
/*
*  @brief   解压文件中的数据
*  @param   lenArr          :数组长度头指针
*           pDecompressedArr:指向解压后的数组指针的指针
*  @return  N/A
*/
void importAndDecompressData(int lenArr[], float **pDecompressionData);


//lynn171107:a.将参数arrLength改为lenArr
//           b.将参数floatArr改为pSrcData
//           c.将参数newFloatArr改为pNewData
/*
*  @brief   生成两个float数组的数据差值并存到文件中
*  @param   lenArr  :用于保存数组长度的数组
*           pSrcData:原数据存储指针
*           pNewData:解压出的数据存储指针
*  @return  N/A
*/
//rime 对于这种比较差值的, 可以接受pData1, 可以接受pData1,但更加理想的是pOrigData和pComparedData
void calcDataDiff(int lenArr[], float **pSrcData,float **pNewData);


//lynn171108:添加了释放内存空间用的函数
/*
*  @brief   释放所有开辟的空间
*  @param   pGenerationData     :指向生成的数据的指针
*           pDecompressionData  :指向解压缩出的数据的指针
*  @return  N/A
*/
//rime +1 有意识的把内存释放封装成一个函数, 是值得推荐的事情, 不过这一般用于比较复杂的情况, 通常包含了
//一系列关联的释放, 正常情况下还是要遵守在哪里malloc就在哪里free
void dispose(float **pGenerationData,float **pDecompressionData);
#endif // DATACOMPRESSION_H
