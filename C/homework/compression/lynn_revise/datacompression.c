#include "datacompression.h"

void compressSingleArr(unsigned char destArr[],float srcArr[],int length)
{
    //生成表头：
    short *pHeader; //由于存入数组是byte型，表头数据为short，故需一个写表头用的short指针
    pHeader = (short*)destArr;
    pHeader[0] = (short)length;
    pHeader[1] = calcMin(length,srcArr);
    pHeader[2] = calcMax(length,srcArr);

    //遍历压缩数组中的元素：
    for (int i = 0; i < length; ++i)
    {
        //rime 这里为什么不一个参数一行或者全部一行
        destArr[HEADER_LENGTH + i] = mapFloatToByte(srcArr[i],pHeader[1],\
                pHeader[2]);
    }
}


//lynn171103:a.将该函数中所有写死的路径和文件名前缀改为了配置文件中宏定义的路径。
//           b.该函数中压缩数组有较多重复代码，添加了函数compressSingleArr。
//           c.修改了无效果的防呆，修改代码大体逻辑，使其能够压缩不止两个数组。
void compressAndExportData(int lenArr[], float **pData)
{
    //lynn171103:将变量名fileName改为path

    //rime 看你的命名完全看不出是你注释中的这层意思
    char command[50];                           // 用于删除目录的shell命令
    char path[50];                              // 生成文件的路径

    //rime 就不能解释解释清楚么, 这么重要的一个变量, 我理解的没错的话, 应该是用来确认数组是否需要合并, 每次合并后就需要重置为0
    int bufferArrLen = 0;                       // 缓存数组的总长度
    int bufferIndexArr[10];                     // 存放缓存数组索引号的数组
    int bufferArrCnt=0;                         // 缓存数组的个数

    //rime 为什么是10000, 解释在哪里
    unsigned char compressionDataArr[10000];    // 压缩出的数据的占存数组

    //生成用来删除目录的shell命令字符串
    sprintf(command,"rm -rf %s",COMPRESSION_DATA_PATH);

    //调用shell命令删除原来的数据目录
    system(command);

    mkdir(COMPRESSION_DATA_PATH,0777);          // 创建用于存放压缩出文件的目录

    clock_t startTime = clock();                // 记录数据压缩及导出开始时间
    for ( int i = 0; i < FLOAT_ARR_CNT; ++i )   // 遍历压缩所有要压缩的数据数组
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1 当数组长度大于等于4096时，压缩并导出该数组
        if ( lenArr[i] >= COMPRESSION_LIMIT )
        {
            // 压缩此数组
            compressionDataArr[0] = 1;          // 数组个数置为1(压缩出内容的第一位)
            compressSingleArr(&(compressionDataArr[1]),pData[i],lenArr[i]);

            // 生成保存文件的路径
            sprintf(path, "%s%s%03d",COMPRESSION_DATA_PATH,FILE_PREFIX,i);

            // 导出到文件
            writeDataToFile(path, compressionDataArr,1 + HEADER_LENGTH + \
                            lenArr[i]);
        }

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.当数组长度小于4096时，记录该数组的信息，不进行压缩、导出操作
        else
        {
            bufferIndexArr[bufferArrCnt]=i;     // 将当前数组的索引号存储
            bufferArrLen+=lenArr[i];            // 在总长度上加上当前数组的长度
            bufferArrCnt++;                     // 准备压缩的数组数量加一
        }

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //3.判断缓存的数组总长度是否达到4096，或者是否无别的数据要压缩了并且仍存在缓存数组，
        //  若存在，则压缩这些数组并导出到文件：
        int compressedDataLength;               // 已压缩的数据的长度
        //rime 这里的判断逻辑比较乱, 最好一行一个
        if(bufferArrLen >= COMPRESSION_LIMIT || ((bufferArrLen != 0)&&\
                                                (i == FLOAT_ARR_CNT - 1)))
        {
            path[0] = '\0';                     // 初始化路径
            compressionDataArr[0] = bufferArrCnt;   // 存入压缩数组个数
            compressedDataLength= 1;            // 已压缩数据长度设置为1

            // 循环压缩所有数据：
            for (int j = 0; j < bufferArrCnt; ++j)
            {
                // 压缩该数组：
                compressSingleArr(&(compressionDataArr[compressedDataLength]),\
                    pData[bufferIndexArr[j]],(int)lenArr[bufferIndexArr[j]]);

                // 更新已压缩数据的长度：
                //rime 为什么是6, 为什么不解释清楚,
                compressedDataLength = compressedDataLength + 6 + \
                    lenArr[bufferIndexArr[j]];

                // 更新文件名：
                sprintf(path,"%s_%s%03d",path,FILE_PREFIX,bufferIndexArr[j]);
            }

            // 更新生成文件路径：
            char temp[50];                      // 临时存储一下生成文件的路径
            strcpy(temp,path);
            sprintf(path,"%s%s",COMPRESSION_DATA_PATH,&(temp[1]));

            // 将压缩出的数据导出到文件：
            writeDataToFile(path, compressionDataArr,compressedDataLength);
            bufferArrLen = 0;                   // 缓存数组的长度清零
            bufferArrCnt = 0;                   // 缓存数组的个数清零
        }
    }   //end of "for ( int i = 0; i < FLOAT_ARR_CNT; ++i )"
    clock_t endTime = clock();                      // 记录数据压缩及导出结束时间
    printf("压缩并导出数据所用的时间：%f s\n",(double)(endTime - startTime) / \
           CLOCKS_PER_SEC);
}


