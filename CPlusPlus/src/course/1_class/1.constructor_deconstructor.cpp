#include <iostream>
#include <chrono>

#include "cube.hpp"

using namespace std;


Cube cube1(20);
//Cube func1()
//{
//    //    Cube cube(20);
//    printf("%p\n", &cube1);
//    return cube1;
//}

Cube func2(Cube cube)
{
    printf("%p\n", &cube);
    cout << cube.side() <<endl;
    return cube;
}

Cube func3()
{
    Cube cube(30);
    return cube;
}

int main()
{
    //>>>----------------------------------------------------------------------------------------------------------
    //1.默认构造函数

    //调用默认构造函数
    //这里需要注意的是，使用Cube cube或者Cube cube{}都会调用默认的构造函数
    //    Cube cube;
    //    cout << cube.side() <<endl;

    //在没有自定默认构造函数的情况下，成员如果有没有初始化的时候，编译器会自动调用
    //默认构造函数，多一次调用，会花费更多的时间
    //    auto start = chrono::steady_clock::now();
    //    int cnt = 50000000;
    //    for (int i = 0; i < cnt; ++i)
    //    {
    //        Cube cube;
    //    }
    //    auto end = chrono::steady_clock::now();
    //    cout << chrono::duration <double, milli> (end-start).count() <<endl;

    //>>>----------------------------------------------------------------------------------------------------------
    //2.参数构造函数
    //如果定义了参数构造函数，同时没有定义默认构造函数的话，是不能进行默认初始化的
    //下面的代码是无法编译通过的
    //    Cube cube1;
    //如果不加explict的情况下，下面2行代码是可以编译通过的
    //    Cube cube2 = 2;
    //    cout << cube2.side() <<endl;
    //     Cube cube3='2';
    //     cout << cube3.side() <<endl;

    //>>>----------------------------------------------------------------------------------------------------------
    //3.复制构造函数

    //    Cube cube(2);
    //    Cube cube1(cube);
    //    printf("%p\n", &cube);
    //    printf("%p\n", &cube1);

    //浅复制
    //    Cube cube(2);
    //    Cube cube1(cube);
    //    printf("%p\n", &a);
    //    printf("%p\n", &cube1.side());
    //    printf("%p\n", cube.a());
    //    printf("%p\n", cube1.a());

    //复制构造函数调用的场合

    //1.按值返回对象
    //    auto cube=func1();
    //    printf("%p\n", &cube);
    //    cout << cube.side() <<endl;

    //2.按值传参数
    //    auto cube=Cube(30);
    //    printf("%p\n", &cube);
    //    func2(cube);


    //    //    //3.复制构造函数和赋值运算符重载的区别
    //    Cube cube1(2);
    //    Cube cube2(3);
    //    Cube cube3 = cube1; //调用复制构造函数
    //    cube2 = cube1;//调用赋值运算符重载函数

    //>>>----------------------------------------------------------------------------------------------------------
    //4.构造函数中的异常
    //    try
    //    {
    //        Cube cube(2);
    //    }
    //    catch(const char* pErrStr)
    //    {
    //        cout <<pErrStr <<endl;
    //    }



    //>>>----------------------------------------------------------------------------------------------------------
    //5. 析钩函数

    //函数结束时调用析钩函数
//    func3();
//    {
//        Cube cube(10);
//    }//退出Block调用析钩函数
//    Cube* pCube2 = new Cube (2);
//    //使用delete关键字调用析构函数
//    delete pCube2;

    //     //程序结束调用cube1的析钩函数

    //>>>----------------------------------------------------------------------------------------------------------
    //6. 析钩函数中异常处理



    return 0;
}
