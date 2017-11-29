//#include <iostream>
//#include <chrono>

//#include <vector>

//using namespace std;

//struct BigTestStruct
//{
//  int iValue = 1;
//  float fValue;
//  long lValue;
//  double dValue;
//  char cNameArr[10];
//  int iValArr[100];
//};

//int testCnt=20000000;

//void fillVector(vector<BigTestStruct>& testVector)
//{
//  for (int i = 0; i < testCnt; i++)
//  {
//    BigTestStruct bt;
//    testVector.push_back(bt);
//  }
//}

//int main()
//{
//    //>>>----------------------------------------------------------------------------------------------------------
//    //1.初始化代码

////    vector <int> g1;
////    vector <int> g2;
////    vector <int> g3;

////    g1.assign(5, 10);   // 5 elements with value 10 each

////    vector <int> :: iterator it;
////    it = g1.begin() + 1;

////    g2.assign(it, g1.end() - 1); // the 3 middle values of g1

////    int gquiz[] = {1, 2};
////    g3.assign(gquiz, gquiz + 2);   // assigning from array

////    cout << "Size of g1: " << int(g1.size()) << '\n';
////    cout << "Size of g2: " << int(g2.size()) << '\n';
////    cout << "Size of g3: " << int(g3.size()) << '\n';

//    //>>>----------------------------------------------------------------------------------------------------------
//    //2.基础

////    vector<int> v{12, 7, 9, 21, 13};

////    cout << v.capacity() << endl;//目前vector占据的内存大小
////    cout << v.size() << endl;//目前元素的数量
////    cout << v.max_size() << endl;//返回vector所能存放的最大元素个数
////    cout << v.empty() << endl;//返回vector是否为空

////    /*注意：[]是不带异常保护的，而at是带异常保护的*/
////    cout << "v[2] = " << v[2] << endl; // 返回vector第二个元素
////    cout << "at : v.at(4) = " << v.at(4) << endl;// 返回vector第五个元素
////    cout << "front() : v.front() = " << v.front()<< endl;//返回vector第一个元素
////    cout << "back() : v.back() = " << v.back()<< endl;//返回vector最后一个元素

////    v.pop_back();//尾部移除元素

////    cout<< v.capacity() << endl;
////    cout<< v.size()<< endl;


////    v.push_back(15);//尾部加入元素

////    cout<< v.capacity() <<endl;
////    cout<< v.size()<<endl;

////    //取出头指针，说明vector在内存中是连续的
////    int* p = &v[0];
////    cout<< p <<endl;
////    cout<< p[1] <<endl;
////    cout<< p[2] <<endl;
////    cout<< p[3] <<endl;
////    cout<< p[4] <<endl;

////    //如果发生了扩容，头指针就发生了变化
////    v.push_back(20);//尾部加入元素
////    int* q = &v[0];
////    cout<< q <<endl;

//    //>>>----------------------------------------------------------------------------------------------------------
//    //3. 插入
////    vector <int> v(3, 10);
////    vector <int> :: iterator it;

////    it = v.begin();
////    it = v.insert(it, 20);//在第一个位置插入20

//////    for (it = v.begin(); it < v.end(); it++)
//////        cout << *it << endl;

////    v.insert(it, 2, 30);//在第一个位置插入2个30
//////        for (it = v.begin(); it < v.end(); it++)
//////            cout << *it << endl;
////    it = v.begin();

////    vector <int> v1(2, 40);
////    v.insert(it + 2, v1.begin(), v1.end());//在第三个位置 2个40
//////    for (it = v.begin(); it < v.end(); it++)
//////        cout << *it << endl;

////    int gq [] = {50, 60, 70};
////    v.insert(v.begin(), gq, gq + 3);//在第一个位置插入50,60,70

////    cout << "v contains : ";
////    for (it = v.begin(); it < v.end(); it++)
////        cout << *it << '\t';


//    //>>>----------------------------------------------------------------------------------------------------------
//    //4. 移除
////    vector <int> gquiz;

////    for (int i = 1; i <= 10; i++)
////        gquiz.push_back(i * 2);

////    // erase the 5th element
////    gquiz.erase(gquiz.begin() + 4);//移除第5个元素 10

////    // erase the first 5 elements:
////    gquiz.erase(gquiz.begin(), gquiz.begin() + 5);//移除前5个元素 ,2,4,6,8,12

////    cout << "gquiz contains :";
////    for (int i = 0; i < gquiz.size(); ++i)
////        cout << gquiz[i] << '\t';

