#ifndef SALES_HPP
#define SALES_HPP

#include "Employee.hpp"

namespace Job
{
    /**
     *  @brief Sales
     *          操作一个工程师类,例如设置工程师的工资等 //rime 这种注释是最可恨的
     *  @author bob
     *  @version 1.00 2017-12-21 bob
     *                note:create it
     */
    class Saler: public Job::Employee
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief  构造函数
        *  @param  N/A
        *  @return N/A
        */
        Saler();

        Saler(std::string employeeId,
              std::string name,
              Job::Sex sex,
              Job::EmployeePost employeePost,
              std::string inaugurationTime,
              int workedMonths,
              double basePay,
              double commissionRatio,
              double sales);

        /**
        *  @brief  析构函数
        *  @param  N/A
        *  @return N/A
        */
        virtual ~Saler();
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        // get & set functions

        double commissionRatio(){return this->m_commissionRatio;}
        void setCommission(double commission){this->m_commissionRatio = commission;}

        void setSales(double sales){this->m_sales = sales;}
        double sales(){ return this->m_sales;}
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        //virtual functions

        /**
        *  @brief  calcSalary
        *           计算销售的薪水
        *  @param  N/A
        *  @return N/A
        */
        virtual double calcSalary() override;
        //<<<----------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>---------------------------------------------------------------------------------------------------------------------------
        //member variants

        double m_commissionRatio{0.0};              //销售的提成比率
        double m_sales{0.0};                        //销售的销售额 //rime 对于公司的业绩, 如果都是一样的,就应该放在公司层面, 为什么要每个类中都有
        //<<<---------------------------------------------------------------------------------------------------------------------------
    };
}

#endif // SALES_HPP
