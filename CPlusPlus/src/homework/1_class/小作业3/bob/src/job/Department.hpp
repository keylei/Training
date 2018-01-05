#ifndef DEPARTMENT_HPP
#define DEPARTMENT_HPP

#include <iostream>
#include <list>

#include "Employee.hpp"
#include "Manager.hpp"

namespace Job
{
    /**
         *  @brief Department
         *          操作公司部门的类,例如增加一个部门等
         *  @author bob
         *  @version 1.00 2017-12-22 bob
         *                note:create it
         */
    class Department
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
            *  @brief  构造函数
            *  @param  N/A
            *  @return N/A
            */
        Department();

        /**
            *  @brief  析构函数
            *  @param  N/A
            *  @return N/A
            */
        virtual ~Department();
        //<<<----------------------------------------------------------------------------------------------------------------------------

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //get & set functions

        std::string departmentName(){return this->m_name;}
        void setDepartmentName(std::string name){this->m_name = name;}

        Manager *pManager(){return this->m_pManager;}
        void setMangerPtr(Manager *pManager){this->m_pManager = pManager;}//rime 为什么不是setPManager

        std::list<Job::Employee *>& pEmployees(){return this->m_pEmployees;}

        Department& operator += ( Employee *pEmployee );

        //<<<---------------------------------------------------------------------------------------------------------------------------------------------

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //member functions

        /**
        *  @brief removeManager
        *           移除部门经理
        *  @param  N/A
        *  @return N/A
        */
        void removeManager();

        /**
        *  @brief addManager
        *           增加部门经理
        *  @param  pManager:生成经理的数据
        *  @return N/A
        */
        void addManager(Manager *pManager);
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------
    private:
        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //member variants

        std::string m_name{""};                         //部门的名称
        std::list<Job::Employee *> m_pEmployees;        //部门的员工列表
        Manager *m_pManager;                            //部门经理
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    };
}


#endif // DEPARTMENT_HPP
