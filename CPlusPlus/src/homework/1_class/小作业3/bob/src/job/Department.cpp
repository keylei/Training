#include "Department.hpp"

using namespace Job;

Department::Department()
{

}

Department::~Department()
{
    try
    {
        if(nullptr != this->m_pManager)
        {
            delete this->m_pManager;
            this->m_pManager = nullptr;
        }

        list<Job::Employee *>::iterator employeeIterator;        //部门的员工列表

        for (employeeIterator = this->m_pEmployees.begin();
             employeeIterator != this->m_pEmployees.end();++employeeIterator)
        {
            if(*employeeIterator != nullptr)
            {
                delete *employeeIterator;
                *employeeIterator = nullptr;
            }
        }
    }
    catch(...)
    {
        THROW_EXCEPTION("部门的析构函数错误");
    }
}

Department &Department::operator +=(Employee *pEmployee)
{
    try
    {
        this->m_pEmployees.push_back(pEmployee);
        return *this;
    }
    catch(...)
    {
        THROW_EXCEPTION("部门中添加员工错误");
    }
}

void Department::removeManager()
{
    try
    {
        delete this->m_pManager;
        this->m_pManager = nullptr;
    }
    catch(...)
    {
        THROW_EXCEPTION("部门删除经理错误!");
    }
}

void Department::addManager(Manager *pManager)
{
    try
    {
        this->m_pManager = new Manager();
        this->m_pManager->setBasePay(pManager->basePay());
        this->m_pManager->setBonuses(pManager->bonuses());
        this->m_pManager->setCommissionRatio(pManager->commissionRatio());
        this->m_pManager->setEmployeeId(pManager->employeeId());
        this->m_pManager->setEmployeePost(pManager->employeePost());
        this->m_pManager->setInaugurationTime(pManager->inaugurationTime());
        this->m_pManager->setName(pManager->name());
        this->m_pManager->setSales(pManager->sales());
        this->m_pManager->setSex(pManager->sex());
        this->m_pManager->setWorkedMonths(pManager->workedMonths());
    }
    catch(...)
    {
        THROW_EXCEPTION("部门删除经理错误!");
    }
}

