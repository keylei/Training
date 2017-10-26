#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#include "datahelp.c"                           //一些范性功能函数

#define BLOCK_SIZE 4096                         //一个块区的大小
#define MAX_ARR_LEN 5000                        //最大数组长度
#define MIX_ARR_LEN 2048                        //最小数组长度
#define HEADER_LEN 6                            //数据表头长度
#define ARR_CNT 1000                            //数组个数

void generateImgData(long int *dataHeadPtrArr,int *arrLenArr);
void compressAndExportData(long int *dataHeadPtrArr,int *arrLenArr);
void compressArr(float *souce,unsigned char *dest,short length);
void decompressData(long int *destHeadPtr,int *arrLenArr);
long int decompressArr(unsigned char *souceArr,int *length);
void clacResultError(long int *soucePtrArr,long int *resultPtrArr,int *lenArr);


int main()
{
    long int dataHeadPtrArr[ARR_CNT];           //生成的数据数组头指针地址
    long int decompressedPtrArr[ARR_CNT];       //解压缩出的数据的头指针地址
    int arrLenArr[ARR_CNT];                     //数组长度数组

    // 调用生成数据函数：
    generateImgData(dataHeadPtrArr,arrLenArr);

    // 调用压缩并导出数据函数：
    compressAndExportData(dataHeadPtrArr,arrLenArr);

    //调用解压缩数据函数：
    decompressData(decompressedPtrArr,arrLenArr);

    //计算解压出的误差：
    clacResultError(dataHeadPtrArr,decompressedPtrArr,arrLenArr);


    //释放堆上开的所有数组空间：
    for (int i = 0; i < ARR_CNT; ++i)
    {
        free((void *)dataHeadPtrArr[i]);
        free((void *)decompressedPtrArr[i]);
    }
}


/*
*  @brief   生成图像数据
*  @param   参数1为存放数据数组头指针的数组
*           参数2为存放数组长度的数组
*  @return
*/
void generateImgData(long int *dataHeadPtrArr,int *arrLenArr)
{
    //将时间作为随机函数的种子：
    srand( (unsigned)time( NULL ) );

    //生成数据数组：
    for (int i = 0; i < ARR_CNT; ++i)
    {
        //生成数组长度：
        arrLenArr[i] = generateRandomNum(MIX_ARR_LEN,MAX_ARR_LEN);

        //创建数组空间：
        dataHeadPtrArr[i] = malloc(sizeof(float) * arrLenArr[i]);

        //生成数组中的数据：
        for (int j = 0; j < arrLenArr[i] ; ++j)
        {
            ((float*)(dataHeadPtrArr[i]))[j] = (float) generateRandomNum(1,500000) / 100;
        }
    }
}


/*
*  @brief   压缩并导出数据
*  @param   参数1为存放数据数组头指针的数组
*  @return  参数2为存放数组长度的数组
*/
void compressAndExportData(long int *dataHeadPtrArr,int *arrLenArr)
{
    unsigned char path[50];                             //生成压缩数据的路径
    unsigned char compressingArr[10000];                //将要压缩的数组
    int indexOffset = 0;                                //用来记录索引的变量

    mkdir("./compressedData",0777);                     //生成存放压缩数据的目录

    for (int i = 0; i < ARR_CNT; ++i)
    {
        indexOffset = 0;
        if ( arrLenArr[i] < BLOCK_SIZE)
        {
            //若存在未压缩数组且下一个数组的长度不小于块大小，执行while中的代码以将数组压缩并导出：
            while ( (arrLenArr[i + 1] >= BLOCK_SIZE) && (i != (ARR_CNT - 1)) )
            {
                //将压缩数组个数位置为1：
                compressingArr[0] = 1;

                ++i;
                ++indexOffset;
                //更新文件名字符串：
                sprintf(path,"./compressedData/chip%03d",i);

                //调用压缩数组函数：
                compressArr((float*)dataHeadPtrArr[i],&compressingArr[1],(short)arrLenArr[i]);

                //调用向文件写入数据函数：
                writeStrToFile(path,compressingArr,arrLenArr[i] + HEADER_LEN + 1);
            }

            //若存在未压缩数组：
            if( i != (ARR_CNT - 1) )
            {
                //将压缩数组个数位置为2：
                compressingArr[0] = 2;

                //更新文件名字符串：
                sprintf(path,"./compressedData/chip%03d_chip%03d",i - indexOffset,i + 1);

                //调用压缩数组函数压缩第一个数组：
                compressArr((float*)dataHeadPtrArr[i - indexOffset],(compressingArr + 1),(short)arrLenArr[i - indexOffset]);
                int oldArrLen = arrLenArr[i - indexOffset];

                ++i;
                //调用压缩数组函数压缩第二个数组：
                compressArr((float*)dataHeadPtrArr[i],&compressingArr[1 + oldArrLen + HEADER_LEN],(short)arrLenArr[i]);

                //调用向文件写入数据函数：
                writeStrToFile(path,compressingArr,arrLenArr[i] + arrLenArr[i - indexOffset] + 2 * HEADER_LEN + 1);
            }
            else
            {
                //将压缩数组个数位置为1：
                ((char*)compressingArr)[0] = 1;

                //更新文件名字符串：
                sprintf(path,"./compressedData/chip%03d",i - indexOffset);

                //调用压缩数组函数：
                compressArr((float*)dataHeadPtrArr[i - indexOffset],(compressingArr + 1),(short)arrLenArr[i - indexOffset]);

                //调用向文件写入数据函数：
                writeStrToFile(path,compressingArr,arrLenArr[i - indexOffset] + HEADER_LEN + 1);
            }
        }
        else
        {
            //更新文件名字符串：
            sprintf(path,"./compressedData/chip%03d",i);

            //将压缩数组个数位置为1：
            compressingArr[0] = 1;

            //调用压缩数组函数：
            compressArr( (float*) dataHeadPtrArr[i],&compressingArr[1],(short)arrLenArr[i]);

            //调用向文件写入数据函数：
            writeStrToFile(path,compressingArr,arrLenArr[i] + HEADER_LEN + 1);
        }
    }
}


