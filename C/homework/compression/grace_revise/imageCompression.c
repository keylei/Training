/**
 *  @brief 本文件有4个函数构成
 *         1.compressOneImg函数：压缩一张图片（数据类型float->byte）
 *         2.compressAllImg函数：压缩所有图片
 *         3.decompressImage函数：解压缩函数（数据类型byte->float）
 *         4.calcDiff函数：计算原始生成数据与解压数据的差值（即精度损失）
 *
 *  @author create by peter comment by grace
 *  @version 1.00 2017-11-08 author
 *                note:create it
 */
#include "imagecompression.h"
#include "iohelper.h"

#define PKG_IMG_CNT       1     //每个压缩包所含图片数量   //grace171108 增加常量宏定义之前是用魔数
#define PKG_HEAD_LENGTH   6     //每个压缩包表头长度所占字节（图片大小,像素最小值,像素最大值）
#define MERGE_THRESHOLD   4096  //图片压缩合并的阈值(每张图片大小大于4096即进行压缩)

void compressOneImg( unsigned char* pCompressedArr,  //grace171108 pCompressedArr代替byteArray
                     float* pOrigData[],             //grace171108 图片最小值最大值作为参数传入，之前是函数内定义的变量
                     int* pImgLen,                   //grace171108 compressionImgCnt（n+n）代替compressPicCnt（v+n）
                     int compressionImgCnt,
                     int heightMin,
                     int heightMax)
{
    int idxPos = 1;  //声明byte数组标志位，定义为1是因为byte[0]存放了图像数量
    *(pCompressedArr+0) = compressionImgCnt;      //将图像数放入byte数组第一位
    for ( int i = 0; i < compressionImgCnt; ++i ) //轮循每张图片
    {
        idxPos += 6; //将byte数组索引移动到表头后  //rime 既然已经定义了宏常量, 这里为什么又写死了
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step1:读取 byte 数组表头数据（图片长度，高度最大值，高度最小值）
        for ( int j = 0; j < pImgLen[i]; ++j )
        {
            if(heightMin >= *(pOrigData[i]+j)) heightMin = *(pOrigData[i]+j);   //找高度最小值
            if(heightMax <= *(pOrigData[i]+j)) heightMax = *(pOrigData[i]+j);   //找高度最大值
        }
        *(pCompressedArr+idxPos-6) = pImgLen[i] >> 8;     //图片长度高位
        *(pCompressedArr+idxPos-5) = pImgLen[i];          //图片长度低位
        *(pCompressedArr+idxPos-4) = heightMin >> 8;      //最小值高位
        *(pCompressedArr+idxPos-3) = heightMin;           //最小值低位
        *(pCompressedArr+idxPos-2) = heightMax >> 8;      //最大值高位
        *(pCompressedArr+idxPos-1) = heightMax;           //最大值低位
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step2:将图像高度压缩到 byte 数组
        for ( int j = 0; j < pImgLen[i]; ++j)
        {
            *(pCompressedArr+idxPos+j) = (*(pOrigData[i]+j)-heightMin)*255/(heightMax-heightMin);
        }

        idxPos += pImgLen[i]; //将byte数组索引移动到下一张图片
    }
}

