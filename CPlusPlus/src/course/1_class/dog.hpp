#ifndef DOG_HPP
#define DOG_HPP

#include <iostream>

#include "animal.hpp"

class Dog: public Animal
{
public:

    /*
     * 通过继承构造函数实现基类构造函数的直接调用
     * 关于基类各构造函数的继承一句话搞定
     */
    using Animal::Animal;

    Dog();
    virtual  ~Dog();
//    Dog(int age);

    virtual void run();

    int tail() const{    return m_tail;}
    void setTail(int tail){m_tail = tail;}

private:
    int m_tail{1};
};

#endif // DOG_HPP
