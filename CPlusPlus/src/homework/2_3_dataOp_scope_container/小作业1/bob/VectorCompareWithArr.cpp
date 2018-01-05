#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <string.h>

using namespace std;

//>>>---------------------------------------------------------------------------------------------------------------------------------------------
//将数据写入动态数组

/**
*  @brief fillByteVector
*          向byte形动态数组中填充数据
*  @param  byteVector:需要写入数据的byte型动态数组
*           objCnt: 动态数组中元素的个数
*  @return N/A
*/
void fillByteVector(vector<char>& byteVector,
                    int objCnt)
{
    char objValue = 1;

    for (int i = 0; i < objCnt; ++i)
    {
        byteVector.push_back(objValue);
    }
}

/**
*  @brief fillIntVector
*          向int形动态数组中填充数据
*  @param  intVector:需要写入数据的int型动态数组
*           objCnt: 动态数组中元素的个数
*  @return N/A
*/
void fillIntVector(vector<int>& intVector,
                   int objCnt)
{
    int objValue = 1;

    for (int i = 0; i < objCnt; ++i)
    {
        intVector.push_back(objValue);
    }
}

/**
*  @brief fillLongIntVector
*          向long int形动态数组中填充数据
*  @param  longIntVector:需要写入数据的long int型动态数组
*           objCnt: 动态数组中元素的个数
*  @return N/A
*/
void fillLongIntVector(vector<long int>& longIntVector,
                        int objCnt)
{
    long int objValue = 1;

    for (int i = 0; i < objCnt; ++i)
    {
        longIntVector.push_back(objValue);
    }
}

//<<<---------------------------------------------------------------------------------------------------------------------------------------------

//>>>---------------------------------------------------------------------------------------------------------------------------------------------
//访问并访问动态数组最后一个元素

/**
*  @brief accessByteVectorLastestObj
*           访问byte型动态数组中最后一个元素
*  @param byteVector:需要访问最后一个元素的byte形动态数组
*  @return N/A
*/
void accessByteVectorLastestObj(vector<char>& byteVector)
{
    char tmp = byteVector.back();
}

/**
*  @brief accessVectorLastestObj
*           访问int型动态数组中最后一个元素
*  @param intVector:需要访问最后一个元素的int形动态数组
*  @return N/A
*/
void accessVectorLastestObj(vector<int>& intVector)
{
    int tmp = intVector.back();
}

/**
*  @brief accessVectorLastestObj
*           访问long int型动态数组中最后一个元素
*  @param longIntVector:需要访问最后一个元素的long int形动态数组
*  @return N/A
*/
void accessLongIntVectorLastestObj(vector<long int>& longIntVector)
{
    long int tmp = longIntVector.back();
}
//<<<---------------------------------------------------------------------------------------------------------------------------------------------

//>>>---------------------------------------------------------------------------------------------------------------------------------------------
//向动态数组末尾插入一个元素

/**
*  @brief insertObjToByteVector
*           向byte型动态数组末尾插入一个元素
*  @param byteVector:需要插入一个元素的byte形动态数组
*           objCnt: 动态数组中元素的个数
*  @return N/A
*/
void insertObjToByteVector(vector<char>& byteVector)
{
    char objValue = 1;
    byteVector.insert(byteVector.end(),objValue);
}

/**
*  @brief insertObjToIntVector
*           向int型动态数组末尾插入一个元素
*  @param intVector:需要插入一个元素的int形动态数组
*           objCnt: 动态数组中元素的个数
*  @return N/A
*/
void insertObjToIntVector(vector<int>& intVector)
{
    int objValue = 1;
    intVector.insert(intVector.end(),objValue);
}

/**
*  @brief insertObjToLongIntVector
*           向long int型动态数组末尾插入一个元素
*  @param longIntVector:需要插入一个元素的long int形动态数组
*           objCnt: 动态数组中元素的个数
*  @return N/A
*/
void insertObjToLongIntVector(vector<long int>& longIntVector)
{
    long int objValue = 1;
    longIntVector.insert(longIntVector.end(),objValue);
}

//<<<---------------------------------------------------------------------------------------------------------------------------------------------

//>>>---------------------------------------------------------------------------------------------------------------------------------------------
//将数据写入数组

/**
*  @brief fillByteArr
*          向byte形数组中填充数据
*  @param  byteArr:需要写入数据的byte型数组
*           objCnt: 数组中元素的个数
*  @return N/A
*/
void fillByteArr(char byteArr[],
                  int objCnt)
{
    char objValue = 1;

    for (int i = 0; i < objCnt; ++i)
    {
        byteArr[i] = objValue;
    }
}

