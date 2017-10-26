#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#define IMAGE_COUNT 1000      // 生成图片数据数组的个数
#define BLOCK_SIZE 4096       // 保存文件时,最小区块的值(电脑保存文件时最小字节数为4096)
#define CHAR_SIZE_VALUE 255   // 一个Char字节保存的最大值
#define HEADER_LEN 6          // 生成数据表头的长度

void generateData(float * dataArr, int totalLen);
void findLimitValueInArr(int * dataArr, int dataCnt, int * limitArr , int dataIdx);
void mappingDataToCharArr(int * limitArr, int * dataArr, int * arrLength,
                          unsigned char * destArr);
void writeCharDataToFile(char * fileName,unsigned char * byteArr , int length);
void compressDateAndOutputToFile(unsigned char * sourceDataArr, int * preDataLen , int * dataLen);
void mappingDataToIntArr( int * limitArr, int * destArr, int arrLength,
                         unsigned char * sourceArr );
void decompressDataToFloatArr( float * destArr);
void writeFloatToFile(char * fileName,float * floatDataArr , int length);



//生成随机数据
/*
*  @brief generateData
*  @param dataArr为保存数据数组,totalLen为数组的总长度
*  @return
*/
void generateData(float * dataArr, int totalLen)
{
    srand( (unsigned)time( NULL ) );                        //初始化随机数

    //随机生成数据信息(0.00-5000.00),并存入数组
    for (int i = 0; i < totalLen; ++i)
    {
        dataArr[i] = (float) (rand() % 500001) / 100;
    }
}

//找出数组中的最大值与最小值
/*
*  @brief findLimitValue
*  @param dataArr为数据数组, dataCnt为数组中数据的个数
*         limitArr为存放最大值与最小值的数组,dataIdx为limitArr数组的索引号
*  @return
*/
void findLimitValueInArr(int * dataArr, int dataCnt, int * limitArr , int dataIdx)
{
    limitArr[dataIdx *2] = dataArr[0];                     //最大值
    limitArr[dataIdx * 2 + 1] = dataArr[0];                //最小值

    for (int j=0; j < dataCnt; j++)                        //求最大、最小
    {
        if ( limitArr[dataIdx *2] < dataArr[j] )
        {
            limitArr[dataIdx *2] = dataArr[j];             //找出最大值
        }
        if ( limitArr[dataIdx * 2 + 1]> dataArr[j] )
        {
            limitArr[dataIdx * 2 + 1] = dataArr[j];        //找出最小值
        }
    }
}

//将数组中的数据映射到char形数组中
/*
*  @brief mappingDataToCharArr
*  @param limitArr为存放最大值与最小值的数组, dataArr为每个数组中的数据数组
*         为数据数组的长度数组 , destArr为存放映射数据的数组
*  @return
*/
void mappingDataToCharArr(int * limitArr, int * dataArr, int * arrLength,
                          unsigned char * destArr)
{
    int preDataLen =0;                               //数据的前N项的长度

    // 轮询每个Data数组中的数据,将其映射到char形destArr数组中
    for (int i = 0; i < IMAGE_COUNT; ++i)
    {
        //判断最大值与最小值是否相等,如果相等则程序错误
        if (limitArr[2*i] == limitArr[2*i+1])
        {
            printf("数组的最大值与最小值错误!");
        }
        else
        {
            // 判断是否为float数组中的第一个数组
            if(0 != i)
            {
                // 轮询映射数组中的每个数据
                for (int j = 0; j < arrLength[i]; ++j)
                {
                    destArr[ preDataLen + (i * HEADER_LEN) ] = arrLength[i] / 100;
                    destArr[ preDataLen + (i * HEADER_LEN )+ 1 ] = arrLength[i] % 100;
                    destArr[ preDataLen + (i * HEADER_LEN) + 2 ] = limitArr[2*i] / 100;
                    destArr[ preDataLen + i * HEADER_LEN + 3 ] = limitArr[2*i] % 100;
                    destArr[ preDataLen + i * HEADER_LEN + 4 ] = limitArr[2*i + 1] / 100;
                    destArr[ preDataLen + i * HEADER_LEN + 5 ] = limitArr[2*i + 1] % 100;
                    //数组中的最大值与最小值分别为0,255,来映射数组中的数据
                    destArr[ preDataLen + i * HEADER_LEN + j + 6 ] = (unsigned char)( CHAR_SIZE_VALUE * (dataArr[preDataLen + j] -limitArr[2*i+1]) /(limitArr[2*i] - limitArr[2*i+1]));
                }
                preDataLen += arrLength[i];     //统计数组前N项数据的总长度
            }
            else
            {
                for (int j = 0; j < arrLength[i]; ++j)
                {
                    destArr[0] = arrLength[0] / 100;
                    destArr[1] = arrLength[0] % 100;
                    destArr[2] = limitArr[0] / 100;
                    destArr[3] = limitArr[0] % 100;
                    destArr[4] = limitArr[1]/ 100;
                    destArr[5] = limitArr[1] % 100;
                    destArr[j + 6] = (unsigned char)( CHAR_SIZE_VALUE * (dataArr[j] -limitArr[1]) / (limitArr[0] - limitArr[1]) );
                }
                preDataLen += arrLength[i];
            }
        }
    }

}

