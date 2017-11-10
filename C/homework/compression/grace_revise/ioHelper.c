/**
 *  @brief 本文件由三个函数构成
 *         1.removeDir函数：删除目录及目录下文件和子目录
 *         2.writeToFile函数：写数据到文件中
 *         3.readFromFile函数
 *
 *  @author create by peter comment by grace
 *  @version 1.00 2017-11-08 author
 *                note:create it
 */
#include "iohelper.h"

int removeDir(const char* pDirPath) //grace171108 新增函数删除pDirPath目录
{
    char fileName[FILENAME_MAX];    //存放目录下的文件名
    DIR *dirPathPtr;                //待打开的目录
    struct dirent *filePath = NULL; //待打开的文件路径
    struct stat dirStat;

    if ( 0 != access(pDirPath, F_OK) )  //判断文件或目录是否存在 0代表存在 否则不存在
    {
        return 0;
    }
    if ( 0 > stat(pDirPath, &dirStat) )//判断文件状态，stat函数返回值：0正常，-1错误
    {
        perror("get directory stat error");
        return -1;
    }
    if ( S_ISREG(dirStat.st_mode) )      //文件直接删除
    {
        remove(pDirPath);
    }
    else if ( S_ISDIR(dirStat.st_mode) ) //目录，递归删除目录中内容
    {
        dirPathPtr = opendir(pDirPath);     //打开目录
        while ( (filePath = readdir(dirPathPtr)) != NULL )
        {
            //如果是当前目录"."或上层目录".."则继续循环，否则向下执行程序
            if ( (0 == strcmp(".", filePath->d_name)) || (0 == strcmp("..", filePath->d_name)) )
            {
                continue;
            }

            sprintf(fileName, "%s/%s", pDirPath, filePath->d_name);
            removeDir(fileName); //删除文件
        }
        closedir(dirPathPtr);//关闭当前目录
        rmdir(pDirPath);     //删除空目录
    }
    return 0;
}

void writeToFile( char* outputName, //grace171108 原来函数名是exportToFile
                   unsigned char* pCompressionByte,
                   int length )
{
    FILE *file = fopen( outputName, "w");  //打开文件，如果文件不存在则创建
    if ( file == NULL )
    {
        printf("open file error!\n");      //打开失败，打印错误信息
    }
    if (strstr(outputName, ".txt") == NULL)//把".txt"连接在outputName之后
    {
        fwrite (pCompressionByte , sizeof(unsigned char), length, file);//以二进制形式写入数据
    }
    else
    {
        for ( int i = 0; i < length; ++i ) //轮循数组
        {
            fprintf(file,"%d\n",*(pCompressionByte+i)); //将数组中的值输出的到文件中（文本形式）
        }
    }
    fclose(file); //关闭打开的文件
}

void readFromFile(int* pFileData,char* pFileName) //grace171108 从main()中拆出
{
    int fileData;                          //文件中数据
    FILE *file = fopen( pFileName, "rb+"); //打开文件流指针
    for ( int i = 0; (fileData = getc(file)) != EOF; ++i )
    {
        *(pFileData+i) = fileData;  //将值存在 pFileData 数组中
    }
    fclose(file);                   //关闭文件流指针
}
