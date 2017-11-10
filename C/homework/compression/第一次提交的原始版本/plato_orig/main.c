/*
实现一个图像压缩的算法（这里需要前提介绍下图像的基础知识: 8位灰度图像，bitmap,png,jpg）
- 1.创建1000个float数组，长度从2048到5000随机生成，数据范围从0.00-5000.00随机生成
    生成数据和压缩过程使用for循环，使用数组指针，在堆上创建
- 2.遍历所有的数组,判断数组长度:
    如果长度>4096,直接压缩;
    如果长度<4096,那么需要和其他长度小于<4096的数组压缩到到同一个新创建的byte数组中。
    新创建的byte数组长度至少为4096
    一个byte数组可以存放多个float数组的数据，但是一个float数组只能放在一个byte数组
- 3.byte数组需要先设置表头:表头的定义如下：
    3.1 第1个Byte：压缩的float数组的个数,如果该byte数组包含了1个float数组的数据，
        那么就是1;如果包含了2个，那么就为2
    3.2 第2,3个Byte：第一个数组的长度
    3.3 往后w*h个byte：float数组每一个数据转化成一个byte，转换方式见4说明
    3.4 如果存多个数据，依次往后按照这样的格式存
- 4.float数组中每一个高度的小数部分去除，整数部分按照其最大值和最小值的范围映射到[0,255].
- 5.获取到的byte数组保存为文件，文件名按照压缩的元件名，如压缩了一个chip001的数组就是
    chip001,如果是chip001和chip002就是chip001_chip002
- 6.读取保存的文件，按照同样的规则把高度从byte解析到float数组
- 7.统计压缩和解压缩的时间
- 8.将解压出的数组的数据和float数组的数据的差值保存名字为“chipxxxdiff或
    chipxxx_chipxxxdiff”格式的文件中
注意:
- 1.整个过程注意内存泄漏问题
- 2.数据的生成，压缩，导出，解压都封装成函数
*/

/**
 *  @brief image compression algorithm
 *
 *  @author plato
 *  @version 1.00 2017-10-16 plato
 *                note:create it
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#define FLOAT_ARR_NUMBER 1000           // float数组个数
#define MIN_ARR_LENGTH 2048             // 最小数组长度
#define MAX_ARR_LENGTH 5000             // 最大数组长度
#define DATA_MAXIMUM 5000               // 数据最大值
#define COMPRESSION_LIMIT 4096          // 压缩界限
#define MAPPING_DEST_MAXIMUM 255        // 映射目标最大值
#define HEADER_LENGTH 6                 // byte数组表头长度

// 计算float数据的最小值和最大值
short calcMinimum(int arrLength, float *floatArr);
short calcMaximum(int arrLength, float *floatArr);
// 计算映射到 0-255 后的数据
char calcMappedData(float floatData, short minimum, short maximum);
// 计算解压后的数据
float calcDecompressedData(float byteData, short minimum, short maximum);
// 生成数据
void generateData(int *arrLength, float **floatArr);
// 压缩数据并保存到文件中
void compress(int *arrLength, float **floatArr);
// 将数据写到文件中
void exportData(char *fileName, unsigned char *byteArr, int byteArrLength);
// 解压数据
void decompress(int *newArrLength, float **newFloatArr);
// 计算源数据与解压后的数据的差值
void calcDataDiff(int *arrLength, float **floatArr,float **newFloatArr);


/*
*  @brief 计算float数据最小值
*  @param arrLength为数组长度
*         *floatArr为float数组头指针
*  @return 数据最小值
*/
short calcMinimum(int arrLength, float *floatArr)
{
    short minimum = DATA_MAXIMUM;
    for ( int j = 0; j < arrLength; ++j )
    {
        if ( minimum > floatArr[j] )
        {
            minimum = (short)floatArr[j];
        }
    }
    return minimum;
}

/*
*  @brief 计算float数据最大值
*  @param arrLength为数组长度
*         *floatArr为float数组头指针
*  @return 数据最大值
*/
short calcMaximum(int arrLength, float *floatArr)
{
    short maximum = 0;
    for ( int j = 0; j < arrLength; ++j )
    {
        if ( maximum < floatArr[j] )
        {
            maximum = (short)floatArr[j];
        }
    }
    return maximum;
}