//lynn171103:a.将该函数中所有写死的路径和文件名前缀改为了配置文件中宏定义的路径
//           b.存在重复代码，添加了函数deCompressSingleArr
//           c.修改代码逻辑，可以解压缩更多数组压缩成的数据
void importAndDecompressData(int lenArr[], float **pDecompressionData)
{
    DIR *pDir;
    //rime 为什么是50 这是一个魔数
    char path[50];                              // 打开文件的路径
    unsigned char compressionDataArr[10000];    // 存放文件中数据的数组
    int arrIdx;                                 // 准备解压的数组的索引号
    int decompressedDatalen;                    // 已解压缩数据的长度 //rime decompressedDatalen -> decompressedDataLen
    short *pHeader; //由于源数据是byte型，而表头数据为short，故需一个取表头用的short指针
    struct dirent *file;// rime 这里的命名不对

    clock_t startTime = clock();                // 记录导入并解压缩数据开始时间

    pDir = opendir(COMPRESSION_DATA_PATH);      // 打开目录

    // 逐个读取目录下的文件
    while( (file = readdir(pDir)) != NULL )
    {
        // 1.排除"."或".."之类的隐藏目录
        if(strncmp(file->d_name, ".", 1) == 0)
        {
            continue;
        }
        // 2.通过文件名生成打开文件的路径
        sprintf(path,"%s%s",COMPRESSION_DATA_PATH,file->d_name);

        // 3.打开文件 rime 为什么返回不是指针确实p开头的
        int pFile=open(path, O_RDONLY, 10000);  // 打开文件

        // 4.读取并解压缩该文件中的数据
        if ( pFile != -1 )                      // 判断文件是否打开成功
        {
            // 4.1读取文件
            read(pFile, compressionDataArr, 10000);
            decompressedDatalen = 1;            // 已压缩数据长度改为1

            // 4.2解压缩当前文件中的所有数据：
            for(int j = 0;file->d_name[j] != '\0'; ++j) //通过文件名判断压缩数组个数
            {
                //通过文件名生成数组索引号并解压缩数据：
                if(file->d_name[j] >= '0' && file->d_name[j] <='9')
                {
                    //更新索引号：
                    arrIdx = atoi(&file->d_name[j]);
                    j += 2;                     // 三字符构成一个索引，所以偏移+2

                    //更新表头指针：
                    pHeader = (short*)&(compressionDataArr[decompressedDatalen]);
                    decompressedDatalen += HEADER_LENGTH;

                    //开辟存储解压缩后数组的空间：
                    pDecompressionData[arrIdx]=malloc(sizeof(float)*pHeader[0]);

                    if(NULL != pDecompressionData[arrIdx])  //若内存开辟成功
                    {
                        //保存当前索引号数组的长度：
                        lenArr[arrIdx] = (int)pHeader[0];

                        //解压缩当前索引号数组：
                        for(int i = 0; i < (int)pHeader[0]; ++i)
                        {
                            pDecompressionData[arrIdx][i] =mapByteToFloat\
                                    (compressionDataArr[decompressedDatalen++],\
                                    (int)pHeader[1],(int)pHeader[2]);
                        }
                    }
                }
            }
        }           //end of  "if ( pFile != -1 )"   //rime +1 对于长循环的, 知道在最后一个}打上标示, 值得鼓励, 但请紧挨着}
    }               //end of "while( (file = readdir(pDir)) != NULL )"
    closedir(pDir); // 关闭目录
    clock_t endTime = clock();                  // 记录导入并解压缩数据结束时间
    printf("导入并解压缩数据所用时间：%f s\n",(double)(endTime - startTime) / \
           CLOCKS_PER_SEC);
}


void calcDataDiff(int lenArr[], float **pSrcData,float **pNewData)
{
    char path[50];                              // 生成的文件的路径
    float diffValue;                            // 计算出的原数据和新数据的差值
    char fileSuffix[]="_diff";                  // 生成的文件的后缀
    char command[50];                           // 用于删除目录的shell命令

    //生成用来删除目录的shell命令字符串
    sprintf(command,"rm -rf %s",DIFF_PATH);

    //调用shell命令删除原来的数据目录
    system(command);

    mkdir(DIFF_PATH,0777);                      // 创建目录

    for( int i = 0; i < FLOAT_ARR_CNT; ++i )    // 遍历所有数组
    {
        // 1.更新文件名字符串：
        sprintf(path, "%s%s%03d%s",DIFF_PATH,FILE_PREFIX,i,fileSuffix);

        // 2.打开文件：
        FILE *pFile = NULL;
        pFile = fopen( path, "a" );             // 打开文件，若不存在则创建

        // 3.计算差值结果并写入文件：
        for( int j = 0; j < lenArr[i]; ++j )    // 遍历数组中的所有元素
        {
            diffValue = pSrcData[i][j] - pNewData[i][j];   // 计算差值
            fprintf(pFile, "  %.2f\n", diffValue);         // 将差值结果写入文件
        }

        // 4.关闭文件
        fclose(pFile);
        pFile = NULL;
    }
}


void dispose(float **pGenerationData,float **pDecompressionData)
{
    //1.释放用于实际存放数据的空间：
    for ( int i = 0; i < FLOAT_ARR_CNT; ++i )
    {
        //1.1释放生成的数据的存储空间：
        free(pGenerationData[i]);
        pGenerationData[i] = NULL;

        //1.2释放解压缩数据的存储空间：
        free(pDecompressionData[i]);
        pDecompressionData[i] = NULL;
    }

    //2.释放用于记录头指针的空间：
    free(pGenerationData);
    pGenerationData = NULL;

    free(pDecompressionData);
    pDecompressionData = NULL;
}
