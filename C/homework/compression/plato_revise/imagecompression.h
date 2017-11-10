#ifndef IMAGECOMPRESSION_H
#define IMAGECOMPRESSION_H

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//plato171110 常量定义
#define COMPRESSION_LIMIT 4096           // 压缩数据包的阀值，即超过此值直接压缩
//rime 叫第一/第二部分肯定不明白是啥意思, 需要把具体的内容命名
#define FIRST_HEADER_LENGTH 1            // 表头第一部分长度，存放一次压缩的数组个数
#define SECOND_HEADER_LENGTH 6           // 表头第二部分长度，存放长度，最大值，最小值
#define COMPRESSION_DIR "./compressionData"   // 压缩数据目录，用于存放压缩后的文件
//rime 既然都叫diff了, 为什么又来check了
#define DATA_DIFF_DIR "./checkData"           // 验证数据目录，用于存放数据差值的文件
//rime 这哪里是fileName啊, 这是fileName的格式定义
#define COMPRESSION_FILENAME "chip%03d"       // 压缩后的文件名 //rime file和name是两个单词
#define DIFF_VALUE_FILENAME "chip%03d_diff"   // 数据差值文件名 //rime 不需要Value,加了个Value反而不好
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//plato171110 1 压缩部分的函数声明

/*
*  @brief 压缩数据到动态内存空间
*  @param pFloatData: 要压缩的float数据指针
*         pArrLength: 数组长度指针
*  @return N/A
*/
void compressData(float *pFloatData,
                  short *pArrLength);

//rime 这种最好是需要把压缩的格式再讲解下6
/*
*  @brief 计算压缩后的数据
*  @param pFloatData: 待压缩的float数据指针
*         arrLength: pFloatData中每个数组的长度
*         pByteData： 压缩后的byte数据指针
*  @return N/A
*/  //rime 压缩就压缩, 为什么计算压缩后的数据, calc没必要,
void calcCompressedData(float *pFloatData,
                        short arrLength,
                        unsigned char *pByteData);//rime Byte不需要加, 如果代表压缩后的数据, 可以用compressedData/destData

/*
*  @brief 将byte数组以二进制的形式写入文件中保存
*  @param pfilename：文件名指针 //rime N要大写
*         pByteData：要写入的数据源
*         dataLength：写入数据的长度
*  @return N/A
*/
void writeDataToFile(char *pFilename,
                     unsigned char *pByteData, //rime Byte不需要, 在不会引起混淆的前提下, 命名越短越好, 尤其是这种参数类型都能够明确知道的情况下
                     int dataLength);
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//plato171110 2 解压缩部分的函数声明

/*
*  @brief 把数据从文本中读出来还原数据，求与原始数据的差值并存入文件中
*  @param pFloatData：原始生成的数据
*         pArrLength：数组长度
*  @return N/A
*///rime 不符合要求, 要求差值文件单独计算的
void decompressData(float *pFloatData,
                    short *pArrLength);

/*
*  @brief 计算解压缩后的数据
*  @param pHeader: 表头指针指针，用于提取数组长度和最小值  //rime 这种注释啥意思, 指针指针
*         pNewFloatData: 解压缩后的新的float数据
*         pOrigByteData: 原始byte数据指针
*  @return N/A
*/
void calcDecompressedData(short *pHeader,
                          float *pNewFloatData,
                          unsigned char *pOrigByteData);

/*
*  @brief 生成两个float数组的数据差值并存到文件中
*  @param filenameNumber: 文件名数字部分    //rime 这种命名谁能看得懂,
*         origLength: 原始数组长度
*         pArrLength: 数组长度指针
*         origData: 原始数据指针
*         newData: 解压后的新数据指针
*  @return N/A
*/
void calcDiffAndWriteToFile(int filenameNumber,
                            int origLength,
                            short *pArrLength,
                            float *origData,
                            float *newData);
//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#endif // IMAGECOMPRESSION_H
