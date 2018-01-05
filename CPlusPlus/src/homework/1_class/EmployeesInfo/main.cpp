#include <iostream>
#include <list>

#include "Company.hpp"
#include "Engineer.hpp"

using namespace std;

int main()
{
    Engineer engineer;
    Department department ;
    department+=engineer;

    //    std::list<Employee*> m_employeeList;
    //    m_employeeList.push_back(new  Employee);

    return 0;
}
