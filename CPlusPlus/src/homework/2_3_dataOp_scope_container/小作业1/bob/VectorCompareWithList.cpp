//#include <iostream>
//#include <vector>
//#include <list>
//#include <chrono>

//using namespace std;

////>>>---------------------------------------------------------------------------------------------------------------------------------------------
////将数据写入动态数组

///**
//*  @brief fillByteVector
//*          向byte形动态数组中填充数据
//*  @param  byteVector:需要写入数据的byte型动态数组
//*           objCnt: 动态数组中元素的个数
//*  @return N/A
//*/
//void fillByteVector(vector<char>& byteVector,
//                    int objCnt)
//{
//    char objValue = 1;

//    for (int i = 0; i < objCnt; ++i)
//    {
//        byteVector.push_back(objValue);
//    }
//}

///**
//*  @brief fillIntVector
//*          向int形动态数组中填充数据
//*  @param  intVector:需要写入数据的int型动态数组
//*           objCnt: 动态数组中元素的个数
//*  @return N/A
//*/
//void fillIntVector(vector<int>& intVector,
//                   int objCnt)
//{
//    int objValue = 1;

//    for (int i = 0; i < objCnt; ++i)
//    {
//        intVector.push_back(objValue);
//    }
//}

///**
//*  @brief fillLongIntVector
//*          向long int形动态数组中填充数据
//*  @param  longIntVector:需要写入数据的long int型动态数组
//*           objCnt: 动态数组中元素的个数
//*  @return N/A
//*/
//void fillLongIntVector(vector<long int>& longIntVector,
//                        int objCnt)
//{
//    long int objValue = 1;

//    for (int i = 0; i < objCnt; ++i)
//    {
//        longIntVector.push_back(objValue);
//    }
//}

////<<<---------------------------------------------------------------------------------------------------------------------------------------------

////>>>---------------------------------------------------------------------------------------------------------------------------------------------
////访问并访问动态数组最后一个元素

///**
//*  @brief accessByteVectorLastestObj
//*           访问byte型动态数组中最后一个元素
//*  @param byteVector:需要访问最后一个元素的byte形动态数组
//*  @return N/A
//*/
//void accessByteVectorLastestObj(vector<char>& byteVector)
//{
//    char tmp = byteVector.back();
//}

///**
//*  @brief accessVectorLastestObj
//*           访问int型动态数组中最后一个元素
//*  @param intVector:需要访问最后一个元素的int形动态数组
//*  @return N/A
//*/
//void accessVectorLastestObj(vector<int>& intVector)
//{
//    int tmp = intVector.back();
//}

///**
//*  @brief accessVectorLastestObj
//*           访问long int型动态数组中最后一个元素
//*  @param longIntVector:需要访问最后一个元素的long int形动态数组
//*  @return N/A
//*/
//void accessLongIntVectorLastestObj(vector<long int>& longIntVector)
//{
//    long int tmp = longIntVector.back();
//}
////<<<---------------------------------------------------------------------------------------------------------------------------------------------

////>>>---------------------------------------------------------------------------------------------------------------------------------------------
////向动态数组末尾插入一个元素

///**
//*  @brief insertObjToByteVector
//*           向byte型动态数组末尾插入一个元素
//*  @param byteVector:需要插入一个元素的byte形动态数组
//*           objCnt: 动态数组中元素的个数
//*  @return N/A
//*/
//void insertObjToByteVector(vector<char>& byteVector)
//{
//    char objValue = 1;
//    byteVector.insert(byteVector.end(),objValue);
//}

///**
//*  @brief insertObjToIntVector
//*           向int型动态数组末尾插入一个元素
//*  @param intVector:需要插入一个元素的int形动态数组
//*           objCnt: 动态数组中元素的个数
//*  @return N/A
//*/
//void insertObjToIntVector(vector<int>& intVector)
//{
//    int objValue = 1;
//    intVector.insert(intVector.end(),objValue);
//}

///**
//*  @brief insertObjToLongIntVector
//*           向long int型动态数组末尾插入一个元素
//*  @param longIntVector:需要插入一个元素的long int形动态数组
//*           objCnt: 动态数组中元素的个数
//*  @return N/A
//*/
//void insertObjToLongIntVector(vector<long int>& longIntVector)
//{
//    long int objValue = 1;
//    longIntVector.insert(longIntVector.end(),objValue);
//}

////<<<---------------------------------------------------------------------------------------------------------------------------------------------

////>>>---------------------------------------------------------------------------------------------------------------------------------------------
////将数据写入list

