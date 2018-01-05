#ifndef  DEPARTMENT_HPP
#define DEPARTMENT_HPP

#include <list>
#include <vector>
#include <string>

#include <Employee.hpp>
#include <Company.hpp>

class T
{

};

/**
 *  @brief comment
 *
 *  @author author
 *  @version 1.00 2017-12-20 author
 *                note:create it
*/
class Department
{
public:
    //>>>-----------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    Department();
    virtual ~Department();

    //<<<-----------------------------------------------------------------------------------------------------------------

    void operator +=( Employee& employee);


    //>>>-----------------------------------------------------------------------------------------------------------------
    //get & set functions

    //<<<-----------------------------------------------------------------------------------------------------------------

private:

    //>>>-----------------------------------------------------------------------------------------------------------------
    //member variant
    std::string m_name;
    std::vector<Employee*> m_pEmployeeList;
    Employee::EmployeeType m_employeeType;

    //<<<-----------------------------------------------------------------------------------------------------------------
};
#endif // DEPARTMENT_HPP
