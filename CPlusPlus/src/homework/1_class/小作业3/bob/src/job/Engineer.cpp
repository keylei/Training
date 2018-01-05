#include "Engineer.hpp"

using namespace Job;
using namespace Job;

Engineer::Engineer()
{

}

Engineer::Engineer(string employeeId,
                   std::string name,
                   Sex sex,
                   EmployeePost employeePost,
                   std::string inaugurationTime,
                   int workedMonths,
                   double basePay,
                   double bonuses):Employee(employeeId,
                                             name,
                                             sex,
                                             employeePost,
                                             inaugurationTime,
                                             workedMonths,
                                             basePay)//rime 自己想想, 我Engineer如果把EmployeePost参数不是Engineer会怎么样
{
    try
    {
        this->m_bonuses = bonuses;
    }
    catch(...)
    {
        THROW_EXCEPTION("工程师的构造函数错误");
    }
}

Engineer::~Engineer()
{

}

double Engineer::calcSalary()
{
    try
    {
        int months = 12;
        return ((this->basePay()+(this->m_bonuses / months))* this->workedMonths());
    }
    catch(...)
    {
        THROW_EXCEPTION("计算工程师的薪水错误");
    }
}