/*
*  @brief 计算映射后的数据
*  @param floatData为float数组中的一个数据
*         minimum为float数组中的最小值
*         maximum为float数组中的最大值
*  @return 映射后的数据
*/
char calcMappedData(float floatData, short minimum, short maximum)
{
    unsigned char mappedData;
    mappedData = MAPPING_DEST_MAXIMUM*(floatData - minimum)/(maximum - minimum);
    return mappedData;
}

/*
*  @brief 计算解压后的数据
*  @param byteData为byte数组中的一个数据
*         minimum为byte数组中的最小值
*         maximum为byte数组中的最大值
*  @return 映射后的数据
*/
float calcDecompressedData(float byteData, short minimum, short maximum)
{
    float decompressedData;
    decompressedData = minimum+byteData*(maximum - minimum)/MAPPING_DEST_MAXIMUM;
    return decompressedData;
}

/*
*  @brief 生成数据
*  @param *arrLength为数组长度头指针
*         **float为指向float数组指针的指针
*  @return N/A
*/
void generateData(int *arrLength, float **floatArr)
{
    srand(time(0));         // 设置随机数种子

    for ( int i = 0; i < FLOAT_ARR_NUMBER; ++i )
    {
        if ( arrLength != NULL )
        {
            // 使用随机函数，生成2048-5000的随机数作为数组长度
            arrLength[i] = rand() % (MAX_ARR_LENGTH - MIN_ARR_LENGTH + 1) + MIN_ARR_LENGTH;
        }
        // 在内存中开辟数组长度所需的内存空间，并将首地址赋值给floatArr[i]
        floatArr[i] = malloc(sizeof(float) * arrLength[i]);

        if ( floatArr != NULL && floatArr[i] != NULL )
        {
            for ( int j = 0; j < arrLength[i]; ++j )
            {
                // 使用随机函数，生成0.00-5000.00的随机数作为高度数据
                floatArr[i][j] = (float)(rand() % (DATA_MAXIMUM * 100 + 1)) / 100;
            }
        }
    }
}

