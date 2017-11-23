#include <iostream>
#include <chrono>

#include <rectangle.hpp>
#include <rectangle1.hpp>
#include <rectangle2.hpp>

using namespace std;

int main()
{
    //>>>----------------------------------------------------------------------------------------------------------
    //测试列表初始化
    int testCnt = 10000000;
    auto start = chrono::steady_clock::now();

    for (int i = 0; i < testCnt; ++i)
    {
        Rectangle rect;
    }

    auto end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end- start).count() <<endl;

    start = chrono::steady_clock::now();
    for (int i = 0; i < testCnt; ++i)
    {
        Rectangle1 rect;
    }
    end = chrono::steady_clock::now();
    cout << chrono::duration_cast<chrono::milliseconds>(end- start).count() <<endl;

    //>>>----------------------------------------------------------------------------------------------------------
    //测试dynmaic的效率

//    int testCnt = 10000000;
//    auto start = chrono::steady_clock::now();

//    for (int i = 0; i < testCnt; ++i)
//    {
////        Rectangle2* pRect = new Rectangle2();
////        Geometry* pGeo = (Geometry*)pRect;

//        Rectangle2* pRect = new Rectangle2();
//        Geometry* pGeo = dynamic_cast<Geometry*>(pRect);
//    }

//    auto end = chrono::steady_clock::now();
//    cout << chrono::duration_cast<chrono::milliseconds>(end- start).count() <<endl;

//    start = chrono::steady_clock::now();
//    for (int i = 0; i < testCnt; ++i)
//    {
//        Rectangle2* pRect = new Rectangle2();
//        Geometry* pGeo = (Geometry*)pRect;

////        Rectangle2* pRect = new Rectangle2();
////        Geometry* pGeo = dynamic_cast<Geometry*>(pRect);
//    }
//    end = chrono::steady_clock::now();
//    cout << chrono::duration_cast<chrono::milliseconds>(end- start).count() <<endl;


}
