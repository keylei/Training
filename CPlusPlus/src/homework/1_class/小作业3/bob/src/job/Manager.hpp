#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "Employee.hpp"

namespace Job
{
    /**
     *  @brief Manager
     *          操作一个经理的类,例如设置经理的奖金,提成等
     *  @author bob
     *  @version 1.00 2017-12-21 bob
     *                note:create it
     */
    class Manager:public Job::Employee
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief  构造函数
        *  @param  N/A
        *  @return N/A
        */
        Manager();

        /**
        *  @brief  构造函数
        *  @param  N/A
        *  @return N/A
        */
        Manager(std::string employeeId,
                std::string name,
                Job::Sex sex,
                Job::EmployeePost employeePost,
                std::string inaugurationTime,
                int workedMonths,
                double basePay,
                double bonuses,
                double commissionRatio,
                double sales);

        virtual ~Manager();
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        // get & set functions

        double bonuses(){return this->m_bonuses;}
        void setBonuses(double bonuses){this->m_bonuses = bonuses;}

        double commissionRatio(){return this->m_commissionRatio;}
        void setCommissionRatio(double commissionRatio)
        {
            this->m_commissionRatio = commissionRatio;
        }

        double sales(){return this->m_sales;}
        void setSales(double sales){this->m_sales = sales;}
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        //virtual functions

        /**
        *  @brief  calcSalary
        *           计算经理的薪水
        *  @param  N/A
        *  @return N/A
        */
        virtual double calcSalary() override;
        //<<<----------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //member variants

        double m_bonuses{0.0};                  //经理的奖金
        double m_commissionRatio{0.0};          //经理销售的提成比率
        double m_sales{0.0};                    //公司的总销售额 //rime 销售额用saleroom更好点
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------
    };
}


#endif // MANAGER_HPP
