#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

//rime 常量的不同单词之间用_隔开
#define TOTALPICS 1000                          //所有照片数量

//rime 为什么注释没有内容
/**
 * @brief generalData
 * @param ptr
 * @param length
 * @return rime 返回值为什么要有*
 */
void *generalData( float *ptr, int length )//rime 对于形参，如果是传统的数组的话，直接用float[] 好一点
{
    srand( (unsigned)time( NULL ) );            //初始化随机数
    int min = 0;                                //高度的最小值
    int max = 5000;                             //高度的最大值
    float height = 0.0;                         //高度 //rime 请问这种注释的必要性

    for ( int i = 0; i < length; ++i )          //随机生成高度信息
    {
        height = (float)(rand()%(100*(max-min)+1))/100 + min;
        *(ptr+i) = height;
    }
    return 0;
}

/**
 * @brief compressArray
 * @param byteArray
 * @param picturePtr
 * @param pixelCountArray
 * @param compressPicCnt
 */
void compressArray( unsigned char *byteArray,//rime char compressedArr[] 或者 char* ptrCompressedArr
                    float *picturePtr[], //rime 图像请用image(缩写img)，picture还是倾向于肉眼直接可以看到的图像
                    int pixelCountArray[], //rime 直接图像长度就可以了，不要加个像素点数量
                    int compressPicCnt )//rime 这里表示名词，如果有v+n，adj+n，n+n，v+n优先级是最低的，所有这里叫compressedImgCnt
{
    int min = 5000;                             //设置高度最小值为5000 //rime 注意, 这里的5000和0都是魔数
    int max = 0;                                //设置高度最大值为0
    *(byteArray+0) = compressPicCnt;            //将图像数放入byte数组第一位
    //声明byte数组标志位，定义为1是因为byte[0]存放了图像数量
    int index = 1;
    for ( int i = 0; i < compressPicCnt; ++i )  //轮循每张图片
    {
        index += 6;                             //将byte数组索引移动到表头后
        //轮循当前图片像素点数组，读取每个像素点高度信息
        for ( int j = 0; j < pixelCountArray[i]; ++j )
        {
            if ( min >= *(picturePtr[i]+j) )    //高度是否小于min
            {
                min = *(picturePtr[i]+j);       //将较小的值赋给min
            }
            if ( max <= *(picturePtr[i]+j) )    //高度是否大于max
            {
                max = *(picturePtr[i]+j);       //将较大的值赋给max
            }
        }
        //像素点数组长度高位
        *(byteArray+index-6) = pixelCountArray[i] >> 8;
        //像素点数组长度低位
        *(byteArray+index-5) = pixelCountArray[i];
        *(byteArray+index-4) = min >> 8;        //最小值高位
        *(byteArray+index-3) = min;             //最小值低位
        *(byteArray+index-2) = max >> 8;        //最大值高位
        *(byteArray+index-1) = max;             //最大值低位

        //轮循当前像素点数组，读取每个像素点高度信息，并映射到0-255
        for ( int j = 0; j < pixelCountArray[i]; ++j)
        {
            //将当前像素点高度映射到0-255，并存入byte数组
            *(byteArray+index+j) = (*(picturePtr[i]+j)-min)*255/(max-min);
        }
        index += pixelCountArray[i];            //将byte数组索引移动到下一张图片
    }
}

/**
 * @brief exportToFile
 * @param outputName
 * @param byteArray
 * @param length
 */
void exportToFile( char* outputName,//rime 这里应该是导出的路径把，而不是文件名，函数用了export，也应该保持一致，这里怎么突然变成output了呢
                   unsigned char* byteArray,
                   int length )
{
    FILE *file = fopen( outputName, "w");       //打开文件，如果文件不存在则创建
    if ( file == NULL )
    {
        printf("open file error!\n");           //打开失败，打印错误信息
    }
    if (strstr(outputName, ".txt") == NULL)     //^^!=NULL means exist
     {
        //输出为二进制
         fwrite (byteArray , sizeof(unsigned char), length, file);
     }
    else
    {
        //输出为文本
        for ( int i = 0; i < length; ++i )          //轮循数组
        {
            fprintf(file,"%d\n",*(byteArray+i));    //将数组中的值输出的到文件中
        }
    }
    fclose(file);                                   //关闭打开的文件
}

/**
 * @brief main
 * @return
 */
