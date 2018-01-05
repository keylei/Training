//#include <iostream>

//#define N 100
//#define M 200 + N

//const int b = 100; //使用const代替define

//using namespace std;

//enum Size
//{
//    Width = 1
//};

//int main()
//{
//    //>>>----------------------------------------------------------------------------------------------------------
//    // 1)使用const/enum代替#define定义常量

//    //    用#define定义常量时，常量不会加入到符号列表中，如果代码中使用了这个常量，
//    //     也许会遇到一些很不容易察觉的错误，往往很难找到问题的所在

//    //宏定义的一些出错
//    //     N = N -10;

//    //    原本想要的应该是100 * （200+ N ），而实际上，编译器却给你变成了 100 * 200 + N
//    //    cout << M * N <<endl;

//    //    float a{N}; //失去了类型检查, 不安全, 也不能进行调式监控
//    //    cout << a <<endl;


//    //相比与const, enum不可以取地址, 更加安全
//    //    int* c = const_cast<int*>(&b);
//    ////    *c = 1;
//    ////    cout << b <<endl;
//    //    delete c;
//    //    cout << b <<endl;

//    //    cout << Size::Width <<endl;
//    //    int* c = const_cast<int*>(&(Size::Width));

//    return 0;
//}
