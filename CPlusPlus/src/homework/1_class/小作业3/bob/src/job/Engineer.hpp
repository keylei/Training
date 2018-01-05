#ifndef ENGINEER_HPP
#define ENGINEER_HPP

#include "Employee.hpp"

namespace Job
{
    /**
     *  @brief Engineer
     *          操作一个工程师类,例如设置工程师的奖金等
     *  @author bob
     *  @version 1.00 2017-12-21 bob
     *                note:create it
     */
    class Engineer : public Job::Employee
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief  构造函数
        *  @param  N/A
        *  @return N/A
        */
        Engineer();

        /**
        *  @brief  构造函数
        *  @param  employeeId:     工程师的编号
        *           name:          工程师的名称
        *           sex:           工程师的性别
        *           employeePost:  工程师的职位
        *        inaugurationTime: 工程师的入职时间
        *          workedMonths:   工程师已工作时间
        *          basePay:        工程师的基本工资
        *          bonuses:        工程师的奖金
        *  @return N/A
        */
        Engineer(std::string employeeId,
                  std::string name,
                  Job::Sex sex,
                  Job::EmployeePost employeePost,
                  std::string inaugurationTime,
                  int workedMonths,
                  double basePay,
                  double bonuses);

        /**
        *  @brief  析构函数
        *  @param  N/A
        *  @return N/A
        */
        virtual ~Engineer();
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        // get & set functions

        void setBonuses(double bonuses){this->m_bonuses = bonuses;}
        double bonuses(){ return this->m_bonuses;}
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //virtual functions

        /**
        *  @brief  calcSalary
        *           计算工程师的薪水
        *  @param  N/A
        *  @return N/A
        */
        virtual double calcSalary() override;
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>---------------------------------------------------------------------------------------------------------------------------
        //member variants

        double m_bonuses{0.0};                  //工程师的奖金
        //<<<---------------------------------------------------------------------------------------------------------------------------
    };
}

#endif // ENGINEER_HPP