/*
*  @brief 压缩数据并写入到文件中
*  @param *arrLength为数组长度头指针
*         **float为指向float数组指针的指针
*  @return N/A
*/
void compress(int *arrLength, float **floatArr)
{
    char fileName[50];                      // 用于存放文件名

    int arrTotalLength = 0;                 // 拼接后的数组总长度
    int compressionNumber = 0;              // 每个byte数组压缩的数组个数
    int index = 0;                          // 用于记录需拼接的第一个数组长度索引

    mkdir("compressedFiles",0777);          // 创建目录，用于存放byte数组文件

    for ( int i = 0; i < FLOAT_ARR_NUMBER; ++i )
    {
        unsigned char *byteArr;             // byte数组头指针
        short *headerPtr;                   // 表头的头指针
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1 当数组长度大于等于4096时
        if ( arrLength[i] >= COMPRESSION_LIMIT )
        {
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //1.1 直接压缩此数组并写入到文件中
            // 在内存中开辟数组长度所需的内存空间，并将首地址赋值给byteArr
            byteArr = malloc(1 + HEADER_LENGTH + arrLength[i]);

            if ( byteArr != NULL )
            {
                // 保存byte数组的表头
                byteArr[0] = 1;             // 保存数组个数
                headerPtr = &byteArr[1];    // 将byteArr[1]指针赋值给pHearder头指针
                headerPtr[0] = arrLength[i];
                headerPtr[1] = calcMinimum(arrLength[i], floatArr[i]);
                headerPtr[2] = calcMaximum(arrLength[i], floatArr[i]);
                // 保存byte数组压缩的数据
                for ( int j = 0; j < arrLength[i]; ++j )
                {
                    byteArr[1+HEADER_LENGTH+j] = calcMappedData(floatArr[i][j], headerPtr[1], headerPtr[2]);
                }
            }
            // 将byte数组的元素写入到文件中
            sprintf(fileName, "./compressedFiles/chip%03d", i);
            exportData(fileName, byteArr, 1+HEADER_LENGTH+arrLength[i]);
            // 释放开辟内存空间
            free(byteArr);
            byteArr = NULL;
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //1.2 如果循环到最后一个还存在小于4096字节的数组未压缩，则压缩此数组
            if ( arrTotalLength > 0 && arrTotalLength < COMPRESSION_LIMIT && i == FLOAT_ARR_NUMBER - 1 )
            {
                byteArr = malloc(1 + HEADER_LENGTH * compressionNumber + arrTotalLength);

                if ( byteArr != NULL )
                {
                    byteArr[0] = compressionNumber;
                    headerPtr = &byteArr[1];
                    headerPtr[0] = arrLength[index];
                    headerPtr[1] = calcMinimum(arrLength[index], floatArr[index]);
                    headerPtr[2] = calcMaximum(arrLength[index], floatArr[index]);
                    for ( int j = 0; j < arrLength[index]; ++j )
                    {
                        byteArr[1+HEADER_LENGTH+j] = calcMappedData(floatArr[index][j], headerPtr[1], headerPtr[2]);
                    }
                }
                sprintf(fileName, "./compressedFiles/chip%03d", index);
                exportData(fileName, byteArr, 1+HEADER_LENGTH*compressionNumber+arrTotalLength);

                free(byteArr);
                byteArr = NULL;
            }
            continue;       // 进入下一次循环
        }
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.当数组长度小于4096时
        else if ( arrLength[i] < COMPRESSION_LIMIT )
        {
            arrTotalLength += arrLength[i];             // 累加拼接的数组总长度
            compressionNumber ++;                       // 压缩的个数加1
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //2.1 如果累加后的总长度仍小于4096
            if ( arrTotalLength < COMPRESSION_LIMIT )
            {
                index = i;    // 保存第一个进来的数组长度索引
                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //2.1.1 如果是最后一个长度小于4096的数组未压缩，则压缩此数组
                if ( i == FLOAT_ARR_NUMBER - 1 )
                {
                    byteArr = malloc(1 + HEADER_LENGTH * compressionNumber + arrTotalLength);

                    if ( byteArr != NULL )
                    {
                        byteArr[0] = compressionNumber;
                        headerPtr = &byteArr[1];
                        headerPtr[0] = arrLength[index];
                        headerPtr[1] = calcMinimum(arrLength[index], floatArr[index]);
                        headerPtr[2] = calcMaximum(arrLength[index], floatArr[index]);
                        for ( int j = 0; j < arrLength[index]; ++j )
                        {
                            byteArr[1+HEADER_LENGTH+j] = calcMappedData(floatArr[index][j], headerPtr[1], headerPtr[2]);
                        }
                    }
                    sprintf(fileName, "./compressedFiles/chip%03d", index);
                    exportData(fileName, byteArr, 1+HEADER_LENGTH*compressionNumber+arrTotalLength);

                    free(byteArr);
                    byteArr = NULL;
                }
            }
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //2.2 如果累加后总长度大于等于4096，则一起压缩这两个数组
            else if ( arrTotalLength >= COMPRESSION_LIMIT )
            {
                byteArr = malloc(1 + HEADER_LENGTH * compressionNumber + arrTotalLength);
                if ( byteArr != NULL )
                {
                    //>>>-------------------------------------------------------------------------------------------------------------------------------------
                    //2.2.1 压缩第一个数组
                    byteArr[0] = compressionNumber;
                    headerPtr = &byteArr[1];
                    headerPtr[0] = arrLength[index];
                    headerPtr[1] = calcMinimum(arrLength[index], floatArr[index]);
                    headerPtr[2] = calcMaximum(arrLength[index], floatArr[index]);
                    for ( int j = 0; j < arrLength[index]; ++j )
                    {
                        byteArr[1+HEADER_LENGTH+j] = calcMappedData(floatArr[index][j], headerPtr[1], headerPtr[2]);
                    }
                    //>>>-------------------------------------------------------------------------------------------------------------------------------------
                    //2.2.2 压缩第二个数组
                    headerPtr = &byteArr[1+HEADER_LENGTH+arrLength[index]];
                    headerPtr[0] = arrLength[i];
                    headerPtr[1] = calcMinimum(arrLength[i], floatArr[i]);
                    headerPtr[2] = calcMaximum(arrLength[i], floatArr[i]);
                    for ( int j = 0; j < arrLength[i]; ++j )
                    {
                        byteArr[1+HEADER_LENGTH*compressionNumber+arrLength[index]+j] = calcMappedData(floatArr[i][j], headerPtr[1], headerPtr[2]);
                    }
                }
                sprintf(fileName, "./compressedFiles/chip%03d_chip%03d", index, i);
                exportData(fileName, byteArr, 1+HEADER_LENGTH*compressionNumber+arrTotalLength);

                arrTotalLength = 0;         // 将累加的数组总长度置为0
                compressionNumber = 0;      // 将每个byte数组压缩的个数置为0

                free(byteArr);
                byteArr = NULL;
            }
        }
    }
}

