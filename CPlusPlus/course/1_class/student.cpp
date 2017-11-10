#include "student.hpp"

Student::Student()
{

}

void Student::print() const
{
    //    /*×  编译不通过，const后置修饰的成员函数不能修改成
    //     员变量*/
    //    m_name = "Hello";

    //    /*×  编译不通过，const后置修饰的成员函数不能调用非
    //       const的成员函数*/
    //    std::string detailString = getDetailString();
}

std::string Student::getName()
{
    return nullptr;
}
