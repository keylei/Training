#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <string>


class Circle
{
public:
    Circle();

    Circle(double radius);

    virtual void calcArea();//public 可以被外部访问

    /*静态函数不能访问对象普通的成员变量和成员函数，只能访问静态成员
    静态无法调用到this指针*/
    static std::string getType(){ ID = 0; return std::string("Circle");  }

    //如果要访问成员变量，可以通过public的访存函数
    //因为访存函数比较简单，可以直接在头文件中实现，就变成内联函数了
    double radius() const{  return this->m_radius; }

    void setRadius(double radius) {  m_radius = radius;}

protected://protected 子类和类内部可以访问
    double m_area;

private://private 只有class内部可以访问

    //一般来说，成员变量都是默认设置成private/protected，如果没有加上那个
    //访问权限的，编译器默认认为是private的
    double m_radius{0.0};

    static int ID;
};

#endif // CIRCLE_HPP
