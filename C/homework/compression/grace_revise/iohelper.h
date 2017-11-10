#ifndef IOHELPER_H
#define IOHELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

//rime +1 这个IOHelper划分基本合理

/*
 * //rime 如果是递归最好加上recursively, 这种很中性的名字别人第一反应就是仅仅删除目录而已
*  @brief 递归删除目录(删除该目录以及该目录包含的文件和目录)
*  @param dir:要删除的目录绝对路径 //rime 既然是指针, 为什么不加p
*  @return 0：正常退出 //rime 返回值也要对齐啊
*          -1：异常退出
*/
int removeDir(const char *dir);

/*
*  @brief 导出浮点型数据到文件
*  @param outputName：导出的文件名  //rime 参数名也要对齐
*         pCompressedArr：导出的浮点型数据地址
*         length：导出数据长度
*  @return NA
*/
void writeToFile( char* outputName,  //rime 下面都知道加p,这里怎么不加p了呢
                   unsigned char* pCompressedArr, //rime 既然是一个导出数据到目录, 这应该是比较底层的函数, 可以被其它模块调用, 而不仅仅是压缩模块, 所以为什么要加上compressed
                   int length );
/*
*  @brief 导入文件数据
*  @param pFileData:存储文件中数据 //rime 可以就叫pData就可以了, 这里和file没有啥联系
*         pFileName：要读取文件的名 //rime 这应该是路径把, 而不是文件名, 这个一定要明确清楚, 否则很容易引起歧义
*  @return NA
*/
void readFromFile(int* pFileData,char* fileName);
#endif // IOHELPER_H
