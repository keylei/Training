#include <iostream>

#include "./app/Datagenerator.hpp"

using namespace std;

using namespace Job;
using namespace App;

//rime 输出的单元没有说清楚, 到底是一个月的薪水, 还是总共, 虽然我可以从数额上看出来, 但是还是要写清楚

//rime 这么复杂的逻辑全部写在一个main函数中, 非常乱
int main()
{
    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
    //step1
    //实例化company对象,并生成comppany

    int administratorCnt = 2;
    int engineerCnt = 3;
    int salerCnt = 4;

    Company company;
    list<Department *>::iterator departmentIterator;   //部门列表迭代器
    list<Employee *>::iterator employeeIterator;       //员工列表的迭代器

    DataGenerator::generateCompanyData(administratorCnt,
                                       engineerCnt,
                                       salerCnt,
                                       company);
    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
    //step2
    //打印出所有员工的薪水,每个部门的总薪水,所有员工的总薪水

    //rime allSolary这又是什么鬼
    double allSolary{0.0};                              //所有员工的总薪水
    int departmentCnt = company.department().size();    //公司的部门的数量
    //公司部门薪水的数组,分别为(行政部,工程部,销售部)
    double departmentSolaryArr[departmentCnt]{0};
    int departmentSolaryIdx = 0;                        //公司部门的索引号

    //rime 这一段for循环请加加注释好不好, 那么多定语看的不难受么
    for (departmentIterator = company.department().begin();
         departmentIterator != company.department().end(); ++departmentIterator)
    {
        cout<<(*departmentIterator)->pManager()->name()<<"(元):\t"
            <<(*departmentIterator)->pManager()->calcSalary()<<endl;

        allSolary += (*departmentIterator)->pManager()->calcSalary();

        departmentSolaryArr[departmentSolaryIdx] +=
                (*departmentIterator)->pManager()->calcSalary();

        for (employeeIterator = (*departmentIterator)->pEmployees().begin();
             employeeIterator != (*departmentIterator)->pEmployees().end();
             ++employeeIterator)
        {
            allSolary += (*employeeIterator)->calcSalary();

            departmentSolaryArr[departmentSolaryIdx] +=
                    (*employeeIterator)->calcSalary();

            cout<< (*employeeIterator)->name()<<"(元):\t"
                << (*employeeIterator)->calcSalary() //rime 上面已经求过一次工资了, 这里又求一次, 完全是浪费, 总共求了3次
                << endl;
        }

        if((*departmentIterator)->departmentName() == "Administration")//rime 你们不是会枚举转字符串的么, 这回怎么不用了
        {
            cout <<"行政部的总薪水为(元):"<<"\t"<<departmentSolaryArr[0]<<endl;
        }
        else if ((*departmentIterator)->departmentName() == "Engineering")
        {
            cout <<"工程部的总薪水为(元):"<<"\t"<<departmentSolaryArr[1]<<endl;
        }
        else if ((*departmentIterator)->departmentName() == "Sales")
        {
            cout <<"销售部的总薪水为(元):"<<"\t"<<departmentSolaryArr[2]<<endl;
        }
        else
        {
            THROW_EXCEPTION("统计部门薪水错误!");
        }
        cout <<"\n";
        departmentSolaryIdx++;
    }
    cout <<"所有员工的总薪水:(元)"<<"\t"<< allSolary << endl;

    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
    //step3
    //打印出所有男员工的薪水

    cout << "\n所有男员工的薪水如下(元):"<<endl;
    for (departmentIterator = company.department().begin();
         departmentIterator != company.department().end();
         ++departmentIterator)
    {
        if( (*departmentIterator)->pManager()->sex() == Sex::MALE)
        {
            cout<<(*departmentIterator)->pManager()->name() <<":\t"
                <<(*departmentIterator)->pManager()->calcSalary()<<"\n";
        }

        for (employeeIterator = (*departmentIterator)->pEmployees().begin();
             employeeIterator != (*departmentIterator)->pEmployees().end();
             ++employeeIterator)
        {
            if((*employeeIterator)->sex() == Sex::MALE)
            {
                cout<<(*employeeIterator)->name()<<":\t"
                    <<(*employeeIterator)->calcSalary()<<endl;
            }
        }
    }
    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
    //step4
    //打印出所有女员工的薪水

    cout << "\n所有女员工的薪水如下(元):"<<endl;
    for (departmentIterator = company.department().begin();
         departmentIterator != company.department().end(); ++departmentIterator)
    {
        if( (*departmentIterator)->pManager()->sex() == Sex::FEMALE)
        {
            cout<<(*departmentIterator)->pManager()->name() <<":\t"
                <<(*departmentIterator)->pManager()->calcSalary()<<"\n";
        }

        for (employeeIterator = (*departmentIterator)->pEmployees().begin();
             employeeIterator != (*departmentIterator)->pEmployees().end();
             ++employeeIterator)
        {
            if((*employeeIterator)->sex() == Sex::FEMALE)
            {
                cout<<(*employeeIterator)->name()<<":\t"
                    <<(*employeeIterator)->calcSalary()<<endl;
            }
        }
    }
    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    //>>>---------------------------------------------------------------------------------------------------------------------------------------------
    //step5
    //删除销售部经理数据,
    //重新生成一个销售部经理数据添加至销售部

    Manager *pSalerManager = new Manager();

    int workedMonth = 1;                    //已经工作的月数
    double tmpSalary{0.0};                  //取出所有员工最高的薪水

    std::string managerName = "SalerManager";
    EmployeePost employeePost = EmployeePost::SALER;
    double sales = company.companySales();
    //生成销售经理数据
    DataGenerator::generateManagerData(managerName,
                                       employeePost,
                                       sales,
                                       *pSalerManager);
    //设置销售经理工作月数为1个月
    pSalerManager->setWorkedMonths(workedMonth);

    //rime 你再前面遍历的时候就不能求出最高薪水么, 这时候再求一遍好玩啊
    //找出薪水最高的员工,并输出其薪水
    for (departmentIterator = company.department().begin();
         departmentIterator != company.department().end();
         ++departmentIterator)
    {
        //如果部门为销售部,则删除原有的销售经理数据,
        //再将新生成的销售经理添加到销售部门

        //rime 不符合要求, 你的深复制体现在哪里?
        if ((*departmentIterator)->departmentName() == "Sales")
        {
            (*departmentIterator)->removeManager();
            (*departmentIterator)->addManager(pSalerManager);
        }

        if(tmpSalary < (*departmentIterator)->pManager()->calcSalary())
        {
            tmpSalary = (*departmentIterator)->pManager()->calcSalary();
        }

        for (employeeIterator = (*departmentIterator)->pEmployees().begin();
             employeeIterator != (*departmentIterator)->pEmployees().end();
             ++employeeIterator)
        {
            if(tmpSalary < (*employeeIterator)->calcSalary())
            {
                tmpSalary = (*employeeIterator)->calcSalary();
            }
        }
    }
    cout << "\n""员工薪水最高为:"<<"\t"<<tmpSalary<<endl;
    //<<<---------------------------------------------------------------------------------------------------------------------------------------------

    if(nullptr != pSalerManager)
    {
        delete pSalerManager;
        pSalerManager = nullptr;
    }

    return 0;
}
