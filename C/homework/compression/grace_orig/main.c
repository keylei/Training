#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
#include <dirent.h>
//#include <sys/stat.h>
#include <time.h>

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//grace171017 常量与宏函数定义
#define ARR_COUNT         1000        //这个是数组的数量
#define ARRLENGTH_MAX     5000        //数组长度最大
#define ARRLENGTH_MIN     2048        //数组长度最小
#define DATA_MAX          500000      //最大数据是5000，要保留两位小数这里保留两位
#define DATA_BIT          0.01        //小数精度保证两位

#define COMPRESS_LIMIT_SIZE   4096    //压缩数据包的阀值，即超过此值直接压缩
#define COMPRSPKG_HEAD_LENGTH 1       //一个压缩数据包中保存已压缩数据包个数
#define ARRPKG_HEAD_LENGTH    6       //一个数组压缩包的表头长度（长度，最大值，最小值）

#define RANDOM_ARR_LENGTH  (rand()%(ARRLENGTH_MAX-ARRLENGTH_MIN)+ARRLENGTH_MIN)  //生成数组的随机长度
#define RANDOM_ARR_DATA   ((float)(rand()%DATA_MAX)*DATA_BIT)                    //随机浮点数的生成

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//grace171018 数据生成和访问函数集

/*
*  @brief 生成 arrCount 个数组
*         长度在400到4000之间 RANDOM_ARR_LENGTH ,数据是浮点数在0到5000之间
*  @param   arrLength：保存各个生成数组的长度
*            arrCount：数组长度
*  @return   float * : 返回保存数据的指针
*/
float *generateData(short* arrLength,int arrCount)
{
    float *dPtr = NULL;      //存放生成的随机数，返回指针
    int arrLengthSum = 0;    //数组总长度

    //1：统计数组长度
    srand(time(NULL));
    for (int arrCountI = 0; arrCountI < arrCount; ++arrCountI)
    {
        arrLength[arrCountI] = RANDOM_ARR_LENGTH;
        arrLengthSum += arrLength[arrCountI];
    }

    //2：申请数据空间
    dPtr = (float *)malloc(arrLengthSum * sizeof(float*));
    if(dPtr == NULL)
    {
        printf("内存开辟失败！");
        exit(1);
    }

    //3：数组数据生成
    arrLengthSum = 0;
    for (int arrCountI = 0; arrCountI < arrCount; ++arrCountI)
    {
        for(int dataCountI = 0;dataCountI < arrLength[arrCountI]; ++dataCountI)
        {
            *(dPtr  + arrLengthSum + dataCountI) = RANDOM_ARR_DATA;  // 存储产生的随机数据
        }
        arrLengthSum += arrLength[arrCountI];
    }

    return dPtr;
}

