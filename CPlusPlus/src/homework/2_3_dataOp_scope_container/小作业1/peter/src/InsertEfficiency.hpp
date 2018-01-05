#ifndef INSERTEFFICIENCY_HPP
#define INSERTEFFICIENCY_HPP

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <list>
#include <chrono>

/**
 *  @brief insertVectorMiddle
 *      该函数功能是测试在vector中间插入数据的时间
 *  @param
 *      需要测试的数据类型
 * @param dataCnt
 *      需要测试的数据长度
 * @param testCnt
 *      需要测试的次数
 *  @return
 *      返回插入的时间
 */
template <typename T>
long double insertVectorMiddle(T dataType,int dataCnt,int testCnt)
{
    // 初始化
    std::vector<T> vects(dataCnt);
    for( int i = 0; i < dataCnt; ++i )
    {
       vects.emplace_back(dataType);
    }

    // 在vector中间插入元素
    typename std::vector<T>::iterator it = vects.begin();
    int midPos = dataCnt/2;
    long double vectorTime {0};
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    for (int i = 0; i < midPos; ++i)
    {
        it++;
    }
    for(int i = 0; i < testCnt; ++i)
    {
        start = std::chrono::system_clock::now();
        it = vects.insert(it,dataType);
        end = std::chrono::system_clock::now();
        vectorTime += std::chrono::duration<long double,std::milli>(end-start).count();
    }
    return vectorTime /= testCnt;
}

/**
 *  @brief insertListMiddle
 *      该函数功能是测试在list中间插入数据的时间
 *  @param
 *      需要测试的数据类型
 * @param dataCnt
 *      需要测试的数据长度
 * @param testCnt
 *      需要测试的次数
 *  @return
 *      返回插入的时间
 */
template <typename T>
long double insertListMiddle(T dataType,int dataCnt,int testCnt)
{
    // 初始化
    std::list<T> lists;
    for( int i = 0; i < dataCnt; ++i )
    {
       lists.push_back(dataType);
    }

    // 在list中间插入元素
    typename std::list<T>::iterator it = lists.begin();
    int midPos = dataCnt/2;
    for (int i = 0; i < midPos; ++i)
    {
        it++;
    }
    long double listTime {0};
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    for(int i = 0; i < testCnt; ++i)
    {
        start = std::chrono::system_clock::now();
        it = lists.insert(it,dataType);
        end = std::chrono::system_clock::now();
        listTime += std::chrono::duration<long double,std::milli>(end-start).count();
    }
    return listTime /= testCnt;
}

/**
 *  @brief insertArrayMiddle
 *      该函数功能是测试在array中间插入数据的时间
 *  @param
 *      需要测试的数据类型
 * @param dataCnt
 *      需要测试的数据长度
 * @param testCnt
 *      需要测试的次数
 *  @return
 *      返回插入的时间
 */
template <typename T>
long double insertArrayMiddle(T dataType,int dataCnt,int testCnt)
{
    // 初始化
    T arrays[dataCnt];
    for( int i = 0; i < dataCnt; ++i )
    {
       arrays[i] = dataType;
    }

    // 在array中间插入元素
    int midPos = dataCnt/2;
    int newSize = dataCnt+1;
    long double arrayTime {0};
    T newArrays[newSize];
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();
    for(int i = 0; i < testCnt; ++i)
    {
        start = std::chrono::system_clock::now();
        for(int j =0; j < newSize; ++j)
        {
            if( j < midPos )
            {
                newArrays[j] = arrays[j];
            }
            else if ( j > midPos )
            {
                newArrays[j] = arrays[j-1];
            }
            else
            {
                newArrays[j] = dataType;
            }

        }
        end = std::chrono::system_clock::now();
        arrayTime += std::chrono::duration<long double,std::milli>(end-start).count();
    }
    return arrayTime /= testCnt;
}


#endif // INSERTEFFICIENCY_HPP
