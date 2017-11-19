#include "cube.hpp"

using namespace std;

//Cube::Cube()
//{
//    m_side = 10;
//     d={0.1};
//     f={0.01};
//}

//int Cube::side() const
//{
//    return m_side;
//}

//void Cube::setSide(int side)
//{
//    m_side = side;
//}

//参数构造函数
Cube::Cube(int side)
{
    try
    {
        this->m_side = side;

        //如果在过程中发生了异常，a和b对象没有被正确的释放，所以会发生内存泄漏
        this->m_a = new A();
        this->m_b = new B();

        throw "构造函数发生异常";//在构造函数中抛出异常将不会调用析钩函数
    }
    catch(...)
    {
        //只有在catch进行正确的释放，所以不会发生内存泄漏
        delete m_a;
        delete m_b;
        throw;
    }
}

 Cube &Cube::operator =(const Cube &cube)
 {
      this->m_side = cube.side();
 }

 Cube::Cube(const Cube &cube)
 {
     this->m_side = cube.side();
 }