//    //>>>----------------------------------------------------------------------------------------------------------
//    //5. swap 和clear

////    vector <int> v1{10,20};
////    vector <int> v2{30,40};
////    vector <int> :: iterator i;

////    cout << "Before Swapping"<<endl;

////    for (i = v1.begin(); i != v1.end(); ++i)
////        cout << *i << endl;

////    cout << &v1[0]<<endl;
////    cout << &v2[0]<<endl;

////    for (i = v2.begin(); i != v2.end(); ++i)
////        cout << *i << endl;

////    //直接交换两个vector的元素,注意，这个效率是很高的，因为直接指针互换
////    swap(v1, v2);
////    cout << &v1[0]<<endl;
////    cout << &v2[0]<<endl;

////    cout << "After Swapping"<<endl;
////    for (i = v1.begin(); i != v1.end(); ++i)
////        cout << *i << endl;

////    cout << ""<<endl;
////    for (i = v2.begin(); i != v2.end(); ++i)
////        cout << *i << endl;

////    //头指针不变，大小不变
////    v1.clear();
////    cout << &v1[0]<<endl;
////    cout << v1.capacity()<<endl;
////    v1.push_back(1000);
////    cout << v1.front();

//    //>>>----------------------------------------------------------------------------------------------------------
//    //效率测试

//    //1. 提前分配足够的空间以避免不必要的重新分配和复制周期
//    //预分配内存
//    //1.66s
//    //    vector<BigTestStruct> vect1;
//    //    fillVector(vect1);

//    //0.53s
////    vector<BigTestStruct> vect2;
////    vect2.reserve(testCnt);
////    fillVector(vect2);


//    //2 使用 shrink_to_fit() 释放 vector 占用的内存， – clear() 或 erase() 不会释放内存。

//    //    vect2.erase(vect2.begin(),  vect2.end());
//    //    cout << vect2.capacity()<<endl;

//    //    vect2.clear();
//    //    cout << vect2.capacity()<<endl;
//// vect2.clear();
////    vect2.shrink_to_fit();
////    cout << vect2.capacity()<<endl;

//    //3.在填充或者拷贝到 vector 的时候，应该使用赋值而不是 insert() 或push_back().
////    vector<BigTestStruct> vect2;
////    vect2.reserve(testCnt);
////    fillVector(vect2);

//        //消耗时间为1.16s
////    vector<BigTestStruct> vect3;
////    vect3.insert(vect3.end(),vect2.begin(),vect2.end());

////    vector<BigTestStruct> vect3;
////    vect3=vect2;

//    //4. 遍历 std::vector 元素的时候，避免使用 std::vector::at() 函数
////    vector<BigTestStruct> vect2;
////    vect2.reserve(testCnt);
////    fillVector(vect2);

////    //1.79s
////    int sum = 0;
//////    for (auto it = vect2.begin(); it != vect2.end(); ++it)
//////    {
//////     sum = sum + it->iValue;
//////    }

////    //1.68s
//////    for (unsigned i = 0; i < vect2.size(); ++i)
//////    {
//////      sum = sum + vect2.at(i).iValue;
//////    }

////    //1.28s
////    for (unsigned i = 0; i < vect2.size(); ++i)
////    {
////        sum = sum + vect2[i].iValue;
////    }

////    //5.尽量避免在 vector 前部插入元素
////    vector<BigTestStruct> vect2;
////    vect2.reserve(testCnt);
////    fillVector(vect2);

//////    //4.39s
//////    for (unsigned i = 1; i < 4; ++i)
//////    {
//////        BigTestStruct bt;
//////        vect2.insert(vect2.begin(),bt);
//////    }

////    //2.44s
////    for (unsigned i = 1; i < 4; ++i)
////    {
////        BigTestStruct bt;
////        vect2.insert(vect2.end(),bt);
////    }

//    //在向 vector 插入元素的时候使用 emplace_back() 而不是 push_back()
////    vector<BigTestStruct> vect1;
////    vect1.reserve(testCnt);
////    fillVector(vect1);

////    int cnt = 40000000;
////    vector<BigTestStruct> vect2;
////    vect2.reserve(testCnt);
////    auto start = chrono::steady_clock::now();
////    for (int i = 0; i < cnt; ++i)
////    {
////        vect2.push_back(BigTestStruct());//6908
//////        vect2.emplace_back(BigTestStruct());//6746
////    }
////    auto end = chrono::steady_clock::now();
////    cout << chrono::duration <double, milli> (end-start).count() <<endl;

//    return 0;
//}
