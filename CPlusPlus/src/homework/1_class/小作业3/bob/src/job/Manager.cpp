#include "Manager.hpp"

using namespace Job;
using namespace Job;

Manager::Manager()
{

}

Manager::Manager(std::string employeeId,
                 std::string name,
                 Sex sex,
                 EmployeePost employeePost,
                 std::string inaugurationTime,
                 int workedMonths,
                 double basePay,
                 double bonuses,
                 double commissionRatio,
                 double sales):Employee(employeeId,
                                        name,
                                        sex,
                                        employeePost,
                                        inaugurationTime,
                                        workedMonths,
                                        basePay)
{
    try
    {
        this->m_bonuses = bonuses;
        this->m_commissionRatio = commissionRatio;
        this->m_sales = sales;
    }
    catch(...)
    {
        THROW_EXCEPTION("经理的构造函数错误");
    }
}

Manager::~Manager()
{

}

double Manager::calcSalary()
{
    try
    {
        //rime 为什么不是常量, 你这里哪里看的出来是一年的意思
        int months = 12;                      //一年有12个月

        double salary = (this->basePay() +  this->m_bonuses / months ) *
                this->workedMonths() + this->commissionRatio() * this->m_sales;
        return salary;
    }
    catch(...)
    {
        THROW_EXCEPTION("计算经理的薪水错误");
    }
}