int main()//rime 所有复杂的逻辑堆在一个函数中是不合适的，超过一屏就应该考虑是否可以剥离出来
{

    mkdir("./data",0777);
    mkdir("./diff",0777);
    srand( (unsigned)time( NULL ) );            //初始化随机数

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //peter171019 生成数据  //rime 最初的版本不需要写日期的，到后期修改再有必要加上，主要为了配合工作方便
    int min = 2048;                             //最少像素点个数  //rime 这里出现的数字都是魔数，需要用变量代替下
    int max = 5000;                             //最多像素点个数
    int pixelCount = 0;                         //总像素点个数 //rime 这里叫图像大小，数据长度都可以，叫像素个数不太何时
    int pixelCountArray[TOTALPICS];             //每张照片中像素点数量的数组
    float *picPtr = NULL; //rime 指针直接用p开头 pImgData
    for ( int i = 0; i < TOTALPICS; ++i )
    {
        //随机生成每张图片的像素点个数，存入数组
        pixelCountArray[i] = rand() % (max-min+1)+min;
        pixelCount += pixelCountArray[i];       //累加每次生成的像素点个数
    }
    //根据像素点总数分配内存
    picPtr = malloc( sizeof(float) * pixelCount );
    generalData(picPtr, pixelCount);            //调用函数生成每个像素点高度
    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //peter171019 压缩数据并导出为txt文件
    //malloc 8192字节的空间，存放待压缩的图像信息
    unsigned char *compressBytePtr = malloc(8192);

    char outputName[40];                        //确认压缩图像并导出的文件名
    char currentOutputName[20];                 //当前待压缩的数组导出文件名
    int isCompressed = 1;                       //判断是否含有待压缩数组 //rime 按照你注释的意思，应该叫hasCompressingArr才对呀

    int byteArrayLen = 0;                       //声明byte数组长度
    int currentArrayLen = 1;                    //当前数组长度(含表头) //rime Array->Arr,current->cur是常用缩写
    int pictureIndex = 0;                       //当前待压缩图像在内存中的索引
    int compressPicCnt;                         //待压缩的图片数量

    int compressPicLen[2];                      //待压缩的每张图像的像素点数
    int currentPicLen[1];                       //当前图像的像素点数
    float *compressPicPtr[2];                   //待压缩的每张图像的地址
    float *currentPicPtr[1];                    //当前图像的地址


    //rime 这层循环中，逻辑分支比较多的，请详细一开始就把逻辑注释清楚，同时在关键的
    //        判断表达式附近写上注释，如：
    //        1.当图像长度<4096
    //           ...
    //        2.当图像长度>=4096
    //          ...
    //如果{}离的比较远，为了增加可读性，还需要在}加上必要的说明，如
    //        if ( 1 == isCompressed )            //判断是否有待压缩数组(1表示没有)
    //       {
    //           ...(大量代码)
    //       }//end of  if ( 1 == isCompressed )

    for ( int i = 0; i < TOTALPICS; ++i )       //轮循每张图片
    {
        currentArrayLen += 6;                   //数组长度加上表头的6个字节
        currentArrayLen += pixelCountArray[i];  //数组长度加上当前图片像素点数

        currentPicPtr[0] = picPtr+pictureIndex; //当前图片地址
        currentPicLen[0] = pixelCountArray[i];  //当前图片像素点个数

        //待压缩图像的导出路径和文件名
        sprintf(currentOutputName,"./data/chip%.3d",i);
        if ( pixelCountArray[i] < 4096 )        //像素点数<4096,合并后再压缩
        {
            if ( 1 == isCompressed )            //判断是否有待压缩数组(1表示没有)
            {
                compressPicPtr[0] = currentPicPtr[0];
                compressPicLen[0] = currentPicLen[0];
                sprintf(outputName,"%s",currentOutputName);
                byteArrayLen = currentArrayLen;
                isCompressed = 0;               //标志位置位0（表示有待压缩数组）
            }
            else
            {
                compressPicCnt = 2;             //待压缩图片数量为2
                byteArrayLen += currentArrayLen;
                compressPicPtr[1] = currentPicPtr[0];
                compressPicLen[1] = currentPicLen[0];
                compressArray(compressBytePtr,  //调用压缩函数，将图像信息压缩
                              compressPicPtr,
                              compressPicLen,
                              compressPicCnt);
                sprintf(outputName,"%s_chip%.3d.bin",outputName,i);//rime 二进制文件并不是一定要加上.bin的，不管是linux还是win是中，二进制文件是默认不需要加bin后缀名的
                exportToFile(outputName,        //调用导出函数，将图像信息导出
                             compressBytePtr,
                             byteArrayLen);
                byteArrayLen = 0;               //图片已压缩,将长度重置为1
                isCompressed = 1;               //标志位置位1(表示没有待压缩数组)
            }

        }
        else                                    //像素点数>4096，直接压缩
        {
            compressPicCnt = 1;                 //待压缩图片数量为1
            compressArray(compressBytePtr,      //调用压缩函数，将图像信息压缩
                          currentPicPtr,
                          currentPicLen,
                          compressPicCnt);
            sprintf(currentOutputName,"%s.bin",currentOutputName);
            exportToFile(currentOutputName,     //调用导出函数，将图像信息导出
                         compressBytePtr,
                         currentArrayLen);
        }
        //判断是最后一张图片，并且有待压缩数组，直接压缩
        if ( TOTALPICS-1 == i && 0 == isCompressed )
        {
            compressPicCnt = 1;                 //待压缩图片数量为1
            compressArray(compressBytePtr,      //调用压缩函数，将图像信息压缩
                          compressPicPtr,
                          compressPicLen,
                          compressPicCnt);
            sprintf(outputName,"%s.bin",outputName);
            exportToFile(outputName,            //调用导出函数，将图像信息导出
                         compressBytePtr,
                         byteArrayLen);
        }
        currentArrayLen = 1;                    //图片已压缩,将长度重置为1
        pictureIndex += pixelCountArray[i];     //下一图像在内存中的索引
    }
    free(compressBytePtr);                      //释放指针
    compressBytePtr = NULL;                     //将指针置为NULL
    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //peter171023 读取数据并存入数组
    char fileName[40];                          //待操作的文件名
    int charValue;                              //文件中的值(高度值、最大/小值..)
    int pixelOffset;                            //文件中的值的偏移量
    int picPtrOffset;                           //当前的图片信息在内存中的偏移量
    int arrayLen = 0;                           //当前图片的长度
    int filenameNumber=0;                       //当前文件名中的数字 //rime filename是两个单词
    //开辟内存，存放读取到的文件中的每个值（图片数量，长度，最大/小值）
    int *arrayPtr = malloc(sizeof(int)*8192);  //rime arrayPtr->pArrayData
    //开辟内存，存放文件中每张图片的高度值 //rime 你丫得加个Export干嘛
    float *diffExport = malloc(sizeof(float)*5000);//rime diffExport->pDiffData

    DIR *directPath;                            //待打开的目录
    FILE *file;                                 //定义文件流指针(待打开的文件)
    struct dirent *filePath = NULL;             //待打开的文件路径
    directPath = opendir ("./data/");           //找出目录中的文件

    if ( directPath == NULL )                   //如果目录不存在，打印错误信息
    {
        perror ("Couldn't open the directory!");
    }

    while ( filePath = readdir(directPath) )    //while循环读取目录中的文件名
    {
        //如果是当前目录"."或上层目录".."则继续循环，否则向下执行程序
        if( strcmp(filePath->d_name,".") == 0 ||
            strcmp(filePath->d_name,"..") == 0 )
        {
            continue;
        }

        //将文件名加上路径，赋值给fileName
        sprintf(fileName,"./data/%s",filePath->d_name);
        file = fopen( fileName, "rb+");         //打开文件流指针
        //轮循文件中每个值，直至返回EOF(-1)
        for ( int i = 0; (charValue = getc(file)) != EOF; ++i )
        {
            *(arrayPtr+i) = charValue;          //将值放入开辟的内存空间
        }
        //文件中值的偏移量置为1(第一位存放图像数）
        pixelOffset = 1;
        for ( int i = 0; i < *arrayPtr; ++i )   //*arrayPtr为压缩的图像数
        {
            pixelOffset += 6;                   //偏移量+6（表头）
            //通过保存在表头中的值，算出像素点个数、最小/大值
            arrayLen = (*(arrayPtr+pixelOffset-6)<<8)+*(arrayPtr+pixelOffset-5);
            min = (*(arrayPtr+pixelOffset-4)<<8)+*(arrayPtr+pixelOffset-3);
            max = (*(arrayPtr+pixelOffset-2)<<8)+*(arrayPtr+pixelOffset-1);

            //获取文件名中的数字，对应内存中相同位置的原数据
            filenameNumber = ( filePath->d_name[8*i+4] - '0' ) * 100 +
                             ( filePath->d_name[8*i+5] - '0' ) * 10  +
                             ( filePath->d_name[8*i+6] - '0' ) * 1;
            picPtrOffset = 0;                   //将图片偏移量置为0
            //通过获取的文件中的数字，算出对应图片在内存中的指针位置
            for ( int j = 0; j < filenameNumber; ++j)
            {
                picPtrOffset += pixelCountArray[j];
            }

            //轮循当前图片
            for ( int j = 0; j < arrayLen; ++j )
            {
                //计算读取的当前图片与内存中相对应图片的差值
                *(diffExport+j) = (*(picPtr + picPtrOffset + j)) -
                                  ( (*(arrayPtr+pixelOffset+j)) *
                                  ( max - min ) / 255.0 + min );
            }

            //导出当前图片的差值
            sprintf(outputName,"./diff/chip%.3d_diff.txt",filenameNumber);
            FILE *diffFile = fopen(outputName, "w");
            //fwrite (diffExport , sizeof(unsigned char), arrayLen, diffFile);
            for ( int j = 0; j < arrayLen; ++j )
            {
                fprintf(diffFile,"%.2f\n",*(diffExport+j));
            }
            fclose(diffFile);
            pixelOffset += arrayLen;            //偏移量加上当前图片的长度

        }
        fclose(file);                           //关闭文件流指针
    }
    (void) closedir (directPath);               //关闭文件夹

    free(diffExport);                           //释放指针
    diffExport = NULL;                          //置为NULL
    free(arrayPtr);                             //释放指针
    arrayPtr = NULL;                            //置为NULL
    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    free(picPtr);                               //释放指针
    picPtr = NULL;                              //置为NULL

    return 0;
}
