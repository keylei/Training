//#include <iostream>
//#include <string>

//using namespace std;

//class TestClass
//{
//public:
//    TestClass()
//    {
//        throw bad_alloc();
//    }

//    static double overflowFunc(double d)
//    {
//        return d > 1e7 ? throw std::overflow_error("too big") : d;
//    }

//    static double invaildFunc(int i)
//    {
//        return i < 0 ? throw std::invalid_argument("Can not less than 0") : i;
//    }
//};

//class Father
//{

//};

//class Son: public Father
//{
//public:
//    Son()
//    {
//        throw runtime_error(" runtime error");
//    }
//};

//int main()
//{
//    try
//    {
////          TestClass tClass; //new的时候发生错误throw
////           string("abc").substr(10); // 长度错误
////           TestClass::overflowFunc(100000000000);//溢出错误
////        TestClass::invaildFunc(-1);//参数不合法错误
//        Father* son = new Son();
//    }
//    catch(const exception& ex)
//    {
//        std::cout << ex.what() << endl;
//    }

//    return 0;
//}
