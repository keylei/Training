#include "dog.hpp"

using namespace std;

//Dog::Dog()
//{
//     cout << "Derived default constructor"<<endl;
//}

////在子类中显式的调用带参数的构造函数
//Dog::Dog(int age)/*:Animal(age)*/
//{
//    Base(age);
//     cout << "Derived parameterized constructor"<<endl;
//}

void Dog::run()
{
//    sleep();//如果不是重名函数直接调用即可
//    Animal::run();//如果重名，使用这样的形式“类型名：函数名”

    cout<<"Dog running..."<<endl;
}
