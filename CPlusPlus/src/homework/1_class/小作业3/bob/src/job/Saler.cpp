#include "Saler.hpp"

using namespace Job;
using namespace Job;


Saler::Saler()
{

}

Saler::Saler(string employeeId,
             std::string name,
             Sex sex,
             EmployeePost employeePost,
             std::string inaugurationTime,
             int workedMonths,
             double basePay,
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
        this->m_commissionRatio = commissionRatio;
        this->m_sales = sales;
    }
    catch(...)
    {
        THROW_EXCEPTION("销售员构造函数错误!");
    }
}

Saler::~Saler()
{

}

double Saler::calcSalary()
{
    try
    {
        double salary = this->basePay() * this->workedMonths() +
                        this->m_commissionRatio * this->m_sales;
        return salary;
    }
    catch(...)
    {
        THROW_EXCEPTION("计算销售员的薪水错误");
    }
}