/*
*  @brief   将源浮点型数组的指定个数元素压缩为一个字节到目标地址
*  @param   参数1为源float数组的头指针
*           参数2为目标数组头指针
*           参数3为要压缩的元素个数
*  @return  N/A
*/
void compressArr(float *souce,unsigned char *dest,short length)
{
    short *temp;
    //生成表头：
    temp = dest;
    temp[0] = (short)length;
    temp[1] = (short)getMinNum(souce,length);
    temp[2] = (short)getMaxNum(souce,length);

    //压缩数据并写入目标地址：
    for (int i = 0; i < length; ++i)
    {
        dest[HEADER_LEN + i] = (unsigned char)clacMapValue(1,255,1,5000,(int)souce[i]);
    }
}


/*
*  @brief   解压缩数据
*  @param   参数1为解压缩后的数组的头指针存放数组
*           参数2存放数组长度
*  @return
*/
void decompressData(long int *destHeadPtr,int *arrLenArr)
{
    DIR *dp;
    char path[50];                             //打开文件的路径
    struct dirent *file;
    char dirname[20] = "./compressedData";     //目录的名字
    unsigned char fileDataArr[10000];          //存放文件中数据的数组
    int arrIndex = 0;                          //数组编号
    int preArrIndex = 0;                       //上一个数组编号

    //打开目录防呆：
    if((dp = opendir(dirname)) == NULL)
    {
        printf("无法打开目录 %s\n", dirname);
    }

    //遍历目录下的所有文件：
    while((file = readdir(dp)) != NULL )
    {
        //判断是否为"."或".."之类的隐藏目录，若是则直接进入下次循环：
        if(strncmp(file->d_name, ".", 1) == 0)
        {
            continue;
        }

        //通过文件名生成打开文件的路径：
        sprintf(path,"./compressedData/%s",file->d_name);

        //打开文件:
        int f=open(path,O_RDONLY,10000);

        if (f != -1)
        {
            //读文件:
            int i = read(f,fileDataArr,10000);
            if(i>0)
            {
                //判断打开的文件名是否为短文件名：
                if (7 == strlen(file->d_name))
                {
                    //通过文件名确认数组编号：
                    arrIndex = 100 * (file->d_name[4] - '0') + 10 * (file->d_name[5] - '0') + (file->d_name[6] - '0');

                    //解压缩该数组：
                    destHeadPtr[arrIndex] = decompressArr(&fileDataArr[1],&arrLenArr[arrIndex]);
                }
                else
                {
                    //通过文件名确认第一个数组的编号：
                    arrIndex = 100 * (file->d_name[4] - '0') + 10 * (file->d_name[5] - '0') + (file->d_name[6] - '0');

                    //解压缩第一个数组：
                    destHeadPtr[arrIndex] = decompressArr(&fileDataArr[1],&arrLenArr[arrIndex]);

                    //通过文件名确认第二个数组的编号：
                    preArrIndex = arrIndex;                                     //保存上一个数组的数组编号，用于取上一个数组的长度
                    arrIndex = 100 * (file->d_name[12] - '0') + 10 * (file->d_name[13] - '0') + (file->d_name[14] - '0');
                    destHeadPtr[arrIndex] = decompressArr(&(fileDataArr[(1 + arrLenArr[preArrIndex] + HEADER_LEN)]),&(arrLenArr[arrIndex]));
                }
            }
        }
    }
    //关闭目录：
    closedir(dp);
}


/*
*  @brief   解压缩数组
*  @param   参数1为源压缩数组
*           参数2为保存数组长度变量的地址
*  @return  返回值为压缩后数组的头指针
*/
long int decompressArr(unsigned char *souceArr,int *length)
{
    short *temp;
    float *destArr;                                 //解压缩数组存储的首地址

    //解压缩表头信息：
    temp = souceArr;
    length[0] = (int)temp[0];                       //获得数组长度
    int minValue = temp[1];                         //获得数组元素最小值
    int maxValue = temp[2];                         //获得数组元素最大值

    //根据数组长度开辟内存空间：
    destArr = malloc(sizeof(float) * length[0]);

    //解压缩源数组中的数：
    for (int i = 0; i < length[0]; ++i)
    {
        destArr[i] = clacMapValue(1,5000,1,255,(int)(souceArr[HEADER_LEN + i])) + generateRandomNum(0,99) / 100;
    }

    //将压缩出数组的头指针返回：
    return destArr;
}


/*
*  @brief   比较解压缩后的数据和源数据差
*  @param   参数1为生成的数据数组的头指针数组
*           参数2为解压出的数据数组的头指针数组
*  @return  N/A
*/
void clacResultError(long int *soucePtrArr,long int *resultPtrArr,int *lenArr)
{
    mkdir("./resultError",0777);                //创建生成结果的目录

    //计算指定长度对两个数组中值的差值：
    for(int i = 0;i < ARR_CNT;++i)
    {
        clacArrDiff((float *)(soucePtrArr[i]),(float *)(resultPtrArr[i]),lenArr[i],i);
    }
}
