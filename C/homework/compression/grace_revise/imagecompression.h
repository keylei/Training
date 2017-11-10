#ifndef IMAGECOMPRESSION_H
#define IMAGECOMPRESSION_H

//rime 请不要在一份代码中,一会用image, 一会用img
/*
*  @brief 压缩一张照片成 byte 数组（数据0-255）
*         表头第一位存放图片个数  //rime +1 这里把压缩的格式又讲了一遍, 很好
*         第二三位存放数组长度
*         第四五位存放数组最小值
*         第六七位存放数组最大值
*         后面跟数据直到第二张图片的信息（最小值,最大值,数据）
*  @param pCompressedArr:压缩后的数组
*         pOrigData:未压缩的数组数据
*         pImgLen:图像长度
*         compressionImgCnt:压缩的图片数(1:一张图片，2：两张图片)
*         heightMin:图像高度最小值
*         heightMax:图像高度最大值
*  @return NA
*/
void compressOneImg(unsigned char* pCompressedArr,
                     float* pOrigData[],
                     int* pImgLen,
                     int compressionImgCnt,
                     int heightMin,
                     int heightMax);

/*
 * //rime 这种最好是需要把压缩的格式再讲解下
*  @brief 把 imgCnt 个图片高度数据压缩成 byte 数据
*  @param imgCnt:图片个数 //rime 请问哪里来的imgCnt
*         pImgLen:图像长度
*         pImgHight：图片高度//rime 哪里来的pImgHight,是pArrHeightCanvas对把
*         pDirPath：压缩数据所在的目录路径
*         maxImgPixelCnt:图片最大的像素点数量   //rime 这里之前讲过的, 图像数组直接用长度就好了, 不要用pixelCnt
*         heightMin:图像高度最小值
*         heightMax:图像高度最大值
*  @return NA
*/
//rime 这里的Img应该复数才对呀
void compressAllImg(int arrCount,
                      int *pixelCntArr,
                      float* pArrHeight,
                      char* pDirPath,
                      int maxImgPixelCnt,
                      int heightMin,
                      int heightMax);

/*
*  @brief 解压缩图像文件  //rime+1 这种使用1,2,3...标题把函数处理步骤写清楚是比较好的
*         1.把所有解压的数据存到一个数组中
*         2.记录读取文件的顺序
*  @param maxDataCount：数组数据的最大数量 5000
*         pDirPath：压缩数据的目录
*         pImgOffset：记录读取文件的顺序
*         imgCount：图像数量
*  @return 返回解压数组的头指针
*/
float* decompressImage(int maxDataCount,//rime 为什么有写是Count/有些是Cnt
                       char* pDirPath,
                       int* pImgOffset,
                       int imgCount);

/*
*  @brief 计算差值
*  @param pImgHeight：图像高度
*         pDecompressImgHeight：解压的图像高度//rime 和形参又不对应,这种细节错误很多, 交不前请检查一遍
*         readFileIdx：读文件的索引（求数据偏移时用到）  //rime 指针为什么不写p了
*         imgCnt：图片数量  //rime  和行参又不对应
*         pDiffDirPath：差值文件所在目录
*         imgLen:图片长度
*  @return NA
*/
void calcDiff(float* pImgHeight,
              float* pDpresImgHeight,
              int* readFileIdx,
              int imgCount,
              char* pDiffDirPath,
              int* imgLen);

#endif // IMAGECOMPRESSION_H
