#include <iostream>
#include <chrono>

#include <Human.hpp>
//#include <MySpace.hpp>

using namespace std;
using namespace Mammal;

int val = 100;
namespace first
{
int val = 500;
}//End of namespace first

namespace ns1
{
int value() { return 5; }
}//End of namespace ns1

namespace ns2
{
const double x = 100;
double value( ){ return 2*x; }
}//End of namespace ns2

namespace first
{
int val2 = 300;
}//End of namespace first

namespace MySpace
{
class A //类的声明
{
    static int i;
public:
    void f();
};

class B; // 类的前向声明
void func();//全局函数声明
}

int MySpace::A::i =9 ;//直接初始化namespace中的类成员

class MySpace:: B
{
    B();
};

MySpace::B::B()
{

}

namespace X
{
    int x;
    class Check
    {
        int i;
    };

    void f(){ std::cout << "X" << std::endl; }
}


namespace Y
{
    using namespace X;
    Check obg;
    int y;

      void f(){ std::cout << "Y" <<std::endl; }
}

int main()
{
    //>>>----------------------------------------------------------------------------------------------------------
    //1. namespace基础部分

    //出现的问题1
    //        在每一个作用域，一个名字仅仅能够用来表示一个实体，同一个范围内
    //        不能有2个相同名字的变量，像下面的代码将会编译出错：
    //        int value = 0;
    //        double value = 0.0;

    //出现的问题2
    //        在c语言中，没有类的封装，可能会出现大量的全局函数和全局变量，这样既不符合规范
    //    也容易出现命名冲突

    //为什么解决上面的问题：
    //        1.可以创建类，那么需要定义类的类型和创建类的对象
    //        2.可以修改命名，value前面增加更多的定语，如inspectionValue/settingValue;
    //           如果再增加更多功能相近的功能，如inspectionLowThreshold等，需要相关的变量或者
    //           函数都需要添加这样的定语，对代码的规范性和程序员的细心成都要求很高

    //    在C++/C#/Java中可以使用namespace来避免上面的命名冲突， 提供了另外一种选择
    //    全局变量，局部变量和namespace中的变量可以重名，当然不建议这么做
    //    int val = 200;
    //    cout << first::val << '\n';

    //      不同namespace的访问
    //        cout << ns1::value() << '\n';
    //        cout << ns2::value() << '\n';
    //        cout << ns2::x << '\n';

    //>>>----------------------------------------------------------------------------------------------------------
    //2. 创建namespace

    //   相同名称namespace可以被分成不同的block
    //    cout << first::val <<"\n";
    //    cout << first::val2 <<"\n";

    // 不具名的namespace
    Human human; //构造函数中会有调用

    //>>>----------------------------------------------------------------------------------------------------------
    //3. 使用namespace

    //3.1 直接使用
    //    因为需要在类外实现, 见main函数外面对MySpace的声明

    //3.2 使用using直接引用
    //  注意类外实现还有, 主要是namespace X/namespace Y部分
//    using namespace Y;
//    Check obj2;

    //3.3

    //>>>----------------------------------------------------------------------------------------------------------
    // 使用using声明namespace成员

//    using Y::f;
//    f();
//    X::f();



    //>>>----------------------------------------------------------------------------------------------------------
    //3. namespace 和类

    //    namespace中可以定义类，类可以在namespace中实现，也可以在namespace外部实现，
    //    但是一般是在源文件中实现，同时在源文件一开始using这个namespace
    //    举例: 如Persion类


}
