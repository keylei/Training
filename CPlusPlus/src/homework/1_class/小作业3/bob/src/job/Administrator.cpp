#include "Administrator.hpp"

using namespace Job;
using namespace SDK;

Administrator::Administrator()
{

}

Administrator::Administrator(string employeeId,
                             std::string name,
                             Sex sex,
                             EmployeePost employeePost,
                             std::string inaugurationTime,
                             int workedMonths,
                             double basePay):Employee(employeeId,
                                                      name,
                                                      sex,
                                                      employeePost,
                                                      inaugurationTime,
                                                      workedMonths,
                                                      basePay)
{

}

Administrator::~Administrator()
{

}

double Administrator::calcSalary()
{
    try
    {
        return this->basePay() * this->workedMonths();
    }
    catch(...)
    {
        THROW_EXCEPTION("计算行政的薪水错误");
    }
}
