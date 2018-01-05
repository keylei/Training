#ifndef  EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <string>
#include <chrono>

#include <Person.hpp>

/**
 *  @brief comment
 *
 *  @author rime
 *  @version 1.00 2017-12-20 rime
 *                note:create it
*/
class Employee: public Person
{
public:
    //>>>-----------------------------------------------------------------------------------------------------------------
    //Enum

    enum class EmployeeType
    {
        ADMINISTRATOR,
        ENGINEER,
        MANAGER,
        SALESMAN
    };

    //<<<-----------------------------------------------------------------------------------------------------------------


    //>>>-----------------------------------------------------------------------------------------------------------------
    //constructor & destructor

    Employee();
    virtual ~Employee();
    Employee(const Employee& employee);

    //<<<-----------------------------------------------------------------------------------------------------------------

    Employee& operator =(const Employee& employee);

    //>>>-----------------------------------------------------------------------------------------------------------------
    //get & set functions

    //<<<-----------------------------------------------------------------------------------------------------------------

    //>>>-----------------------------------------------------------------------------------------------------------------
    //member functions



    //<<<-----------------------------------------------------------------------------------------------------------------

    int seniority() const { return this->m_seniority; }
    void setSeniority(int seniority) { this->m_seniority = seniority; }

    double monthlySalary() const { return this->m_monthlySalary; }
    void setMonthlySalary(double monthlySalary) { this->m_monthlySalary = monthlySalary; }

protected:

    int m_seniority;
    double m_monthlySalary;

private:

    //>>>-----------------------------------------------------------------------------------------------------------------
    //member variant


    //<<<-----------------------------------------------------------------------------------------------------------------
};
#endif // EMPLOYEE_HPP