//将数据写入文件中
/*
*  @brief writeCharDataToFile
*  @param fileName 为数组名字的char形数组, byteArr为存放压缩数据的 char形数组
*         length 为数据的长度
*  @return
*/
void writeCharDataToFile(char * fileName,unsigned char * byteArr , int length)
{
    FILE *pf = NULL;
    pf = fopen(fileName,"w");

    for(int i=0; i<length; i++)
    {
        fprintf(pf,"%c",byteArr[i]);
    }
    fclose(pf);
}

//压缩数据并写入文件中
/*
*  @brief compressDateAndOutputToFile
*  @param sourceDataArr为需要写入文件的元数据数组, preDataLen为当前数组前N项数据的总长度
*         dataLen为当前数组的长度
*  @return
*/
void compressDateAndOutputToFile(unsigned char * sourceDataArr, int * preDataLen , int * dataLen)
{
    unsigned char longByteArr[5007];   // 压缩长度大于等于4096数组数据的char形数组
    unsigned char shortByteArr[10000]; // 压缩长度小于4096数组数据的char 形数组
    int shortFloatCnt = 0;             // 定义存放长度小于4096数组的个数,并初始化
    int shortFloatIdx = 0;             // 定义存放长度小于4096数组的索引号,并初始化
    int shortFloatLen = 0;             // 存放当前长度小于4096的数组长度,
    char fileName[50];                 // 文件名数组,长度为50
    int fileDataLen = 0;               // 文件数据的总长度

    // 轮询映射数组中的每个数据,并将小于4096的数据合并成一个数据,输出至文件
    for (int i = 0; i < IMAGE_COUNT; ++i)
    {
        // 数据长度大于等于4096的直接输出
        if( dataLen[i] >= BLOCK_SIZE )
        {
            //轮询映射数组中的每个数据,并压缩至新的数组中
            for (int j = 0; j < ( dataLen[i] + HEADER_LEN +1 ) ; ++j)
            {
                if( 0 != i )
                {
                    // 将压缩数组的第一个字节赋值为文件中数组的个数
                    longByteArr[0] = 1;
                    // 一次将数据存放在压缩数组中
                    longByteArr[j+1] = sourceDataArr[ j + preDataLen[i - 1] + i * HEADER_LEN ];
                }
                else
                {
                    longByteArr[0] = 1;
                    longByteArr[j+1] = sourceDataArr[j];
                }
            }
            // 将文件的总长度赋值
            fileDataLen = dataLen[i]+ HEADER_LEN + 1;
            // 将文件名字赋值
            sprintf(fileName,"/home/bob/data/chip%03d",i);
            // 将数据写入文件
            writeCharDataToFile(fileName, longByteArr , fileDataLen);

        }
        else
        {
            // 数据长度小于4096,且压缩数组中文件的个数不为0时
            if( 0 != shortFloatCnt )
            {
                shortFloatCnt++;                        //压缩文件中数组的数量累加

                shortByteArr[0] = shortFloatCnt;        //压缩文件的第一个数据改写为2

                // 将映射的数据存入至压缩数组中
                for (int j = 0; j < ( dataLen[i] + HEADER_LEN +1 ); ++j)
                {
                     shortByteArr[ shortFloatLen + 1 + HEADER_LEN + j ] = sourceDataArr[j + preDataLen[i - 1] + i * HEADER_LEN ];
                }

                fileDataLen = dataLen[i] + dataLen[shortFloatIdx] + 2 * HEADER_LEN + 1 ;

                sprintf(fileName,"/home/bob/data/chip%03d_chip%03d",shortFloatIdx,i);

                writeCharDataToFile(fileName, shortByteArr , fileDataLen);

                shortFloatCnt = 0;  //压缩数据并输出至文件后,将压缩数组中文件个数重置为0
            }
            else
            {
                // 数据长度小于4096,且压缩数组中文件的个数为0时
                shortFloatCnt++;                //压缩文件中文件个数累加
                shortFloatIdx = i;              //记录存放文件数组的索引号
                shortFloatLen = dataLen[i];     //记录存放文件数组的文件长度

                // 将映射的数据存入至压缩数组中
                for (int j = 0; j < ( dataLen[i] + HEADER_LEN +1 ) ; ++j)
                {
                    if( 0 != i )
                    {
                        shortByteArr[0] = shortFloatCnt;
                        shortByteArr[j+1] = sourceDataArr[j + preDataLen[i - 1] + i * HEADER_LEN ];
                    }
                    else
                    {
                        shortByteArr[0] = shortFloatCnt;
                        shortByteArr[j+1] = sourceDataArr[j];
                    }
                }
            }

        }
        // 如果所有数组轮询完后,仍有压缩文件的数据长度小于4096,直接压缩
        if(i == (IMAGE_COUNT-1) &&  0 != shortFloatCnt )
        {

            fileDataLen = dataLen[i]+ HEADER_LEN + 1;

            sprintf(fileName,"/home/bob/data/chip%03d",shortFloatIdx);

            writeCharDataToFile(fileName, shortByteArr , fileDataLen);

        }
    }
}