///**
//*  @brief fillByteList
//*          向byte形list中填充数据
//*  @param  byteList:需要写入数据的byte型list
//*           objCnt: list中元素的个数
//*  @return N/A
//*/
//void fillByteList(list<char>& byteList,
//                  int objCnt)
//{
//    char objValue = 1;

//    for (int i = 0; i < objCnt; ++i)
//    {
//        byteList.push_back(objValue);
//    }
//}

///**
//*  @brief fillIntList
//*          向int形list中填充数据
//*  @param  intList:需要写入数据的int型list
//*           objCnt:list中元素的个数
//*  @return N/A
//*/
//void fillIntList(list<int>& intList,
//                 int objCnt)
//{
//    int objValue = 1;

//    for (int i = 0; i < objCnt; ++i)
//    {
//        intList.push_back(objValue);
//    }
//}

///**
//*  @brief fillLongIntList
//*          向long int形list中填充数据
//*  @param  longIntList:需要写入数据的long int型list
//*           objCnt:list中元素的个数
//*  @return N/A
//*/
//void fillLongIntList(list<long int>& longIntList,
//                     int objCnt)
//{
//    int objValue = 1;

//    for (int i = 0; i < objCnt; ++i)
//    {
//        longIntList.push_back(objValue);
//    }
//}
////<<<---------------------------------------------------------------------------------------------------------------------------------------------

////>>>---------------------------------------------------------------------------------------------------------------------------------------------
////访问list最后一个元素

///**
//*  @brief accessByteListLastestObj
//*           访问出byte型list中最后一个元素
//*  @param byteList:需要访问出最后一个元素的byte形list
//*  @return N/A
//*/
//void accessByteListLastestObj(list<char>& byteList)
//{
//    char tmp = byteList.back();
//}

///**
//*  @brief accessIntListLastestObj
//*           访问int型list中最后一个元素
//*  @param intList:需要访问出最后一个元素的int形list
//*  @return N/A
//*/
//void accessIntListLastestObj(list<int>& intList)
//{
//    int tmp = intList.back();
//}

///**
//*  @brief printLongIntListLastestObj
//*           访问long int型list中最后一个元素
//*  @param longIntList:需要访问出最后一个元素的long int形list
//*  @return N/A
//*/
//void accessLongIntListLastestObj(list<long int>& longIntList)
//{
//    long int tmp = longIntList.back();
//}
////<<<---------------------------------------------------------------------------------------------------------------------------------------------

////>>>---------------------------------------------------------------------------------------------------------------------------------------------
////向list中末尾插入一个元素

///**
//*  @brief insertObjToByteList
//*           向byte型list中间位置插入一个元素
//*  @param byteList:需要插入一个元素的byte形list
//*  @return N/A
//*/
//void insertObjToByteList(list<char>& byteList)
//{
//    char objValue = 1;
//    byteList.insert(byteList.end(),objValue);
//}

///**
//*  @brief insertObjToIntList
//*           向int型list中间位置插入一个元素
//*  @param intList:需要插入一个元素的int形list
//*  @return N/A
//*/
//void insertObjToIntList(list<int>& intList)
//{
//    int objValue = 1;
//    intList.insert(intList.end(),objValue);
//}

///**
//*  @brief insertObjToLongIntList
//*           向long int型list中间位置插入一个元素
//*  @param longIntList:需要插入一个元素的long int形list
//*  @return N/A
//*/
//void insertObjToLongIntList(list<long int>& longIntList)
//{
//    long int objValue = 1;
//    longIntList.insert(longIntList.end(),objValue);
//}

//int main()
//{
//    int objCnt = 20000000;

//    cout << "对比动态数组与list中访问数据与插入数据的差异,元素数量为:"
//         <<objCnt << "\n"<<endl;
//    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//    //step1 统计访问动态数组最后一个元素的时间

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step1.1统计访问byte动态数组中最后一个元素的时间

//        vector<char> byteVector;
//        byteVector.reserve(objCnt);

//        fillByteVector(byteVector,objCnt);

//        auto start = std::chrono::steady_clock::now();
//        accessByteVectorLastestObj(byteVector);
//        auto end = std::chrono::steady_clock::now();
//        double time = std::chrono::duration<double,milli>(end-start).count();

//        cout << "访问Byte动态数组最后一个元素的时间为: "<<time <<"ms"<<endl;

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step1.2统计访问Int动态数组中最后一个元素的时间

//        vector<int> intVector;
//        intVector.reserve(objCnt);

//        fillIntVector(intVector,objCnt);

//        start = std::chrono::steady_clock::now();
//        accessVectorLastestObj(intVector);
//        end = std::chrono::steady_clock::now();
//        time = std::chrono::duration<double,milli>(end-start).count();

