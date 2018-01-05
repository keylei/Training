#ifndef MYSPACE_HPP
#define MYSPACE_HPP


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
#endif // MYSPACE_HPP
