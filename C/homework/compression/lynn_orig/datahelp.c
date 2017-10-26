/*
*  @brief   生成随机数函数
*  @param   参数1作为下限，参数2作为上限
*  @return  返回一个范围内的随机数（包括上限和下限）
*/
int generateRandomNum(int lowerLimit,int upperLimit)
{
    int range = upperLimit - lowerLimit + 1;                    //计算随机数的范围
    int randomNum =  rand() % range + lowerLimit;               //生成随机数
    return randomNum;                                           //将生成的随机数作为返回值返回
}


/*
*  @brief   将一个范围内的值映射到另一个范围中
*  @param   参数1是待映射范围的下限
*           参数2是待映射范围的上限
*           参数3是源范围的下限
*           参数4是源范围的上限
*           参数5是要映射的值
*  @return  返回整形的映射出来的值
*/
int clacMapValue(int mappingLowerLimit,int mappintUpperLimit,int sourceLowerLimit,int sourceUpperLimit,int mappingValue)
{
    double mappingRange = mappintUpperLimit - mappingLowerLimit + 1;       //要映射到的范围跨度
    double sourceRange = sourceUpperLimit - sourceLowerLimit + 1;          //源范围跨度
    int mappedValue;                                                       //映射后的值

    //判断是待映射的值是否为步长的整倍数，若是，实际算出的映射值要-1：
    if (mappingValue % (int)(sourceRange / mappingRange + 1) == 0)
    {
        mappedValue = mappingValue * mappingRange / sourceRange + mappingLowerLimit - 1;
    }
    else
    {
        mappedValue = mappingValue * mappingRange / sourceRange + mappingLowerLimit;
    }

    //  源范围远远大于映射范围时会有误差，将求出的大于映射范围的映射值全部当做映射范围最大值
    if (mappedValue > mappintUpperLimit)
    {
        mappedValue = mappintUpperLimit;
    }
    return mappedValue;                                                     //将映射出的值作为返回值返回
}


/*
*  @brief   求数组最大值
*  @param   参数1为数组头指针，参数2为数组元素个数
*  @return  数组中的最大值
*/
int getMaxNum(float *arr,int length)
{
    float maxNum = arr[0];
    for (int i = 1; i < length; ++i)
    {
        if( maxNum < arr[i])
            maxNum = arr[i];
    }
    return maxNum;
}


/*
*  @brief   求数组最小值
*  @param   参数1为数组头指针，参数2为数组元素个数
*  @return  数组中的最小值
*/

int getMinNum(float *arr,int length)
{
    float minNum = arr[0];
    for (int i = 1; i < length; ++i)
    {
        if( minNum > arr[i] )
            minNum = arr[i];
    }
    if ((int)minNum == 0)
    {
        minNum++;
    }
    return (int)minNum;
}


/*
*  @brief   将源目标地址开始的若干个字节复制到目标地址
*  @param   参数1为源地址
*           参数2为目标地址
*           参数3为复制的字节数
*  @return  N/A
*/
void cpyArr(char *soucePtr,char *destPtr,int length)
{
    for (int i = 0; i < length; ++i)
    {
        destPtr[i] = soucePtr[i];
    }
}


/*
*  @brief   向文件中写入固定长度的字符串
*  @param   参数1为存放文件名的数组（读到\0为止）
*           参数2为要写入的字符串
*           参数3为要写入的长度
*  @return  N/A
*/
void writeStrToFile(char *fileName,unsigned char *str,int length)
{
    int fd = open(fileName, O_WRONLY | O_CREAT,0777);
    write(fd, str, length);
    close(fd);
}


/*
*  @brief   生成两个float数组的数据差值并存到文件中
*  @param   参数1为被减数数组
*           参数2为减数数组
*           参数3为要比较的元素个数
*           参数4为文件名索引号
*  @return  N/A
*/
void clacArrDiff(float *firstArr,float *secondArr,int length,int fileNameIndex)
{
    char path[50];
    float result;

    //更新文件名字符串：
    sprintf(path,"./resultError/chip%03d.diff",fileNameIndex);

    //将结果写入文件：
    FILE *pf = NULL;

    //打开文件，若不存在则创建：
    pf = fopen(path,"a");

    for(int i=0; i<length; i++)
    {
        //计算差值结果：
        result = firstArr[i] - secondArr[i];
        //将差值结果写入文件：
        fprintf(pf,"  %.2f\n",result);
    }

    //关闭文件：
    fclose(pf);
}