/*
*  @brief 导出数据，将数据写入到文件中
*  @param *fileName为写入的文件名
*         *byteArr为byte数组头指针
*         byteArrLength为byte数组的长度
*  @return N/A
*/
void exportData(char *fileName,unsigned char *byteArr,int byteArrLength)
{
    int fd = open(fileName, O_WRONLY | O_CREAT,0777);
    write(fd, byteArr, byteArrLength);
    close(fd);
}

/*
*  @brief 解压文件中的数据
*  @param *arrLength为数组长度头指针
*         **pDecompressedArr为指向解压后的数组指针的指针
*  @return
*/
void decompress(int *newArrLength, float **newFloatArr)
{
    DIR *pDir;
    char path[50];                             // 打开文件的路径
    struct dirent *file;
    char dirname[20] = "./compressedFiles";    // 目录的名字
    unsigned char newByteArr[10000];           // 存放文件中数据的数组
    int arrIndex = 0;                          // 数组索引
    int firstArrIndex = 0;                     // 第一个数组的索引

    pDir = opendir(dirname);                    // 打开目录

    // 逐个读取目录下的文件
    while( (file = readdir(pDir)) != NULL )
    {
        // 排除"."或".."之类的隐藏目录
        if(strncmp(file->d_name, ".", 1) == 0)
        {
            continue;
        }
        // 通过文件名生成打开文件的路径
        sprintf(path,"./compressedFiles/%s",file->d_name);

        // 打开文件
        int f=open(path, O_RDONLY, 10000);

        if ( f != -1 )
        {
            // 读取文件
            int i = read(f, newByteArr, 10000);
            if( i > 0 )
            {
                short *pHeader;                              // 表头的头指针
                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //1 如果读取的文件名长度为7,直接解压该数组
                if (strlen(file->d_name) == 7)
                {
                    // 计算文件的索引号
                    arrIndex = 100 * (file->d_name[4] - '0') + 10 * (file->d_name[5] - '0') + (file->d_name[6] - '0');

                    // 将byteArr头指针赋值给pHearder头指针
                    pHeader = &newByteArr[1];

                    newArrLength[arrIndex] = pHeader[0];     // 获得数组长度
                    int minimum = pHeader[1];                // 获得数组元素最小值
                    int maximum = pHeader[2];                // 获得数组元素最大值

                    newFloatArr[arrIndex] = malloc(sizeof(float) * newArrLength[arrIndex]);
                    if ( newFloatArr[arrIndex] != NULL )
                    {
                        // 解压缩byte数组中的数据
                        for (int j = 0; j < newArrLength[arrIndex]; ++j)
                        {
                            newFloatArr[arrIndex][j] = calcDecompressedData((float)(newByteArr[1+HEADER_LENGTH+j]),minimum,maximum);
                        }
                    }
                }
                //>>>-------------------------------------------------------------------------------------------------------------------------------------
                //2 如果读取的文件名为拼接成的
                else
                {
                    //>>>-------------------------------------------------------------------------------------------------------------------------------------
                    //2.1 计算文件中第一个数组的编号
                    arrIndex = 100 * (file->d_name[4] - '0') + 10 * (file->d_name[5] - '0') + (file->d_name[6] - '0');

                    // 将byteArr头指针赋值给pHearder头指针
                    pHeader = &newByteArr[1];

                    newArrLength[arrIndex] = pHeader[0];     // 获得数组长度
                    int minimum = pHeader[1];                // 获得数组元素最小值
                    int maximum = pHeader[2];                // 获得数组元素最大值

                    newFloatArr[arrIndex] = malloc(sizeof(float) * newArrLength[arrIndex]);
                    if ( newFloatArr[arrIndex] != NULL )
                    {
                        // 解压缩byte数组中的数据
                        for (int j = 0; j < newArrLength[arrIndex]; ++j)
                        {
                            newFloatArr[arrIndex][j] = calcDecompressedData((float)(newByteArr[1+HEADER_LENGTH + j]),minimum,maximum);
                        }
                    }
                    //>>>-------------------------------------------------------------------------------------------------------------------------------------
                    //2.2 计算文件中第二个数组的编号
                    firstArrIndex = arrIndex;       // 保存第一个数组的索引号，用于取第一个数组的长度

                    arrIndex = 100 * (file->d_name[12] - '0') + 10 * (file->d_name[13] - '0') + (file->d_name[14] - '0');

                    // 将byteArr头指针赋值给pHearder头指针
                    pHeader = &newByteArr[1+HEADER_LENGTH+newArrLength[firstArrIndex]];

                    newArrLength[arrIndex] = pHeader[0];   // 获得数组长度
                    minimum = pHeader[1];                  // 获得数组元素最小值
                    maximum = pHeader[2];                  // 获得数组元素最大值

                    newFloatArr[arrIndex] = malloc(sizeof(float) * newArrLength[arrIndex]);
                    if ( newFloatArr[arrIndex] != NULL )
                    {
                        // 解压缩byte数组中的数据
                        for (int j = 0; j < newArrLength[arrIndex]; ++j)
                        {
                            newFloatArr[arrIndex][j] = calcDecompressedData((float)(newByteArr[1+HEADER_LENGTH*2+newArrLength[firstArrIndex]+j]),minimum,maximum);
                        }
                    }
                }
            }
        }
    }
    // 关闭目录
    closedir(pDir);
}