/**
*  @brief fillIntList
*          向int形数组中填充数据
*  @param  intArr:需要写入数据的int型数组
*           objCnt: 数组中元素的个数
*  @return N/A
*/
void fillIntArr(int intArr[],
                 int objCnt)
{
    int objValue = 1;

    for (int i = 0; i < objCnt; ++i)
    {
        intArr[i] = objValue;
    }
}

/**
*  @brief fillLongIntArr
*          向long int形数组中填充数据
*  @param  intArr:需要写入数据的int型数组
*           objCnt: 数组中元素的个数
*  @return N/A
*/
void fillLongIntArr(long int longIntArr[],
                    int objCnt)
{
    int objValue = 1;

    for (int i = 0; i < objCnt; ++i)
    {
        longIntArr[i] = objValue;
    }
}
//<<<---------------------------------------------------------------------------------------------------------------------------------------------

//>>>---------------------------------------------------------------------------------------------------------------------------------------------
//访问数组中最后一个元素

/**
*  @brief accessByteListLastestObj
*           访问出byte型数组中最后一个元素
*  @param  byteArr:需要写入数据的byte型数组
*           objCnt: 数组中元素的个数
*  @return N/A
*/
void accessByteArrLastestObj(char byteArr[],
                             int objCnt)
{
    char tmp = byteArr[objCnt-1];
}

/**
*  @brief accessIntArrLastestObj
*           访问出int型数组中最后一个元素
*  @param  intArr:需要写入数据的int型数组
*           objCnt: 数组中元素的个数
*  @return N/A
*/
void accessIntArrLastestObj(int intArr[],
                            int objCnt)
{
    char tmp = intArr[objCnt-1];
}

/**
*  @brief accessLongIntArrLastestObj
*           访问出long int型数组中最后一个元素
*  @param  intArr:需要写入数据的int型数组
*           objCnt: 数组中元素的个数
*  @return N/A
*/
void accessLongIntArrLastestObj(long int longIntArr[],
                                int objCnt)
{
    char tmp = longIntArr[objCnt-1];
}

//<<<---------------------------------------------------------------------------------------------------------------------------------------------

//>>>---------------------------------------------------------------------------------------------------------------------------------------------
//向list中末尾插入一个元素

/**
*  @brief insertObjToByteArr
*           向byte型数组末尾插入一个元素
*  @param byteArr:需要插入一个元素的byte形数组
*          objCnt:数组中元素的数量
*  @return N/A
*/
void insertObjToByteArr(char *& byteArr,
                        int objCnt)
{
    char objValue = 1;
    char tempArr[objCnt];
    memcpy(tempArr,byteArr,objCnt);
    delete [] byteArr;
    byteArr = new char[objCnt+1];
    memcpy(byteArr,tempArr,objCnt);
    byteArr[objCnt] = objValue;
}

/**
*  @brief insertObjToIntArr
*           向int型数组末尾插入一个元素
*  @param intArr:需要插入一个元素的int形数组
*          objCnt:数组中元素的数量
*  @return N/A
*/
void insertObjToIntArr(int *& intArr,
                        int objCnt)
{
    int objValue = 1;
    int tempArr[objCnt];
    memcpy(tempArr,intArr,objCnt);
    delete [] intArr;
    intArr = new int[objCnt+1];
    memcpy(intArr,tempArr,objCnt);
    intArr[objCnt] = objValue;
}

/**
*  @brief insertObjToLongIntArr
*           向long int型数组末尾插入一个元素
*  @param longIntArr:需要插入一个元素的long int形数组
*          objCnt:数组中元素的数量
*  @return N/A
*/
void insertObjToLongIntArr(long int *& longIntArr,
                           int objCnt)
{
    long int objValue = 1;
    long int tempArr[objCnt];
    memcpy(tempArr,longIntArr,objCnt);
    delete [] longIntArr;
    longIntArr = new long int[objCnt+1];
    memcpy(longIntArr,tempArr,objCnt);
    longIntArr[objCnt] = objValue;
}