//        cout << "访问int动态数组最后一个元素的时间为: "<<time <<"ms"<<endl;

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step1.3统计访问Long Int动态数组中最后一个元素的时间

//        vector<long int> longIntVector;
//        longIntVector.reserve(objCnt);

//        fillLongIntVector(longIntVector,objCnt);

//        start = std::chrono::steady_clock::now();
//        accessLongIntVectorLastestObj(longIntVector);
//        end = std::chrono::steady_clock::now();
//        time = std::chrono::duration<double,milli>(end-start).count();

//        cout << "访问long int动态数组最后一个元素的时间为: "<<time <<"ms"<<endl;

//    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

//    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//    //step2统计向动态数组末尾插入一个元素的时间

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step2.1统计Byte动态数组末尾插入一个元素时间

//        start = std::chrono::steady_clock::now();
//        insertObjToByteVector(byteVector);
//        end = std::chrono::steady_clock::now();
//        time = std::chrono::duration<double,milli>(end-start).count();
//        cout << "向Byte动态数组末尾插入一个元素时间: "<<time <<"ms"<<endl;

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step2.2统计Int动态数组末尾插入一个元素时间
//        start = std::chrono::steady_clock::now();
//        insertObjToIntVector(intVector);
//        end = std::chrono::steady_clock::now();
//        time = std::chrono::duration<double,milli>(end-start).count();
//        cout << "向int动态数组末尾插入一个元素时间: "<<time <<"ms"<<endl;

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step2.3统计long int动态数组末尾插入一个元素时间
//        start = std::chrono::steady_clock::now();
//        insertObjToLongIntVector(longIntVector);
//        end = std::chrono::steady_clock::now();
//        time = std::chrono::duration<double,milli>(end-start).count();
//        cout << "向long int动态数组末尾插入一个元素时间: "<<time <<"ms"<<endl;
//    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

//    cout<<"\n";

//    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//    //step3 统计读取list最后一个元素的时间

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step3.1统计读取byte型list中最后一个元素的时间

//        list<char> byteList;

//        fillByteList(byteList,objCnt);

//        start = std::chrono::steady_clock::now();
//        accessByteListLastestObj(byteList);
//        end = std::chrono::steady_clock::now();
//        time = std::chrono::duration<double,milli>(end-start).count();

//        cout << "访问Byte型list最后一个元素的时间为: "<<time <<"ms"<<endl;

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step3.2统计读取Int型list中最后一个元素的时间

//        list<int> intList;

//        fillIntList(intList,objCnt);

//        start = std::chrono::steady_clock::now();
//        accessIntListLastestObj(intList);
//        end = std::chrono::steady_clock::now();
//        time = std::chrono::duration<double,milli>(end-start).count();

//        cout << "访问int型list最后一个元素的时间为: "<<time <<"ms"<<endl;

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step3.3统计读取Long Int型list中最后一个元素的时间

//        list<long int> longIntList;

//        fillLongIntList(longIntList,objCnt);

//        start = std::chrono::steady_clock::now();
//        accessLongIntListLastestObj(longIntList);
//        end = std::chrono::steady_clock::now();
//        time = std::chrono::duration<double,milli>(end-start).count();

//        cout << "访问long int型list最后一个元素的时间为: "<<time <<"ms"<<endl;

//    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

//    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//    //step4统计向list中间插入一个元素的时间

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step4.1统计Byte动态数组中间插入一个元素时间

//        start = std::chrono::steady_clock::now();
//        insertObjToByteList(byteList);
//        end = std::chrono::steady_clock::now();
//        time = std::chrono::duration<double,milli>(end-start).count();
//        cout << "向Byte型list末尾插入一个元素时间: "<<time <<"ms"<<endl;

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step4.2统计Int动态数组中间插入一个元素时间
//        start = std::chrono::steady_clock::now();
//        insertObjToIntList(intList);
//        end = std::chrono::steady_clock::now();
//        time = std::chrono::duration<double,milli>(end-start).count();
//        cout << "向int型list末尾插入一个元素时间: "<<time <<"ms"<<endl;

//        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
//        //step4.3统计long int动态数组中间插入一个元素时间
//        start = std::chrono::steady_clock::now();
//        insertObjToLongIntList(longIntList);
//        end = std::chrono::steady_clock::now();
//        time = std::chrono::duration<double,milli>(end-start).count();
//        cout << "向long int型list末尾插入一个元素时间: "<<time <<"ms"<<endl;

//    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

//    return 0;
//}