void compressAllImg(int imgCnt,       //grace171108 把这个函数从main()函数中拆出来
                    int* pImgLen,
                    float* pImgHight,
                    char* pDirPath,
                    int maxImgPixelCnt,
                    int heightMin,
                    int heightMax)
{
    //rime +1 直接使用标准库中的FILENAME_MAX, 值得鼓励
    char outputName[FILENAME_MAX];              //确认压缩图像并导出的文件名    //grace171108 FILENAME_MAX代替40（尽量少用魔数）
    char curOutputName[FILENAME_MAX];           //当前待压缩的数组导出文件名，如果压缩一张图片curOutputName是输出的文件名，如果是两张图片需要拼接作为文件名  //grace171108 FILENAME_MAX代替20
    //rime has表示已经完成的, 所以需要使用过去完成时, 怎么可以还是进行时态呢
    int hasCompressingImg = 1;                  //判断是否含有待压缩数组，有两个值：1.表示没有 0.表示有  //grace171108 hasCompressingImg代替isCompressed
    int byteLen;                                //声明压缩成 byte 数组长度
    int curArrLen = 1;                          //当前数组长度(含表头)
    int imgIdx = 0;                             //当前待压缩图像在内存中的索引
    //rime 如果要表示待压缩的意思, 最好使用compressing
    int compressionImgCnt;                      //待压缩的图片数量      //grace171108 compressionImgCnt代替compressPicCnt(下面compress有关变量名改为compression)
   //rime 这里需要解释一下为什么为2,这是一个魔数
    int compressionImgLen[2];                   //待压缩的每张图像的长度
    int curImgLen[1];                           //当前图像的长度
    float *pCompressionImgAddr[2];              //待压缩的每张图像的地址 //grace171108 pCompressionImgAddr代替compressPicPtr
    float *pCurImgAddr[1];                      //当前图像的地址       //grace171108 pCurImgAddr代替currentPicPtr
    int byteSize = maxImgPixelCnt*2+PKG_IMG_CNT+PKG_HEAD_LENGTH*2; //压缩成的 byte 数组的大小  //grace171108 byteSize代替8192
    unsigned char *pCompressionByte = malloc(byteSize); //压缩数据存到 pCompressionByte 数组
    if(pCompressionByte == NULL)
    {
        perror("pCompressionByte指针开辟内存失败");
        exit(0);
    }

    for ( int i = 0; i < imgCnt; ++i )              //轮循每张图片
    {
        curArrLen += PKG_HEAD_LENGTH + pImgLen[i];  //数组长度+表头的6个字节+当前图片长度
        pCurImgAddr[0] = pImgHight + imgIdx;        //当前图片地址
        curImgLen[0] = pImgLen[i];                  //当前图片长度

        sprintf(curOutputName,"%schip%.3d",pDirPath,i); //保存图像的导出路径和文件名
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1.当图像长度 < 4096 找下一张图像长度小于 4096 的图片合并压缩
        if ( pImgLen[i] < MERGE_THRESHOLD )
        {
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //1.1没有待压缩的图片则记录此图片信息
            if ( 1 == hasCompressingImg )//判断是否有待压缩数组(1表示没有)
            {
                pCompressionImgAddr[0] = pCurImgAddr[0];
                compressionImgLen[0] = curImgLen[0];
                sprintf(outputName,"%s",curOutputName);
                byteLen = curArrLen;
                hasCompressingImg = 0;   //置0（表示有待压缩数组）
            }
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //1.2有待压缩的图片则合并压缩图片并导出到文件
            else
            {
                compressionImgCnt = 2;             //待压缩图片数量为2
                byteLen += curArrLen;
                pCompressionImgAddr[1] = pCurImgAddr[0];
                compressionImgLen[1] = curImgLen[0];
                compressOneImg(pCompressionByte,   //调用压缩函数，将图像信息压缩
                               pCompressionImgAddr,
                               compressionImgLen,
                               compressionImgCnt,
                               heightMin,
                               heightMax);
                sprintf(outputName,"%s_chip%.3d",outputName,i);
                writeToFile(outputName,        //调用写文件函数，将图像信息写入文件
                            pCompressionByte, //rime 既然有导出文件的部分, 为什么函数名中没有体现出来,建议命名compressAllImgsToFolder
                            byteLen);
                byteLen = 0;           //图片已压缩,将长度重置为1
                hasCompressingImg = 1; //置1(表示没有待压缩数组)
            }
        }
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.当图像长度大于等于 4096 直接压缩成 byte 数组
        else
        {
            compressionImgCnt = 1;                 //待压缩图片数量为1
            compressOneImg(pCompressionByte,       //调用压缩函数，将图像信息压缩
                           pCurImgAddr,
                           curImgLen,
                           compressionImgCnt,
                           heightMin,
                           heightMax);
            sprintf(curOutputName,"%s",curOutputName); //grace171108 文件名后.bin去掉
            writeToFile(curOutputName,         //调用写文件函数，将图像信息写入文件
                        pCompressionByte,
                        curArrLen);
        }
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //3.判断是最后一张图片，并且有待压缩数组（最后一张图片 < 4096），直接压缩
        if ( imgCnt-1 == i && 0 == hasCompressingImg )
        {
            compressionImgCnt = 1;                 //待压缩图片数量为1
            compressOneImg(pCompressionByte,       //调用压缩函数，将图像信息压缩
                           pCompressionImgAddr,
                           compressionImgLen,
                           compressionImgCnt,
                           heightMin,
                           heightMax);
            sprintf(outputName,"%s",outputName);
            writeToFile(outputName,            //调用导出函数，将图像信息导出
                        pCompressionByte,
                        byteLen);
        }
        curArrLen = 1;                         //图片已压缩,将长度重置为1
        imgIdx += pImgLen[i];                  //下一图像在内存中的索引
    }//END OF "for ( int i = 0; i < imgCnt; ++i )"

    free(pCompressionByte);                      //释放指针
    pCompressionByte = NULL;                     //将指针置为NULL
}

