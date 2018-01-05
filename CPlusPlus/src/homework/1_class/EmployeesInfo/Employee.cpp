#include "Employee.hpp"

using namespace std;

//>>>-----------------------------------------------------------------------------------------------------------------
//constructor & destructor

Employee::Employee()
{

}
Employee::~Employee()
{

}

Employee::Employee(const Employee& employee)
{
    *this = employee;
}

Employee &Employee::operator =(const Employee& employee)
{
    this->m_id = chrono::high_resolution_clock::now().time_since_epoch().count();
    this->m_name = employee.m_name;
    this->m_monthlySalary = employee.m_monthlySalary;
    this->m_sex = employee.m_sex;
    this->m_seniority = employee.m_seniority;
}

//<<<-----------------------------------------------------------------------------------------------------------------
