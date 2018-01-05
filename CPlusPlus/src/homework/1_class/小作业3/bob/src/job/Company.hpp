#ifndef COMPANY_HPP
#define COMPANY_HPP

#include <list>

#include "Department.hpp"

namespace Job
{
    /**
     *  @brief Company
     *          表示一个公司的类,可操作设置公司的基本属性,
     *          例如,设置公司的名称等
     *  @author bob
     *  @version 1.00 2017-12-23 bob
     *                note:create it
     */
    class Company
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief 构造函数
        *  @param  N/A
        *  @return N/A
        */
        Company();

        /**
        *  @brief 构造函数
        *  @param  N/A
        *  @return N/A
        */
        Company(std::string companyName,
                double companySales);

        /**
        *  @brief 析构函数
        *  @param  N/A
        *  @return N/A
        */
        virtual ~Company();
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        // get & set functions

        std::string companyName(){ return this->m_companyName;}
        void setCompanyName(std::string name){this->m_companyName = name;}

        double companySales(){return this->m_sales;}
        void setCompanySales(double sales){this->m_sales = sales;}

        std::list<Department *>& department(){return this->m_pDepartments;}
        //<<<----------------------------------------------------------------------------------------------------------------------------

    private:
        std::string m_companyName{""};          //表示一个公司的名称
        std::list<Department *> m_pDepartments; //表示一个公司的部门列表
        double m_sales{0.0};                    //公司的销售额
    };
}   //End of namespace Group


#endif // COMPANY_HPP
