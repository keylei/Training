
#include "Department.hpp"

//>>>-----------------------------------------------------------------------------------------------------------------
//constructor & destructor

Department::Department()
{

}
Department::~Department()
{
//    this->m_employeeList.clear();
}

void Department::operator +=( Employee& employee)
{
    this->m_pEmployeeList.push_back(&employee);
}

//<<<-----------------------------------------------------------------------------------------------------------------