/*
*  @brief   生成两个float数组的数据差值并存到文件中
*  @param   *arrLength为数组长度头指针
*           **float为指向原float数组指针的指针
*           **newFloatArr为指向解压后的新float数组指针的指针
*  @return  N/A
*/
void calcDataDiff(int *arrLength, float **floatArr,float **newFloatArr)
{
    char path[50];
    float diffValue;                    // 差值

    mkdir("dataDiffValue",0777);        // 创建目录

    for( int i = 0; i < FLOAT_ARR_NUMBER; ++i )
    {
        // 更新文件名字符串
        sprintf(path, "./dataDiffValue/chip%03d_diff", i);
        // 将结果写入文件：
        FILE *pFile = NULL;
        // 打开文件，若不存在则创建：
        pFile = fopen( path, "a" );

        for( int j = 0; j < arrLength[i]; ++j )
        {
            // 计算差值
            diffValue = floatArr[i][j] - newFloatArr[i][j];
            // 将差值结果写入文件
            fprintf(pFile, "  %.2f\n", diffValue);
        }
        // 关闭文件
        fclose(pFile);
    }
}

int main()
{
    int *arrLength;                 // 声明整形指针变量
    float **floatArr;               // 声明float型双重指针变量
    // 在内存中开辟数组个数所需的内存空间，并将首地址赋值给arrLength
    arrLength = malloc(sizeof(int) * FLOAT_ARR_NUMBER);
    // 在内存中开辟数组个数所需的内存空间，并将首地址赋值给floatArr
    floatArr = malloc(sizeof(int *) * FLOAT_ARR_NUMBER);

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //1. 生成数据
    generateData(arrLength, floatArr);
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //2. 压缩数据并写到文件中
    compress(arrLength, floatArr);

    int *newArrLength;
    float **newFloatArr;
    newArrLength = malloc(sizeof(int) * FLOAT_ARR_NUMBER);
    newFloatArr = malloc(sizeof(int *) * FLOAT_ARR_NUMBER);

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //3. 解压数据
    decompress(newArrLength, newFloatArr);

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //4. 计算源数据与解压后数据的差值
    calcDataDiff(arrLength,floatArr,newFloatArr);

    //释放申请的内存空间
    for ( int i = 0; i < FLOAT_ARR_NUMBER; ++i )
    {
        free(floatArr[i]);
        floatArr[i] = NULL;
        free(newFloatArr[i]);
        newFloatArr[i] = NULL;
    }

    free(arrLength);
    arrLength = NULL;

    free(floatArr);
    floatArr = NULL;

    free(newArrLength);
    newArrLength = NULL;

    free(newFloatArr);
    newFloatArr = NULL;

    return 0;
}

