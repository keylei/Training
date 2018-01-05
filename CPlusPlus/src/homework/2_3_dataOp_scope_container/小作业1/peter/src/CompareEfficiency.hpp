#ifndef TESTEFFICIENCY_HPP
#define TESTEFFICIENCY_HPP

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <list>
#include <chrono>

#include "ReadEfficiency.hpp"
#include "InsertEfficiency.hpp"

using namespace std;

/**
 *  @brief OneByte
 *      该结构体表示一个字节的数据类型
 *  @author peter
 *  @version 1.00 2018-01-01 peter
 *                note:create it
 */
struct OneByte
{
    u_char oneByte;
};
/**
 *  @brief OneByte
 *      该结构体表示4096字节的数据类型
 *  @author peter
 *  @version 1.00 2018-01-01 peter
 *                note:create it
 */
struct FourKb
{
    int fourKB[1024];
};
/**
 *  @brief OneByte
 *      该结构体表示8192字节的数据类型
 *  @author peter
 *  @version 1.00 2018-01-01 peter
 *                note:create it
 */
struct EightKb
{
    int eightKb[2048];
};

/**
 * @brief compareVectorAndListEfficiency
 *      该函数的功能是比较vector和list的时间长短
 *  1.读取最后一个元素的时间
 *  2.在容器中间插入一个元素的时间
 * @param dataCnt
 *      数据长度
 * @param testCnt
 *      测试次数
 * @return N/A
 */
void compareVectorAndListEfficiency(int dataCnt,int testCnt)
{
    OneByte onebyte;
    FourKb fourKbByte;
    EightKb eightKbByte;
    int margin {20};    // 打印到屏幕时两字段间隔

    // vector 和 list 读取最后一个元素的时间
    cout << "读取长度为" << dataCnt << "的容器的最后一个元素(单位:ns)" << endl;
    cout << setw(margin) << left << " "
         << setw(margin) << left << "1B"
         << setw(margin) << left << "4KB"
         << setw(margin) << left << "8KB"
         << endl;

    cout << setw(margin) << left << "vector:"
         << setw(margin) << left << readFromTheVectorBack(onebyte,dataCnt,testCnt)
         << setw(margin) << left << readFromTheVectorBack(fourKbByte,dataCnt,testCnt)
         << setw(margin) << left << readFromTheVectorBack(eightKbByte,dataCnt,testCnt)
         << endl;

    cout << setw(margin) << left << "list:"
         << setw(margin) << left << readFromListBack(onebyte,dataCnt,testCnt)
         << setw(margin) << left << readFromListBack(fourKbByte,dataCnt,testCnt)
         << setw(margin) << left << readFromListBack(eightKbByte,dataCnt,testCnt)
         << endl;

    // vector 和 list 中间插入一个元素的时间
    cout << "\n在长度为" << dataCnt << "的容器中间插入一个元素(单位:ms)" << endl;
    cout << setw(margin) << left << " "
         << setw(margin) << left << "1B"
         << setw(margin) << left << "4KB"
         << setw(margin) << left << "8KB"
         << endl;

    cout << setw(margin) << left << "vector:"
         << setw(margin) << left << insertVectorMiddle(onebyte,dataCnt,testCnt)
         << setw(margin) << left << insertVectorMiddle(fourKbByte,dataCnt,testCnt)
         << setw(margin) << left << insertVectorMiddle(eightKbByte,dataCnt,testCnt)
         << endl;

    cout << setw(margin) << left << "list:"
         << setw(margin) << left << insertListMiddle(onebyte,dataCnt,testCnt)
         << setw(margin) << left << insertListMiddle(fourKbByte,dataCnt,testCnt)
         << setw(margin) << left << insertListMiddle(eightKbByte,dataCnt,testCnt)
         << endl;
}

/**
 * @brief compareVectorAndArrayEfficiency
 *      该函数的功能是比较vector和array的时间长短
 *  1.读取最后一个元素的时间
 *  2.在容器中间插入一个元素的时间
 * @param dataCnt
 *      数据长度
 * @param testCnt
 *      测试次数
 * @return N/A
 */
void compareVectorAndArrayEfficiency(int dataCnt,int testCnt)
{
    OneByte onebyte;
    FourKb fourKbByte;
    EightKb eightKbByte;
    int margin {20};    // 打印到屏幕时两字段间隔
    // vector 和 array 读取最后一个元素的时间
    cout << "读取长度为" << dataCnt << "的容器的最后一个元素(单位:ns)" << endl;
    cout << setw(margin) << left << " "
         << setw(margin) << left << "1B"
         << setw(margin) << left << "4KB"
         << setw(margin) << left << "8KB"
         << endl;

    cout << setw(margin) << left << "vector:"
         << setw(margin) << left << readFromTheVectorBack(onebyte,dataCnt,testCnt)
         << setw(margin) << left << readFromTheVectorBack(fourKbByte,dataCnt,testCnt)
         << setw(margin) << left << readFromTheVectorBack(eightKbByte,dataCnt,testCnt)
         << endl;

    cout << setw(margin) << left << "array:"
         << setw(margin) << left << readFromArrayBack(onebyte,dataCnt,testCnt)
         << setw(margin) << left << readFromArrayBack(fourKbByte,dataCnt,testCnt)
         << setw(margin) << left << readFromArrayBack(eightKbByte,dataCnt,testCnt)
         << endl;

    // vector 和 array 中间插入一个元素的时间
    cout << "\n在长度为" << dataCnt << "的容器中间插入一个元素(单位:ms)" << endl;
    cout << setw(margin) << left << " "
         << setw(margin) << left << "1B"
         << setw(margin) << left << "4KB"
         << setw(margin) << left << "8KB"
         << endl;

    cout << setw(margin) << left << "vector:"
         << setw(margin) << left << insertVectorMiddle(onebyte,dataCnt,testCnt)
         << setw(margin) << left << insertVectorMiddle(fourKbByte,dataCnt,testCnt)
         << setw(margin) << left << insertVectorMiddle(eightKbByte,dataCnt,testCnt)
         << endl;

    cout << setw(margin) << left << "array:"
         << setw(margin) << left << insertArrayMiddle(onebyte,dataCnt,testCnt)
         << setw(margin) << left << insertArrayMiddle(fourKbByte,dataCnt,testCnt)
         << setw(margin) << left << insertArrayMiddle(eightKbByte,dataCnt,testCnt)
         << endl;
}

#endif // TESTEFFICIENCY_HPP