//将数据映射成整形
/*
*  @brief mappingDataToIntArr
*  @param limitArr为存放最大值与最小值数组, destArr为将存放映射回整形数据的数组
*         arrLength为要映射数组的长度, sourceArr为需要映射的数组
*  @return
*/
void mappingDataToIntArr( int * limitArr, int * destArr, int arrLength,
                         unsigned char * sourceArr )
{
    int maxValue = limitArr[0];                 // 将最大值与最小值赋值给变量
    int minValue = limitArr[1];

    //判断最大值与最小值是否相等,如果相等则程序错误
    if ( maxValue == minValue )
    {
        printf("数组的最大值与最小值错误!");
    }
    else
    {
        // 轮询映射数组中的每个数据
        for (int i = 0; i < arrLength; ++i)
        {
            //数组中的数据根据最大值与最小值,反映射整形
            destArr[i] = (int)(sourceArr[ i + HEADER_LEN + 1 ]) * (maxValue - minValue) / CHAR_SIZE_VALUE + minValue;
        }
    }
}

//读取解压数据并将数据转换为浮点型
/*
*  @brief decompressDataToFloatArr
*  @param destArr为存放解压数据的数组
*  @return
*/
void decompressDataToFloatArr( float * destArr)
{
    DIR *dp;                                    //定义数据类型为DIR类型
    char filePath[50];                          //文件路径的指针
    struct dirent *file;                        //声明结构体文件目录指针
    char dirname[50] = "/home/bob/data/";       //定义存放文件的目录
    int firstArrIdx, secondArrIdx;              //文件中对应数组的索引号
    int arrCntInFile = 0;                       //文件中数组的数量
    int dataLen[1000];                          //定义存放数组长度的数组
    int limitValueArr[2 * IMAGE_COUNT];         //定义存放最大值最小值的数组
    unsigned char dataCacheArr[10000];          //缓存读取文件数据的数组

    int ** dataArr ;                            //定义双重指针(存放映射后文件数据)
    dataArr = (int **)malloc(sizeof(int *) * IMAGE_COUNT); //开辟1000个数组指针(数据头指针)

    // 判断文件目录是否被打开
    if((dp = opendir(dirname)) == NULL)
    {
        printf("Can't open %s\n", dirname);
    }

    // 当文件读取
    while((file = readdir(dp)) != NULL )
    {
        //判断读取的目录是否为'.'或者'..',如果是则跳过
        if(strcmp(file->d_name,".") == 0 || strcmp(file->d_name,"..") == 0)
        {
            continue;
        }
        sprintf(filePath,"/home/bob/data/%s",file->d_name);

        //打开文件:
        int fileCondition = open(filePath,O_RDONLY,10000);

        if (fileCondition != -1)
        {
            //读文件将文件的数据放到dataCacheArr数组中
            int fileCharCnt = read(fileCondition,dataCacheArr,10000);
            //判断文件中数组的数量
            arrCntInFile = (int)(dataCacheArr[0]);
            //获得数组的索引号
            firstArrIdx = 100 * (file->d_name[4] - '0') + 10 * (file->d_name[5] - '0') + (file->d_name[6] - '0');
            //获得数组的长度
            dataLen[firstArrIdx] = 100 * (int)(dataCacheArr[1]) + (int)(dataCacheArr[2]);
            //获得数组中最大值
            limitValueArr[2 * firstArrIdx] = 100 * (int)(dataCacheArr[3]) + (int)(dataCacheArr[4]);
            //获得数组中最小值
            limitValueArr[2 * firstArrIdx + 1] = 100 * (int)(dataCacheArr[5]) + (int)(dataCacheArr[6]);

            //开辟存放数据的数组空间
            dataArr[firstArrIdx] = (int *)malloc(sizeof(int) * dataLen[firstArrIdx]);
            //将数据映射为整形数组
            mappingDataToIntArr( &limitValueArr[2 * firstArrIdx], dataArr[firstArrIdx],
                                 dataLen[firstArrIdx] , dataCacheArr );

            if( arrCntInFile == 2)
            {
                //将第二个数组的索引号赋值
                secondArrIdx = 100 * (file->d_name[12] - '0') + 10 * (file->d_name[13] - '0') + (file->d_name[14] - '0');
                //获取数组的长度
                dataLen[secondArrIdx] = 100 *(int) (dataCacheArr[ dataLen[firstArrIdx] + HEADER_LEN + 1 ]) +
                                        (int)(dataCacheArr[ dataLen[firstArrIdx] +
                                        HEADER_LEN + 2 ]);
                //获取第二个数组的最大值
                limitValueArr[2 * secondArrIdx] = 100 *(int) (dataCacheArr[ dataLen[firstArrIdx] + HEADER_LEN + 3 ]) +
                                                  (int)(dataCacheArr[ dataLen[firstArrIdx] +
                                                   HEADER_LEN + 4 ]);
                //获取第二个数组的最小值
                limitValueArr[2 * secondArrIdx + 1] = 100 *(int) (dataCacheArr[ dataLen[firstArrIdx] + HEADER_LEN + 5 ]) +
                                                      (int)(dataCacheArr[ dataLen[firstArrIdx] +
                                                       HEADER_LEN + 6 ]);
                //开辟存放数据的数组空间
                dataArr[secondArrIdx] = (int *)malloc(sizeof(int) * dataLen[secondArrIdx]);
                //将数据映射为整形数组
                mappingDataToIntArr( &limitValueArr[2 * secondArrIdx], dataArr[secondArrIdx],
                                     dataLen[secondArrIdx] , & dataCacheArr[ dataLen[firstArrIdx] + HEADER_LEN] );
            }
        }
        close(fileCondition);
    }

    int dataIdx = 0;                                     // 定义转换浮点数据的索引
    // 将二维数组中数据转换成浮点数并赋值给一维数组
    for (int i = 0; i < IMAGE_COUNT; ++i)
    {
        for (int j = 0; j < dataLen[i]; ++j)
        {
            destArr[dataIdx] = (float)dataArr[i][j] + (float) (rand() % 100) / 100 ;
            dataIdx++;
        }
        free(dataArr[i]);
        dataArr[i] = NULL;
    }
    free(dataArr);
    dataArr = NULL;
}