int main()
{
    int objCnt = 20000;
    cout << "对比动态数组与数组中访问数据与插入数据的差异,数组中元素数量为:"
         <<objCnt << "\n"<<endl;

    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
    //step1 统计访问动态数组最后一个元素的时间

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step1.1统计访问byte动态数组中最后一个元素的时间

        vector<char> byteVector;
        byteVector.reserve(objCnt);

        fillByteVector(byteVector,objCnt);

        auto start = std::chrono::steady_clock::now();
        accessByteVectorLastestObj(byteVector);
        auto end = std::chrono::steady_clock::now();
        double time = std::chrono::duration<double,milli>(end-start).count();

        cout << "访问Byte动态数组最后一个元素的时间为: "<<time <<"ms"<<endl;

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step1.2统计访问Int动态数组中最后一个元素的时间

        vector<int> intVector;
        intVector.reserve(objCnt);

        fillIntVector(intVector,objCnt);

        start = std::chrono::steady_clock::now();
        accessVectorLastestObj(intVector);
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double,milli>(end-start).count();

        cout << "访问int动态数组最后一个元素的时间为: "<<time <<"ms"<<endl;

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step1.3统计访问Long Int动态数组中最后一个元素的时间

        vector<long int> longIntVector;
        longIntVector.reserve(objCnt);

        fillLongIntVector(longIntVector,objCnt);

        start = std::chrono::steady_clock::now();
        accessLongIntVectorLastestObj(longIntVector);
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double,milli>(end-start).count();

        cout << "访问long int动态数组最后一个元素的时间为: "<<time <<"ms"<<endl;

    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
    //step2统计向动态数组末尾插入一个元素的时间

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step2.1统计Byte动态数组末尾插入一个元素时间

        start = std::chrono::steady_clock::now();
        insertObjToByteVector(byteVector);
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double,milli>(end-start).count();
        cout << "向Byte动态数组末尾插入一个元素时间: "<<time <<"ms"<<endl;

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step2.2统计Int动态数组末尾插入一个元素时间
        start = std::chrono::steady_clock::now();
        insertObjToIntVector(intVector);
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double,milli>(end-start).count();
        cout << "向int动态数组末尾插入一个元素时间: "<<time <<"ms"<<endl;

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step2.3统计long int动态数组末尾插入一个元素时间
        start = std::chrono::steady_clock::now();
        insertObjToLongIntVector(longIntVector);
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double,milli>(end-start).count();
        cout << "向long int动态数组末尾插入一个元素时间: "<<time <<"ms"<<endl;
    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    cout<<"\n";

    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
    //step3 统计读取list最后一个元素的时间

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step3.1统计读取byte型数组中最后一个元素的时间

        char *byteArr = new char[objCnt];

        fillByteArr(byteArr,objCnt);

        start = std::chrono::steady_clock::now();
        accessByteArrLastestObj(byteArr,objCnt);
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double,milli>(end-start).count();

        cout << "访问Byte型数组最后一个元素的时间为: "<<time <<"ms"<<endl;

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step3.2统计读取Int型数组中最后一个元素的时间

        int *intArr = new int[objCnt];

        fillIntArr(intArr,objCnt);

        start = std::chrono::steady_clock::now();
        accessIntArrLastestObj(intArr,objCnt);
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double,milli>(end-start).count();

        cout << "访问int型数组最后一个元素的时间为: "<<time <<"ms"<<endl;


        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step3.3统计读取Long Int型数组中最后一个元素的时间

        long int * longIntArr = new long int[objCnt];

        fillLongIntArr(longIntArr,objCnt);

        start = std::chrono::steady_clock::now();
        accessLongIntArrLastestObj(longIntArr,objCnt);
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double,milli>(end-start).count();

        cout << "访问long int型数组最后一个元素的时间为: "<<time <<"ms"<<endl;

    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
    //step4统计向数组中间插入一个元素的时间

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step4.1统计Byte数组末尾插入一个元素时间

        start = std::chrono::steady_clock::now();
        insertObjToByteArr(byteArr,objCnt);
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double,milli>(end-start).count();
        cout << "向Byte型数组末尾插入一个元素时间: "<<time <<"ms"<<endl;

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step4.2统计int数组末尾插入一个元素时间

        start = std::chrono::steady_clock::now();
        insertObjToIntArr(intArr,objCnt);
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double,milli>(end-start).count();
        cout << "向int型list末尾插入一个元素时间: "<<time <<"ms"<<endl;

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step4.2统计long int数组末尾插入一个元素时间

        start = std::chrono::steady_clock::now();
        insertObjToLongIntArr(longIntArr,objCnt);
        end = std::chrono::steady_clock::now();
        time = std::chrono::duration<double,milli>(end-start).count();
        cout << "向int型list末尾插入一个元素时间: "<<time <<"ms"<<endl;

    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    delete [] byteArr;
    delete [] intArr;
    delete [] longIntArr;

    byteArr = nullptr;
    intArr = nullptr;
    longIntArr = nullptr;

    return 0;
}

