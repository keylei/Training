#include "Employee.hpp"

using namespace std;

using namespace Job;

Employee::Employee()
{

}

Employee::Employee(string employeeId,
                   std::string name,
                   Sex sex,
                   EmployeePost employeePost,
                   std::string inaugurationTime,
                   int workedMonths,
                   double basePay)
{
    try
    {
        this->m_employeeId = employeeId;
        this->m_name = name;
        this->m_sex = sex;
        this->m_employeePost = employeePost;
        this->m_inaugurationTime = inaugurationTime;
        this->m_workedMonths = workedMonths;
        this->m_basePay = basePay;
    }
    catch(...)
    {
        THROW_EXCEPTION("员工的构造函数错误");
    }

}

Employee::~Employee()
{

}

