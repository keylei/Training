/*
实现一个图像压缩的算法（这里需要前提介绍下图像的基础知识: 8位灰度图像，bitmap,png,jpg）rime 你在注释里写这个干啥
- 1.创建1000个float数组，长度从2048到5000随机生成，数据范围从0.00-5000.00随机生成    rime 注释的版面太乱, 你就算抄也注意下阅读性啊
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

//rime 为什么整个项目中没有类似与readme这样的一个文件

//rime +1 整个项目比较统一, 没有出现data和image混用的情况, 基本坚持了全部是data

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

//rime +1 这里把头文件进行了分类, 值得表扬
#include "config"                   // 配置文件，存放一些可改动的参数
#include "datahelper.h"             // 一些范用的函数在这 //rime 范用 -> 泛用
#include "datageneration.h"         // 生成数据的函数在这
#include "datacompression.h"        // 除了生成数据之外的功能模块函数都在这

//lynn:171030 所有函数的声明全都按照功能加到了头文件中，并将函数实现加到了对应的源文件中。
//            将函数说明加到了头文件中，函数实现的地方去除了函数说明。


/*
*  @brief   函数入口，负责调用各功能模块函数
*  @param   N/A
*  @return  返回值为1表示正常退出
*           返回值为0表示错误退出
*/
int main()
{
    //rime 为什么同一份代码中, 有地方是len, 有地方是length
    int lengthArr[FLOAT_ARR_CNT];// 存放数组长度的数组

    //lynn171101:a. 这里直接用数组即可，没必要跑到堆上去开一片空间，意义不大，影响效率
    //           b. 将arrLength改为lenArr,此处表示的是一个数组,arrLength更像个变量
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //1. 生成数据：
    float **pGenerationData;     // 指向生成数据的指针(数据为多个数组，故需用二维指针)

    //  1.1开辟用于保存所有数组头指针用的空间:
    //lynn 171030 :sizeof里面的类型从int改为了int*，(此处为rime制造的bug修改)
    pGenerationData = malloc(sizeof(int* ) * FLOAT_ARR_CNT);
    if(NULL == pGenerationData)  // 若此处内存开辟失败，程序无法正常执行，直接退出程序
    {
        printf("生成数据内存开辟失败");
        return 0;
    }

    //  1.2调用生成数据函数
    generateRandomData(lengthArr, pGenerationData);

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //2. 压缩数据并导出到文件：
    compressAndExportData(lengthArr, pGenerationData);

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //3. 解压数据：
    float **pDecompressionData; // 指向解压出数据的指针(数据为多个数组，故需用二维指针)

    //  3.1开辟用于保存所有数组头指针用的空间
    pDecompressionData = malloc(sizeof(int *) * FLOAT_ARR_CNT);
    if(NULL == pDecompressionData)  // 若此处内存开辟失败，程序无法正常执行，直接退出程序
    {
        printf("生成数据内存开辟失败");
        return 0;
    }

    //  3.2调用解压缩数据函数
    importAndDecompressData(lengthArr, pDecompressionData);

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //4. 计算源数据与解压后数据的差值：
    calcDataDiff(lengthArr,pGenerationData,pDecompressionData);

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    //5. 释放申请的内存空间：
    dispose(pGenerationData,pDecompressionData);

    return 1;
}
