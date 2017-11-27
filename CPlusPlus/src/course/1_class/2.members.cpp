// #include <iostream>

// #include "circle.hpp"
// #include "ellipse.hpp"

// using namespace std;

// int main()
// {
//    //>>>----------------------------------------------------------------------------------------------------------
//    //1.访问权限
// //    Circle circle(2);
// //    //可以直接访问public的成员
// //    circle.calcArea();
// //    //如果要访问private的成员，可以通过访存函数
// //    cout << "Radius is:" << circle.radius() << "\n";

// //    //子类可以访问父类protected的成员
// //    Ellipse ellipse(2,3);
// //    ellipse.calcArea();

//    //>>>----------------------------------------------------------------------------------------------------------
//    // 成员函数

//    //静态函数不能向普通成员函数一样用对象加'.'操作符访问，必须使用类型加"::"访问
//    cout << Circle::getType()<<endl;

//    return 0;
// }
