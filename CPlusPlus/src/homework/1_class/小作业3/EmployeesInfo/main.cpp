#include <iostream>

#include "Company.hpp"

using namespace std;

int main()
{
    Employee p;
    Employee p1;
    Employee* p2 = new Employee();
    p2 = &p1;

    return 0;
}
