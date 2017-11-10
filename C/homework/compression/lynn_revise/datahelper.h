#ifndef DATAHELPER_H
#define DATAHELPER_H

#include <fcntl.h>
#include <unistd.h>

#define MAPPING_MAX_VALUE 255  // 映射的最大值（由于是映射到byte型数据，最大能存放到255）

//rime +1 把泛用的函数单独封装成一个文件供其他模块调用是值得鼓励的做法, 同时封装的函数具有足够
//的泛用性

//lynn:171030 a.将变量名floatArr改为了array
//            b.将float *array 修改为float array[]
//            c.将所有的minimum改为min
// a修改原因:函数参数类型没必要写到参数名中，型参中很容易看出来。
// b修改原因:函数参数为数组时用“float xxArray[]”格式，为指针时用"float *pXx"格式更好。
// ps:后面有多出类似问题，原因不再一一列出
/*
*  @brief   计算数组中的最小值
*  @param   arrLength :数组长度 //rime 为什么参数的注释不对齐,包括不同的返回值注释说明也需要对齐
*           array     :要找出最小值的数组
*  @return  数组中的最小值
*/
short calcMin(int arrLength, float array[]);//rime 找最大值最小值不是calc, 而是find


//lynn:171030 a.将变量名floatArr改为了array
//            b.将float *array 修改为float array[]
//            c.将所有的maximum改为max
/*
*  @brief   计算数组中的最大值
*  @param   arrLength :数组长度
*           array     :要找出最大值的数组
*  @return  数组中的最大值
*/
short calcMax(int arrLength, float array[]);//rime arr要缩写就一样缩写了,为什么不统一


//lynn:171031:a.将参数名fileName改为path
//            b.参数名byreArr改为dataArr
//            c.参数名byteArrLength改为length
//            d.将函数名从exportData改为writeDataToFile，这样更符合函数的单一性
//            e.修改了函数注释，更好的说明函数的用意
/*
*  @brief   将指定长度的数据写入指定路径
*  @param   path    :写入的路径
*           dataArr :数据数组
*           length  :数组的长度
*  @return  N/A
*/
void writeDataToFile(char *path, unsigned char dataArr[], int length);//rime 为什么上面的函数都是array和arrLength, 这里又编程了dataArr了?


//lynn171101:a.将函数名从calcMappedData改为mapFloatToByte
//           b.将参数floatData改为srcData
//           c.将参数minium改为min
//           d.将参数maxium改为max
//           e.将函数返回类型由char改为了unsigned char,此处虽然不会产生错误，但是函数里面
//             return的是一个unsigned char型的数据，最好保持一致。
//           f.修改了函数注释，更好的说明函数的用意
/*
*  @brief   将一个float型的数值映射为char型
*           （mapByteToFloat函数可以还原数据，但是会产生误差，数据敏感处慎用）//rime 啥叫数据敏感? 你可以说是精度要求高的地方慎用
*  @param   srcData :准备映射的源数据
*           min     :源映射范围的下限
*           max     :源映射范围的上限
*  @return  映射成char型的数据
*/
unsigned char mapFloatToByte(float srcData, short min, short max);


//lynn171101:a.将函数名从calcDecompressedData改为mapByteToFloat
//           b.将参数byteData改为srcData
//           c.将参数minium改为min
//           d.将参数maxium改为max
//           e.这里float byteData不合理，用unsigned char更合理
//           f.修改了函数注释，更好的说明函数的用意
/*
*  @brief   计算解压后的数据
*  @param   srcData :准备映射的源数据
*           min     :映射目标范围的下限
*           max     :映射目标范围的上限
*  @return  映射后的数据
*/
float mapByteToFloat(unsigned char srcData, short min, short max);

#endif // DATAHELPER_H

