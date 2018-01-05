#include <iostream>
#include <chrono>
#include <algorithm>
//#include <string>

#include <memory>
#include <vector>

using namespace std;

class person
{
    double d=1;
public:
    void func()
    {
        d=d*2;
    }
};

int main()
{
    //>>>----------------------------------------------------------------------------------------------------------
    //删除指针的容器时避免资源泄漏

//    vector<int*> vec;
//    int cnt = 10 ;
//    for (int i = 0; i < cnt; ++i)
//    {
//        vec.push_back(new int);
//    }

    //    auto iter = vec.begin();
    //    while(iter != vec.end())
    //    {
    //        delete *iter;
    //        iter++;
    //    }

    //    vector<shared_ptr<int>> vec;
    //    int cnt = 10 ;
    //    for (int i = 0; i < cnt; ++i)
    //    {
    //        vec.push_back(shared_ptr<int>(new int));
    //    }

    //>>>----------------------------------------------------------------------------------------------------------
    //算法循环

//    int * a = (int* )malloc(4);
//    *a = 2;
//    a[1]=3;
//    a[2]=4;

    int cnt = 50000000;
    vector<person> vec;
    for (int i = 0; i < cnt; ++i)
    {
        vec.push_back(person());
    }

    auto start = chrono::steady_clock::now();

    //1167
//    auto iter = vec.begin();
//    while(iter != vec.end())
//    {
//        iter->func();
//        iter++;
//    }

//    //813
    for_each(vec.begin(), vec.end(), mem_fun_ref(&person::func));

//    auto end = chrono::steady_clock::now();
//    cout << chrono::duration <double, milli> (end-start).count() <<endl;


    return 0;
}
