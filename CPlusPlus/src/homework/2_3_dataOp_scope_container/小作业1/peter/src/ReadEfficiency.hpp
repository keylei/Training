#ifndef READEFFICIENCY_HPP
#define READEFFICIENCY_HPP

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <list>
#include <chrono>

/**
 *  @brief readFromTheVectorBack
 *      该函数功能是测试读取vector尾部数据的时间
 *  @param
 *      需要测试的数据类型
 * @param dataCnt
 *      需要测试的数据长度
 * @param testCnt
 *      需要测试的次数
 *  @return
 *      返回读取的时间
 */
template <typename T>
long double readFromTheVectorBack( T dataType,int dataCnt,int testCnt )
{
    // 初始化
    std::vector<T> vects(dataCnt);
    for( int i = 0; i < dataCnt; ++i )
    {
       vects.emplace_back(dataType);
    }

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    // 读取vector最后一个元素
    T lastVectorElement;
    long double vectorTime {0};

    for( int i = 0; i < testCnt; ++i )
    {
        start = std::chrono::steady_clock::now();
        lastVectorElement = vects[vects.size()-1];
        end = std::chrono::steady_clock::now();
        vectorTime += std::chrono::duration<long double,std::nano>(end-start).count();
    }
    return vectorTime /= testCnt;
}

/**
 *  @brief readFromListBack
 *      该函数功能是测试读取list尾部数据的时间
 *  @param
 *      需要测试的数据类型
 * @param dataCnt
 *      需要测试的数据长度
 * @param testCnt
 *      需要测试的次数
 *  @return
 *      返回读取的时间
 */
template <typename T>
long double readFromListBack( T dataType,int dataCnt,int testCnt )
{
    // 初始化
    std::list<T> lists;
    for( int i = 0; i < dataCnt; ++i )
    {
       lists.push_back(dataType);
    }

    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    // 读取list最后一个元素
    T lastListElement;
    long double listTime {0};

   double temp;

    for( int i = 0; i < testCnt; ++i )
    {
        start = std::chrono::steady_clock::now();
        lastListElement = lists.back();
        end = std::chrono::steady_clock::now();
        listTime += std::chrono::duration<long double,std::nano>(end-start).count();
    }
    return listTime /= testCnt;
}

/**
 *  @brief readFromArrayBack
 *      该函数功能是测试读取array尾部数据的时间
 *  @param
 *      需要测试的数据类型
 * @param dataCnt
 *      需要测试的数据长度
 * @param testCnt
 *      需要测试的次数
 *  @return
 *      返回读取的时间
 */
template <typename T>
long double readFromArrayBack( T dataType,int dataCnt,int testCnt)
{
    // 初始化
    T byteArr[dataCnt];
    for( int i = 0; i < dataCnt; ++i )
    {
       byteArr[i] = dataType;
    }

    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    // 读取array最后一个元素
    T lastArrElement;
    long double arrTime {0};

    for( int i = 0; i < testCnt; ++i )
    {
        start = std::chrono::system_clock::now();
        lastArrElement = byteArr[dataCnt-1];
        end = std::chrono::system_clock::now();
        arrTime += std::chrono::duration<long double,std::nano>(end-start).count();
    }
    return arrTime /= testCnt;
}


#endif // READEFFICIENCY_HPP
