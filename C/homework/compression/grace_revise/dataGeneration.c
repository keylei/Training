/**
 *  @brief 一次生成所有数据             //grace171108 增加文件说明
 *         1.随机生成数组长度
 *         2.随机生成所有数组的数据
 *
 *  @author create by peter comment by grace
 *  @version 1.00 2017-11-08 author
 *                note:create it
 */
#include "datageneration.h"

float* generateHighData(int* pImgLen,  //grace171108 之前函数是void*(无返回值)，现在改为返回值float*
                        int maxHeight, //grace171108 高度最大最小值，图片长度最大最小值做为参数传进，之前是在函数内定义
                        int minHeight, //grace171108 之前参数length现改为imgCnt //rime 注释对应不到真实对应的参数
                        int maxImgLen,
                        int minImgLen,
                        int imgCnt)
{
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //step1:随机生成每张图片的大小
    srand(time(NULL));
    float* pHeightData = NULL;               //存放图片高度数据
    int imgSize = 0;                         //记录所有图像大小
    for ( int i = 0; i < imgCnt; ++i )       //随机生成图像大小
    {
        pImgLen[i] = rand() % (maxImgLen - minImgLen + 1) + minImgLen;
        imgSize += pImgLen[i];               //累加每次生成的像素点个数
    }
    pHeightData = malloc( sizeof(float) * imgSize );
    if(pHeightData == NULL)            //grace171108 增加开辟内存失败情况判断
    {
        perror("pHeightData指针内存开辟失败");
        exit(0);
    }
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //step2:一次随机生成所有图片上的像素点数量
    for(int i = 0; i < imgSize; ++i)
    {
        *(pHeightData+i) = (float)(rand()%(100*(maxHeight-minHeight)+1))/100 + minHeight;
    }
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //step3:返回所有的图片高度数据
    return pHeightData;
}