//rime 为什么image和img要混用
float* decompressImage(int maxDataCount,  //grace171108 从main()函数中拆出
                       char* pDirPath,
                       int* pImgOffset,
                       int imgCount)
{
    int dataOffset = 0;
    char fileName[FILENAME_MAX];                //待操作的文件名 //grace:FILENAME_MAX->40
    int fileDataOffset;                         //文件中数据的偏移量
    int curImgLen = 0;                          //当前图片的长度
    int readFileIdx = 0;                        //读取文件顺序 的索引
    int pixelCntMax;                            //最大像素数
    int pixelCntMin;                            //最小像素数
    int fileMaxSize = PKG_IMG_CNT + PKG_HEAD_LENGTH * 2 + MERGE_THRESHOLD * 2; //文件大小
    int *pFileData = malloc(sizeof(int) * fileMaxSize); //一个文件中所有数据
    if(pFileData == NULL)
    {
        perror("pFileData指针开辟内存失败");
        exit(0);
    }
    float *pDecompressImgHight = malloc(sizeof(float) * maxDataCount * imgCount); //存放文件中所有图片的高度值
    if(pDecompressImgHight == NULL)
    {
        perror("pDecompressImgHight指针开辟内存失败");
        exit(0);
    }
    DIR *dirPath;                            //待打开的目录 //rime 这里为什么不加p了
    struct dirent *filePath = NULL;          //待打开的文件路径//rime 和上面一样
    dirPath = opendir (pDirPath);            //找出目录中的文件

    if ( dirPath == NULL )                   //如果目录不存在，打印错误信息
    {
        perror ("Couldn't open the directory!");//rime 这里既然发生了异常, 就应该退出函数或者退出程序, 已经不能够再往下执行了
    }

    int idx = 0;                             //pImgOffset的索引
    while ( (filePath = readdir(dirPath)) != NULL ) //while循环读取目录中的文件名
    {
        //1.打开目录
        //如果是当前目录"."或上层目录".."则继续循环，否则向下执行程序
        if( strcmp(filePath->d_name,".") == 0 ||
            strcmp(filePath->d_name,"..") == 0 )
        {
            continue;
        }

        //2.读取每个文件中的数据
        sprintf(fileName,"%s%s",pDirPath,filePath->d_name); //将文件名加上路径，赋值给fileName
        readFromFile(pFileData,fileName); //调用函数，从文件中读数据

        //3.解压缩 byte 数组，把解压数据存到 pDecompressImgHight 数组中

        fileDataOffset = 1;  //文件中数据的偏移量置为1(第一位存放图像数）
        for ( int i = 0; i < *pFileData; ++i ) //*pFileData是压缩的图像数（1或2）
        {
            fileDataOffset += PKG_HEAD_LENGTH; //偏移量+6（表头）

            //3.1通过保存在表头中的值，算出像素点个数、最小/大值
            //rime 这里2是魔术, 如果觉得没有必要用变量(后面也是一样的), 那也注释一下, 不要觉得在一开始注释了, 就可以不用注释了, 在最近的地方注释永远是需要的,请牢牢记住, 阅读你代码的
            //        的人没有那么聪明, 不可能很快理解你写的是啥
            curImgLen = (*(pFileData+fileDataOffset-6)<<8)+*(pFileData+fileDataOffset-5);
            pixelCntMin = (*(pFileData+fileDataOffset-4)<<8)+*(pFileData+fileDataOffset-3);
            pixelCntMax = (*(pFileData+fileDataOffset-2)<<8)+*(pFileData+fileDataOffset-1);

            //3.2获取文件名中的数字，对应内存中相同位置的原数据
            readFileIdx = ( filePath->d_name[8*i+4] - '0' ) * 100 +
                    ( filePath->d_name[8*i+5] - '0' ) * 10  +
                    ( filePath->d_name[8*i+6] - '0' ) * 1;
            pImgOffset[idx++] = readFileIdx;

            //3.3轮循当前图片获取当前文件的解压数据
            for ( int j = 0; j < curImgLen; ++j )
            {
                *(pDecompressImgHight+j+dataOffset) = (float)(*(pFileData+fileDataOffset+j)) * ( pixelCntMax-pixelCntMin ) / 255.0 + pixelCntMin;
            }
            dataOffset += curImgLen;     //下次循环 pDecompressImgHight 数组的下标（存放解压数据的数组）
            fileDataOffset += curImgLen; //下次循环 pFileData 数组的下标（存放压缩数据的数组）
        }
    }//END OF "while ( (filePath = readdir(dirPath)) != NULL )"

    (void) closedir (dirPath);           //关闭文件夹

    free(pFileData);                     //释放指针
    pFileData = NULL;                    //置为NULL

    return pDecompressImgHight;
}

