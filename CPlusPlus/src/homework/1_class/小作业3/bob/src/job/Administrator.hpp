#ifndef ADMINISTRATOR_HPP
#define ADMINISTRATOR_HPP

#include "Employee.hpp"

namespace Job
{
    /**
         *  @brief Administrator
         *            操作一个经理的类,例如设置经理的奖金,提成等
         *  @author bob
         *  @version 1.00 2017-12-21 bob
         *                note:create it
         */
    class Administrator : public Job::Employee
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief  构造函数
        *  @param  N/A
        *  @return N/A
        */
        Administrator();

        /**
        *  @brief  构造函数
        *  @param  employeeId:     行政人员的编号
        *           name:          行政人员的名称
        *           sex:           行政人员的性别
        *           employeePost:  行政人员的职位
        *        inaugurationTime: 行政人员的入职时间
        *          workedMonths:   行政人员已工作时间
        *          basePay:        行政人员的基本工资
        *  @return N/A
        */
        Administrator(std::string employeeId,
                      std::string name,
                      Job::Sex sex,
                      Job::EmployeePost employeePost,
                      std::string inaugurationTime,
                      int workedMonths,
                      double basePay);

        /**
        *  @brief  析构函数
        *  @param  N/A
        *  @return N/A
        */
        virtual ~Administrator();
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //virtual functions

        /**
        *  @brief  calcSalary
        *           计算经理的工资
        *  @param  N/A
        *  @return N/A
        */
        virtual double calcSalary() override;
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    };
}


#endif // ADMINISTRATOR_HPP
