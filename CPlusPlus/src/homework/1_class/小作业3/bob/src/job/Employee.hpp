#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP

#include <iostream>

#include "../sdk/Customexception.hpp"

namespace Job
{
    /**
     * @brief The Sex enum
     *          公司员工的性别
     */
    enum Sex
    {
        MALE = 0,           //性别男
        FEMALE              //性别女
    };


    //rime 为什么enum又忘了写class了,为什么不在Employee内部定义这种枚举
    /**
     * @brief The EmployeePost enum
     *          公司员工的职位
     */
    enum EmployeePost //rime 职位是必要要包含经理的, 要不然请问你为什么要把Manager继承Employee
    {
        SALER = 0,          //销售
        ENGINEER,           //工程师
        ADMINISTRATOR,      //行政
    };

    /**
     *  @brief Employee
     *          操作设置所有雇员的信息,例如设置雇员的名字,性别等
     *  @author bob
     *  @version 1.00 2017-12-21 bob
     *                note:create it
     */
    class Employee
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief  构造函数
        *  @param  N/A
        *  @return N/A
        */
        Employee();

        /**
        *  @brief  构造函数
        *  @param  employeeId:     员工的编号
        *           name:          员工的名称
        *           sex:           员工的性别
        *           employeePost:  员工的职位
        *        inaugurationTime: 员工的入职时间
        *          workedMonths:   员工已工作时间
        *          basePay:        员工的基本工资
        *  @return N/A
        */
        Employee(std::string employeeId,
                 std::string name,
                 Sex sex,
                 EmployeePost employeePost,
                 std::string inaugurationTime,
                 int workedMonths,
                 double basePay);

        /**
        *  @brief  析构函数
        *  @param  N/A
        *  @return N/A
        */
        virtual ~Employee();
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        // get & set functions

        void setEmployeeId(std::string employeeId){this->m_employeeId = employeeId;}
        std::string employeeId(){return this->m_employeeId;}

        void setName(std::string name){ this->m_name = name;}
        std::string name(){return this->m_name;}

        void setSex(Sex sex){this->m_sex = sex;}
        Sex sex(){return this->m_sex;}

        void setEmployeePost(EmployeePost employeePost){this->m_employeePost = employeePost;}
        EmployeePost employeePost(){return this->m_employeePost;}

        void setInaugurationTime(std::string time){this->m_inaugurationTime = time;}
        std::string inaugurationTime(){return this->m_inaugurationTime;}

        void setWorkedMonths(int months){this->m_workedMonths = months;}
        int workedMonths(){return this->m_workedMonths;}

        void setBasePay(double basePay){this->m_basePay = basePay;}
        double basePay(){return this->m_basePay;}
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //virtual functions

        virtual double calcSalary() = 0;
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //member variants

        std::string m_employeeId;                //雇员的ID号
        std::string m_name{""};                  //雇员的名称
        Sex m_sex;                               //雇员的性别  //rime 要初始化可以都初始化的
        EmployeePost m_employeePost;             //雇员的职位
        std::string m_inaugurationTime{""};      //雇员的入职时间
        int m_workedMonths{0};                   //员工已经工作的月数
        double m_basePay{0.0};                   //员工的基本工资
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------
    };
}   //End of namespace SDK

#endif // EMPLOYEE_HPP