void calcDiff(float* pImgHeight,   //grace171108 从main()函数中拆出
              float* pDecompressImgHeight,
              int* readFileIdx,
              int imgCnt,
              char* pDiffDirPath,
              int* imgLen)
{
    float diff;                              //压缩数据与解压数据的差值
    int decompressOffset = 0;                //解压数据的偏移值
    char outputName[FILENAME_MAX];           //确认压缩图像并导出的文件名
    DIR *dirPath;                            //待打开的目录
    dirPath = opendir (pDiffDirPath);        //找出目录中的文件

    if ( dirPath == NULL )                   //如果目录不存在，打印错误信息
    {
        perror ("Directory open wrong!");
    }

    for (int i = 0; i < imgCnt; ++i)         //轮循 imgCnt 张图片解压
    {
        long int dataOffset = 0;             //原始数据数据的偏移值
        sprintf(outputName,"%schip%.3d_diff.txt",pDiffDirPath,readFileIdx[i]);
        FILE *diffFile = fopen(outputName, "w");
        if(diffFile == NULL)
        {
            perror("open file error!\n");    //打开失败，打印错误信息
            exit(0);
        }
        for (int j = 0; j < readFileIdx[i]; ++j)//计算原始数据的偏移
        {
            dataOffset += imgLen[j];
        }
        for (int j = 0; j < imgLen[readFileIdx[i]]; ++j) //readFileIdx[i]张图片上的高度数据存到文件中
        {
            diff = pImgHeight[dataOffset + j] - pDecompressImgHeight[decompressOffset + j];
            fprintf(diffFile,"%.2f\n",diff);
        }

        decompressOffset += imgLen[readFileIdx[i]];//计算解压数据的偏移
        fclose(diffFile);      //关闭文件
    }

    (void) closedir (dirPath); //关闭文件夹
}
