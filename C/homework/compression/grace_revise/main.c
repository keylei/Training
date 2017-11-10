/**
 *  @brief 图像压缩算法    //grace171108 增加项目说明
 *         1.数据生成：创建1000个float数组，长度从2048到5000随机生成，数据范围从0.00-5000.00随机生成
 *         2.压缩：数组长度大于4096直接压缩，否则找下一个长度小于4096的数组合并压缩，压缩成byte数组
 *         3.解压：把byte数组还原成浮点数数组
 *         4.求差值：计算生成的原始数据与还原数据的差值
 *
 *  @author create by peter ,comment by grace
 *  @version 1.00 2017-11-08 author
 *                note:create it
 */

#include "datageneration.h"
#include "imagecompression.h"
#include "iohelper.h"        //grace171108 增加region/subregion
//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//常量宏定义
#define IMG_CNT      1000   //图片数量
#define MAX_HEIGHT   5000   //图片最大高度  //rime 为什么有些加了IMG前缀, 有些没有加, 依据是什么
#define MIN_HEIGHT   0      //图片最小高度
#define IMG_MAX_LEN  5000   //图片最长的长度
#define IMG_MIN_LEN  2048   //图片最短的长度

#define COMPRESS_DATA_DIR_PATH "./data/" //压缩数据文件所在的目录
#define DIFF_DATA_DIR_PATH     "./diff/" //差值文件所在的目录

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
*  @brief 主函数，调用其他函数实现项目功能
*  @param NA
*  @return NA
*/
int main()
{
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //1.删除原来目录，创建新目录
    removeDir(COMPRESS_DATA_DIR_PATH);   //删除./data/目录
    removeDir(DIFF_DATA_DIR_PATH);       //删除./diff/目录
    mkdir(COMPRESS_DATA_DIR_PATH,0777);  //创建压缩数据文件所在的目录
    mkdir(DIFF_DATA_DIR_PATH,0777);      //创建差值文件所在的目录
    //rime region之间最好加一个空行, 好阅读
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //2.变量定义
    float *pImgHeight;          //图片高度 //rime 这个命名不好, 下面既然加上了Decompress作为定语, 那么上面也需要进行对仗, 可以使用原始数据(orig)/需要压缩的数据(compressing)/生成的数据(generation)
    float *pDecompressImgHeight;//解压的图片高度
    int imgLen[IMG_CNT];        //每张照片的长度 //rime 这个数组怎么又不加arr了?
    int *pFileIdx = malloc(sizeof(int) * IMG_CNT); //文件名（数字） //改  //rime 完全看不出来是文件名的意思, 更新文件索引
    if(pFileIdx == NULL)  //grace171108 增加内存开辟失败情况
    {
        perror("pFileIdx指针内存开辟失败！");
        exit(0);
    }
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //3.函数调用
    //3.1生成数据
    pImgHeight = generateHighData(imgLen,
                                  MAX_HEIGHT,
                                  MIN_HEIGHT,
                                  IMG_MAX_LEN,
                                  IMG_MIN_LEN,
                                  IMG_CNT);
    //3.2压缩数据
    compressAllImg(IMG_CNT,
                   imgLen,
                   pImgHeight,
                   COMPRESS_DATA_DIR_PATH,
                   IMG_MAX_LEN,
                   MIN_HEIGHT,
                   MAX_HEIGHT);
    //3.3解压数据
    pDecompressImgHeight = decompressImage(IMG_MAX_LEN,
                                           COMPRESS_DATA_DIR_PATH,
                                           pFileIdx,
                                           IMG_CNT);
    //3.4计算差值
    calcDiff(pImgHeight,
             pDecompressImgHeight,
             pFileIdx,
             IMG_CNT,
             DIFF_DATA_DIR_PATH,
             imgLen);
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //4.释放指针
    free(pImgHeight);
    pImgHeight = NULL;
    free(pDecompressImgHeight);
    pDecompressImgHeight = NULL;
    free(pFileIdx);
    pFileIdx = NULL;

    return 0;
}