//将浮点型数据写入文件
/*
*  @brief writeFloatToFile
*  @param fileName为存放文件路径, floatDataArr为需要输出至文件的浮点数据
*         length为数组的长度
*  @return
*/
void writeFloatToFile(char * fileName,float * floatDataArr , int length)
{
    FILE *pf = NULL;                    //定义文件流指针
    pf = fopen(fileName,"w");           //打开文件,并赋予文件可写的权限
    // 将数组中数据写入文件
    for(int i=0; i<length; i++)
    {
        fprintf(pf,"  %.2f",floatDataArr[i]);
    }
    fclose(pf);
}

int main()
{
    srand( (unsigned)time( NULL ) );                 //初始化随机数
    int dataLen[IMAGE_COUNT];                        //声明图片大小的数组

    int limitValueArr[2 * IMAGE_COUNT];             //定义一个存放最大值与最小值数组

    float * floatDataArr;                           //声明一个图片数据指针
    float * decompressDataArr;                      //存放解压后数据的数组
    int * intDataArr;                               //声明一个整形数据数组指针
    int dataTotalLen[IMAGE_COUNT];                  //声明数组前N项的总大小,并初始化
    unsigned char * mappingArr;                     //声明一个映射值的数组指针
    float * dataDiffArr;                            //定义一个存放映射前后差值的数组

    // 随机生成数组的长度,并统计数组长度的前N项和
    for (int i = 0; i < IMAGE_COUNT; ++i)
    {
        dataLen[i] = (rand() % 2953) + 2048;         //获得任意一个图片大小(2048-5000)
        // 统计数组长度前N项的和
        if(0 != i)
        {
            dataTotalLen[i] = dataLen[i] + dataTotalLen[i-1];     //计算数据的总大小
        }
        else
        {
            dataTotalLen[i] = dataLen[i] ;     //计算数据的总大小
        }
    }
    //开辟存放数据的空间
    floatDataArr = (float*)malloc( dataTotalLen[IMAGE_COUNT-1] * sizeof(float) );
    //开辟存放整形数据的空间
    intDataArr = (int *)malloc( dataTotalLen[IMAGE_COUNT-1] * sizeof(int) );
    // 开辟存放映射数组的空间
    mappingArr = (unsigned char *)malloc( (dataTotalLen[IMAGE_COUNT-1] + IMAGE_COUNT * HEADER_LEN + 1) * sizeof(unsigned char) );
    //开辟存放解压后数据的空间
    decompressDataArr = (float *)malloc( dataTotalLen[IMAGE_COUNT-1] * sizeof(float) );
    //开辟存放解压数组前后差值的数组
    dataDiffArr = (float *)malloc( dataTotalLen[IMAGE_COUNT-1] * sizeof(float) );

    //判断是否已开辟好内存
    if( floatDataArr == NULL || intDataArr == NULL || mappingArr == NULL)
    {
        printf("创建数组失败 ！\n");
        return 1;
    }

    // 生成数据
    generateData(floatDataArr,dataTotalLen[IMAGE_COUNT-1]);

    //将数据转换成整形
    for (int i = 0; i < dataTotalLen[IMAGE_COUNT-1]; ++i)
    {
        intDataArr[i] = (int) floatDataArr[i];
    }

    //找出整数组中的最大值,与最小值
    for (int i = 0; i < IMAGE_COUNT; ++i)
    {
        if( i != 0)
        {
             findLimitValueInArr(intDataArr+dataTotalLen[i-1], dataLen[i], limitValueArr, i);
        }
        else
        {
            findLimitValueInArr(intDataArr, dataLen[i], limitValueArr, i);
       }
    }

    //将数组中的数据,映射到char形数组中
    mappingDataToCharArr(limitValueArr,intDataArr, dataLen, mappingArr);

    // 将数据压缩并输出至文件
    compressDateAndOutputToFile(mappingArr, dataTotalLen , dataLen);

    // 将文件数据解压并存放到数组中
    decompressDataToFloatArr(decompressDataArr);

    //比较解压后与原始数据的差值,并存放至文件中
    for (int i = 0; i < dataTotalLen[IMAGE_COUNT-1]; ++i)
    {
        dataDiffArr[i] = floatDataArr[i] - decompressDataArr[i];
    }
    //将差值数据写入文件
    char filePath[50];
    for (int i = 0; i < IMAGE_COUNT; ++i)
    {
        sprintf(filePath,"/home/bob/datadiff/chip%03d_diff",i);

        if( i != 0)
        {
            writeFloatToFile(filePath, &dataDiffArr[dataTotalLen[i-1]] , dataLen[i]);
        }
        else
        {
            writeFloatToFile(filePath, dataDiffArr, dataLen[i]);
        }
    }

    free(floatDataArr);
    free(intDataArr);
    free(mappingArr);
    free(decompressDataArr);
    free(dataDiffArr);
    floatDataArr = NULL;
    intDataArr = NULL;
    mappingArr = NULL;
    decompressDataArr = NULL;
    dataDiffArr = NULL;
    return 0;
}