/*
*  @brief  返回在大数组中的存储起始位置
*  @param   arrLength：保存各个生成数组的长度
*            arrIndex：数组索引号
*  @return   int ： 返回偏移值
*/
int getDataAddOffset(short *arrLength,int arrIndex)
{
    int startAdd = 0;
    for (int arrCountI = 0; arrCountI < arrIndex; ++arrCountI)
    {
        startAdd += arrLength[arrCountI];
    }
    return startAdd;
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//grace171019 读写文件函数集

/*
*  @brief  将一个uchar数组以二进制的形式写入文件中保存
*  @param  filename：文件名
*              data：要写入的数据源
*        dataLength：写入数据的长度
*  @return N/A
*/
void writeBytesToFile(char *filename, unsigned char *data, int dataLength)
{
    FILE *fp;

    if( (fp=fopen(filename,"w")) == NULL )
    {
        printf("%s open failed!",filename);
        exit(0);
    }

    for(int i = 0;i < dataLength; ++i)
    {
        fputc(*(data + i),fp);
    }

    fclose(fp);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//grace171018 压缩函数集合

/*
*  @brief  将一个特定浮点数组的数据压入一个Byte数据包
*  @param     fdata: 输入被转换的浮点数据
*         arrLength: fdata中每个数组的长度
*         fArrIndex： 要压缩的数组索引
*     compreDataArr： 压缩数据存储位置
*  @return N/A
*/
void floatCompreToUChar(float *fdata,short arrLength,unsigned char *compreDataArr)
{
    float *tFDataPtr;
    int tempData,dataMax = 0,dataMin = DATA_MAX / 100;
    unsigned char tempCompData;          //求压缩比例的中转值
    float scale = 0.0;                   //压缩比例
    tFDataPtr = fdata;

    *(compreDataArr + 0) = arrLength;    //存储数组长度
    *(compreDataArr + 1) = arrLength >> 8;

    for(int dataIndex = 0;dataIndex < arrLength; ++dataIndex) //找最大最小值
    {
        tempData = (int) *(tFDataPtr + dataIndex);
        if(dataMax < tempData) dataMax = tempData;
        if(dataMin > tempData) dataMin = tempData;
    }

    *(compreDataArr + 2) = dataMin;    //存储数组最小值
    *(compreDataArr + 3) = dataMin >> 8;

    *(compreDataArr + 4) = dataMax;    //存储数组最大值
    *(compreDataArr + 5) = dataMax >> 8;

    scale = (float)(dataMax - dataMin) / 255.0;

    for(int dataIndex = 0;dataIndex < arrLength; ++dataIndex) //压缩存储数据
    {
        tempData = (int) *(tFDataPtr+dataIndex);
        tempCompData = (tempData - dataMin) / scale;
        *(compreDataArr + ARRPKG_HEAD_LENGTH + dataIndex) = tempCompData;
    }
}

/*
*  @brief  压缩数据到动态内存空间
*  @param   fdata:要压缩的数据
*       arrLength:数组长度
*  @return  N/A
*/
void imgCompress(float *fdata,short *arrLength)
{
    clock_t startTime, finishTime;                 //压缩开始,结束时间
    double compressTime;                           //定义压缩运行时间
    short compresDataLen;                          //图像压缩数组的长度
    int tempOffset;                                //临时保存原始浮点数据数组在存储中的偏移
    short arrCompresIndexMatch[ARR_COUNT];         //保存直接大于COMPRESS_LIMIT_SIZE的数组
    short arrCompresIndexPiece[ARR_COUNT];         //保存小于COMPRESS_LIMIT_SIZE的数组
    unsigned char *compresDataArrPtr;              //压缩数组存储申请空间
    int arrI = 0,subArrI = 0;                      //索引临时变量
    int matchI = 0,pieceI = 0;                     //保存搜索数组的索性
    short fLengthArrIndex = 0;                     //float数组长度的下标
    int pkgArrCnt = 0;                             //一个压缩包的数组个数
    int indexBuf = 0;                              //保存arri
    char filename[FILENAME_MAX];                   //保存文件名的数组
    char subFilename[FILENAME_MAX];                //保存连接的文件名

    startTime = clock();                           //获取开始时间
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    // step1 搜索数组长度大于COMPRESS_LIMIT_SIZE的数组索性更新到 arrCompresIndexMatch 和 arrCompresIndexPiece数组
    for (arrI = 0; arrI < ARR_COUNT; ++arrI)
    {
        if(arrLength[arrI] > COMPRESS_LIMIT_SIZE)
        {
            arrCompresIndexMatch[matchI++] = arrI;
        }
        else
        {
            arrCompresIndexPiece[pieceI++] = arrI;
        }
    }

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    // step2 将数组长度大于COMPRESS_LIMIT_SIZE的数组 即arrCompresIndexMatch中的数组进行压缩
    for (arrI = 0; arrI < matchI; ++arrI)
    {
        fLengthArrIndex = arrCompresIndexMatch[arrI];                                       //读取arrLength数组下标

        compresDataLen = COMPRSPKG_HEAD_LENGTH + ARRPKG_HEAD_LENGTH + arrLength[fLengthArrIndex];//数据申请空间大小
        compresDataArrPtr = (unsigned char *)malloc(compresDataLen * sizeof(char));         //申请空间
        if(compresDataArrPtr == NULL)
        {
            printf("内存开辟失败\n");
            exit(1);
        }

        *compresDataArrPtr = 1;                                                             //标记本数据包存储数组个数
        tempOffset = getDataAddOffset(arrLength,fLengthArrIndex);                           //获取原始数据起始偏移
        floatCompreToUChar((fdata + tempOffset),arrLength[fLengthArrIndex],(compresDataArrPtr+1));//将浮点数压入字节数组
        sprintf(filename,"./data/chip%03d",fLengthArrIndex);
        writeBytesToFile(filename,compresDataArrPtr,compresDataLen);                       //将字节数组写入文件
        free(compresDataArrPtr);
    }

    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    // step3 将数组长度小于COMPRESS_LIMIT_SIZE的数组 即arrCompresIndexPieceh中的数组进行压缩和写出文件
    for (arrI = 0; arrI < pieceI; ++arrI)
    {
        compresDataLen = 0;
        pkgArrCnt = 0;
        indexBuf = arrI;
        int offset = 1; //多数组存放时的偏移

        //1 根据搜索到的待压缩节点数组
        for(subArrI = arrI;subArrI < pieceI; ++subArrI)
        {
            fLengthArrIndex = arrCompresIndexPiece[subArrI];    //获取存储的数组长度下面
            compresDataLen += arrLength[fLengthArrIndex];
            ++pkgArrCnt;                                        //数据包计数
            if(compresDataLen > COMPRESS_LIMIT_SIZE || subArrI == (pieceI - 1)) //累加满足4096 或 为最后一个数据
            {
                arrI = subArrI;         //更新下一次搜索压缩包的起点
                break;
            }
        }

        //2 申请数据空间
        compresDataLen += COMPRSPKG_HEAD_LENGTH + ARRPKG_HEAD_LENGTH * pkgArrCnt;   //数据申请空间大小
        compresDataArrPtr = (unsigned char *)malloc(compresDataLen * sizeof(char)); //申请空间
        if(compresDataArrPtr == NULL)
        {
            printf("内存开辟失败！");
            exit(1);
        }
        *compresDataArrPtr = pkgArrCnt; //数据包存储数组个数

        //3 循环将相应数据压缩
        for(subArrI = indexBuf;subArrI < (indexBuf + pkgArrCnt); ++subArrI)
        {
            fLengthArrIndex = arrCompresIndexPiece[subArrI];                        //读取arrLength数组下标
            tempOffset = getDataAddOffset(arrLength,fLengthArrIndex);               //获取原始数据起始偏移
            floatCompreToUChar((fdata + tempOffset),arrLength[fLengthArrIndex],(compresDataArrPtr+offset));  //将浮点数压入字节数组
            offset += arrLength[fLengthArrIndex]+ARRPKG_HEAD_LENGTH;
            if(subArrI == indexBuf)
                sprintf(filename,"./data/chip%03d",fLengthArrIndex);
            else
            {
                sprintf(subFilename,"_chip%03d",fLengthArrIndex);
                strcat(filename,subFilename);
            }
        }

        //4 写出压缩数据到文件并释放申请的数据
        writeBytesToFile(filename,compresDataArrPtr,compresDataLen);  //将字节数组写入文件
        free(compresDataArrPtr);
    }
    finishTime = clock();                                             //获取完成时间
    compressTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC; //获取压缩时间
    printf("压缩时间为：%fs\n",compressTime);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//grace171023 解压缩函数

/*
*  @brief 把数据从文本中读出来还原数据，求与原始数据的差值并存入文件中
*  @param   fdata：原始生成的数据
*       arrLength：数组长度
*  @return  N/A
*/
void uncompress(float *fdata,short *arrLength)
{
    clock_t startTime, finishTime;          //压缩开始,结束时间
    double uncompressTime;                  //定义压缩运行时间
    float scale;                            //压缩比例
    short *header;                          //存取表头数据
    int pkgArrCnt;                          //数据包的个数
    short ARRCONTENTLEN = COMPRSPKG_HEAD_LENGTH + ARRPKG_HEAD_LENGTH; //存放表头
    float *chToFData;                       //存放char型转float型数据
    unsigned char *origArrData;             //存放原始char型数据
    int origDateOffset;                     //原始数据偏移
    int filenameNumber = 0;                 //当前文件名中的数字
    float arrDataDiff;                      //数组数据差值

    startTime = clock();                    //获取开始时间
    //>>>-------------------------------------------------------------------------------------------------------------------------------------
    // step1.遍历文件目录
    DIR *directPath;                        //待打开的目录
    struct dirent *filePath = NULL;         //待打开的文件路径
    directPath = opendir ("./data/");       //找出目录中的文件
    if ( directPath == NULL )               //如果目录不存在，打印错误信息
    {
        perror ("Couldn't open the directory!");
    }

    char fileNamebuffer[FILENAME_MAX];
    while ( (filePath = readdir(directPath)) != NULL ) //while循环读取目录中的文件名
    {
        if( strcmp(filePath->d_name,".") == 0 ||       //如果是当前目录"."或上层目录".."则继续循环，否则向下执行程序
                strcmp(filePath->d_name,"..") == 0 )
        {
            continue;
        }
        sprintf(fileNamebuffer,"./data/%s",filePath->d_name); //将文件名加上路径，赋值给fileNamebuffer

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        // step2.打开文件
        FILE *fp;                                         //文件指针
        unsigned char ch[ARRCONTENTLEN];
        if((fp = fopen(fileNamebuffer,"rb+")) == NULL)    //打开文件失败退出
        {
            printf("\nCannot open file!");
            exit(1);
        }
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        // step3.数据操作

        //1.还原数据
        fread(ch,sizeof(char),COMPRSPKG_HEAD_LENGTH,fp);  //把文件个数存放到ch数组中
        pkgArrCnt = ch[0];                                //保存数组个数，后面ch[0]会改变
        header = ch;
        for(int i=0;i<pkgArrCnt;++i)
        {
            fread(ch,sizeof(char),ARRPKG_HEAD_LENGTH,fp); //保存文件长度最大值最小值

            origArrData = malloc(header[0] * sizeof(char)); //存放char型原始数据
            if(origArrData == NULL)
            {
                printf("内存开辟失败\n");
                exit(1);
            }
            chToFData = malloc(header[0]*sizeof(float));    //存放char型转float数据
            if(chToFData == NULL)
            {
                printf("内存开辟失败\n");
                exit(1);
            }

            fread(origArrData,sizeof(char),header[0] * sizeof(char),fp); //读取数组数据
            scale = (header[2] - header[1])/255.0;                       //获取比例

            filenameNumber = ( filePath->d_name[8*i+4] - '0' ) * 100 +   //获取文件名数字部分，并由字符串转为数字
                    ( filePath->d_name[8*i+5] - '0' ) * 10  +
                    ( filePath->d_name[8*i+6] - '0' ) * 1;

            sprintf(fileNamebuffer,"./diff/chip%03d_diff.txt",filenameNumber);
            FILE *diffFile = fopen(fileNamebuffer, "a+");                //以追加形式的打开文件，没有文件则创建

            //2.计算差值并存入文件
            for(int j=0;j<(int)header[0];++j)                            //遍历数组中数据
            {
                chToFData[j] = origArrData[j] * scale + header[1];
                origDateOffset =  getDataAddOffset(arrLength,filenameNumber);//获取当前数据的偏移
                arrDataDiff = fdata[origDateOffset+j] - chToFData[j];        //获取差值
                fprintf(diffFile,"%.2f\n",arrDataDiff);
            }

            //3.关闭文件并释放指针
            fclose(diffFile);
            free(origArrData);
            origArrData = NULL;
            free(chToFData);
            chToFData = NULL;
        }
        fclose(fp);
    }
    closedir (directPath);  //关闭目录
    finishTime = clock();   //获取完成时间
    uncompressTime = (double)(finishTime - startTime) / CLOCKS_PER_SEC; //获取解压缩时间
    printf("解压缩运行时间：%fs\n",uncompressTime);
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
*  @brief 主函数：创建目录，其他函数入口
*  @param N/A
*  @return N/A
*/
int main()
{
    mkdir("./data",0777);                        //创建目录
    mkdir("./diff",0777);

    float* dataArr;
    short arrLength[ARR_COUNT];

    dataArr = generateData(arrLength,ARR_COUNT); //数据生成

    imgCompress(dataArr,arrLength);              //数据压缩
    uncompress(dataArr,arrLength);               //数据解压

    free(dataArr);
    dataArr = NULL;
    return 0;
}
