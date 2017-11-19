#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>

class A
{
public:
    A(){}
    ~A(){ std::cout << "销毁A对象" << std::endl;}
};

class B
{
public:
    B(){}
    ~B(){ std::cout << "销毁B对象" << std::endl; }
};

class Cube
{
public:    
    /*
     * 即使不显式的声明默认构造函数，编译器也会自动生成一个默认构造函数,
     * 但是会出现:
     *
     * 问题1:.导致成员变量值的不确定，为了避免初始值的不确定，可以在成员变量使用{}
     * 解决办法：
     *         在C++11中，可以在成员变量声明后使用{}进行初始化，这种初始化方式早于构造函数执行，
     * 也就是说只要在构造函数中没有进行另外的初始化工作，成员变量将按照{}中设定的值进行初始化。
     * 这可以有效避免变量的确定值，属于通用的初始化方式
     *
     *
     */
//    Cube();//如果定义了参数构造函数，同时没有定义默认构造函数的话，是不能进行默认初始化的

//    当类存在单一参数的构造函数时，编译器在类的构造时会帮我们进行隐式转换，虽然这一定程度上简化了编码
     explicit  Cube(int side);

    ~Cube()
    {
        try
        {
            delete m_a;
            delete m_b;
            std::cout << m_side <<std::endl;
            std::cout << "Destructor called" <<std::endl;
        }
        catch(...)
        {
            //这里可以什么都不做，只是保证catch块的程序抛出的异常不会被扔出析构函数之外。
        }
    }

    Cube& operator = (const Cube &cube);

    //即使没有声明复制构造函数，，编译器也会默认生成一个构造函数
    Cube(const Cube& cube);

    int side() const{return m_side;}
    void setSide(int side){m_side = side;}

private:
    //1.如果有一个成员没有进行初始化，同时没有显式定义默认的构造函数的话，那么会调用
    //   编译器默认生成的默认构造函数，会多一次调用
    //2.如果全部成员都初始化的话，不会调用默认构造函数，效率会高一些
    int m_side{ 1 };
    double d{0.1*2/3};
    float f{0.01};

    A* m_a;
    B* m_b;
};

#endif // CUBE_HPP
