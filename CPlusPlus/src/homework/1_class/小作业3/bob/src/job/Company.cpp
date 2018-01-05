#include "Company.hpp"

using namespace Job;
using namespace Job;

Company::Company()
{

}

Company::Company(std::string companyName,
                 double companySales)
{
    try
    {
        this->m_companyName = companyName;
        this->m_sales = companySales;
    }
    catch(...)
    {
        THROW_EXCEPTION("生成公司的构造函数错误");
    }
}

Company::~Company()
{
    try
    {
        list<Job::Department *>::iterator departmentIterator;        //部门的员工列表

        for (departmentIterator = this->m_pDepartments.begin();
             departmentIterator != this->m_pDepartments.end();++departmentIterator)
        {
            if( *departmentIterator != nullptr)
            {
                delete *departmentIterator;
                *departmentIterator = nullptr;
            }
        }
    }
    catch(...)
    {
        THROW_EXCEPTION("公司的析构函数错误");
    }
}

