#include "Datagenerator.hpp"

using namespace std;

using namespace App;
using namespace Job;
using namespace SDK;


DataGenerator::DataGenerator()
{

}

DataGenerator::~DataGenerator()
{

}

void DataGenerator::generateCompanyData(int administratorCnt,
                                        int engineerCnt,
                                        int salerCnt,
                                        Job::Company &company)//rime 为什么这里有加Job的namespace了
{
    try
    {
        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step1
        //声明&定义局部变量

        srand((unsigned)time(NULL));                    //初始化随机数
        double salesMax = 1000000;                      //销售额的最大值(单位:元 下同)
        double salesMin = 0.0;                          //销售额的最小值
        double adminBasePayMax = 6000;                  //行政基本工作最大值    //rime 啥叫基本工作最大值? 工资是讲大小的?
        //rime Pay是支付的意思更多, 你既然项目都叫salary, 为什么这里有变成了pay了
        double adminBasePayMin = 5000;                  //行政基本工作最小值   //rime Base是不能乱用的, C#中有专门的关键字Base, 表示基类的意思
        double engineerBasePayMax = 10000;              //工程师基本工资最大值
        double engineerBasePayMin = 5000;               //工程师基本工资最小值
        double salerBasePay = 3000;                     //销售的基本工作
        double salerComissionRatio = 0.05;              //销售的提成比例
        unsigned char workedMonthsMax = 36;             //工作月份最大值
        unsigned char workedMonthsMin = 1;              //工作月份的最小值
        double engineerBonuses = 20000 / MONTHS;        //工程师的奖金(每月) //rime 奖金就不用了复数了,况且还是表示每月的
        std::string companyName = "Scijet";             //公司的名称

        string namePrefix{""};                          //员工名称的前缀
        string employeeName{""};                        //员工的名字
        string employeeId{""};                          //员工的ID号码
        Sex employeeSex;                                //员工的姓名
        std::string inaugurationTime{""};               //员工的入职时间  //rime 入职用entry/registration
        int workedMonths{0};                            //员工的工作月数
        double employeeBasePay{0.0};                    //员工的基本工资
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------

                //>>>---------------------------------------------------------------------------------------------------------------------------------------------
                //step2
                //生成公司数据(公司名称,部 company.setCompanyName(companyName);//rime 为什么已经是company了, 成员函数还要加上company. 岂不是多此一举
        double sales = RandomNumber::randomDouble(salesMin,salesMax);
        company.setCompanySales(sales);

        //rime  既然是部门, 为什么对象名是这样, 还以为是员工呢
        Department *pAdministration = new Department();
        Department *pEngineering = new Department();
        Department *pSales = new Department();

        //rime  department应该是复数啊, 这里增加部分使用成员函数更好, 因为增加部分本来就属于company的行为, 让别人直接能够
        //           .出来不是更直观, 否则的话还要点departments()才能知道, 人家说不定根本就不明白departments()是啥意思
        company.department().push_back(pAdministration);
        company.department().push_back(pEngineering);
        company.department().push_back(pSales);
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step3
        //随机生成经理,及所有员工的数据(2个行政,3个工程师,4个销售)

        Employee *pEmployee{nullptr};

        time_t currentTime = time(NULL);
        tm * pTime = localtime(&currentTime);             //获取当前系统时间的地址

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step3.1
        //随机生成各个部门经理的数据

        Manager *pAdminManager = new Manager();           //生成1个行政部经理数据
        pAdministration->setMangerPtr(pAdminManager);
        pAdministration->setDepartmentName("Administration"); //rime  不需要加Department, 和上面一样
        generateManagerData("AdminManager",
                            EmployeePost::ADMINISTRATOR,
                            sales,
                            (*pAdministration->pManager()));

        Manager *pEngineerManager = new Manager();        //生成1个工程部经理数据
        pEngineering->setMangerPtr(pEngineerManager);
        pEngineering->setDepartmentName("Engineering");
        generateManagerData("EngineerManager",
                            EmployeePost::ENGINEER,
                            sales,
                            (*pEngineering->pManager()));

        Manager *pSalerManager = new Manager();           //生成1个销售部经理数据
        pSales->setMangerPtr(pSalerManager);
        pSales->setDepartmentName("Sales");
        generateManagerData("SalerManager",
                            EmployeePost::SALER,
                            sales,
                            (*pSales->pManager()));

        pAdministration->setDepartmentName("Administration");   //设置行政部名称
        pEngineering->setDepartmentName("Engineering");         //设置工程部名称
        pSales->setDepartmentName("Sales");                     //设置销售部名称

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step3.2
        //随机2个行政,3个工程师,4个销售的数据

        // rime 这样写太累赘, 经理和其它类型的员工有太多的重复代码
        //         如果硬要一个个写, 也单独for循环比较好, 你for终止条件是3个的和, 里面再进行判断, 这样写太麻烦
        for (int i = 0; i < (administratorCnt + engineerCnt + salerCnt); ++i)
        {
            //员工的ID,根据当前系统时间生成
            employeeId = FormatConvertor::intToString(pTime->tm_year + 1990) +
                         FormatConvertor::intToString(pTime->tm_mon + 1) +
                         FormatConvertor::intToString(pTime->tm_mday) +
                         FormatConvertor::intToString(pTime->tm_hour) +
                         FormatConvertor::intToString(pTime->tm_min) +
                         FormatConvertor::intToString(pTime->tm_sec);
            //元的性别,随机生成
            employeeSex = (Sex) RandomNumber::randomByte((unsigned char)Sex::MALE,
                                                         (unsigned char)Sex::FEMALE);
            //员工的工作月数
            workedMonths = RandomNumber::randomByte(workedMonthsMin,workedMonthsMax);
            //生成员工的入职时间
            inaugurationTime = FormatConvertor::intToString(
                        pTime->tm_year + 1990 - (workedMonths / MONTHS)) +
                    FormatConvertor::intToString(
                        pTime->tm_mon + 1 - (workedMonths % MONTHS)) +
                    FormatConvertor::intToString(pTime->tm_mday) +
                    FormatConvertor::intToString(pTime->tm_hour) +
                    FormatConvertor::intToString(pTime->tm_min) +
                    FormatConvertor::intToString(pTime->tm_sec);

            if( i < administratorCnt)     //生成行政人员个数,并加入到行政部员工列表中
            {
                namePrefix = "Administrator";
                employeeName = namePrefix + FormatConvertor::intToString(i + 1);
                employeeBasePay = RandomNumber::randomDouble(adminBasePayMin,
                                                             adminBasePayMax);
                pEmployee = new Administrator(employeeId,
                                              employeeName,
                                              employeeSex,
                                              EmployeePost::ADMINISTRATOR,
                                              inaugurationTime,
                                              workedMonths,
                                              employeeBasePay);
                (*pAdministration) += pEmployee;   //将行政添加到行政部门中
            }
            else if (i < (administratorCnt + engineerCnt)) //生成工程师数据,并加入到工程部员工列表中
            {
                namePrefix = "Engineer";
                employeeName = namePrefix + FormatConvertor::intToString(
                            i + 1 - administratorCnt );
                employeeBasePay = RandomNumber::randomDouble(engineerBasePayMin,
                                                             engineerBasePayMax);

                pEmployee = new Engineer(employeeId,
                                         employeeName,
                                         employeeSex,
                                         EmployeePost::ENGINEER,
                                         inaugurationTime,
                                         workedMonths,
                                         employeeBasePay,
                                         engineerBonuses);
                (*pEngineering) += pEmployee;    //工程师添加到工程部中
            }
            else                      //生成销售员数据,并加入到销售部员工列表中
            {
                namePrefix = "Saler";
                employeeName = namePrefix + FormatConvertor::intToString(
                            i + 1 - administratorCnt - engineerCnt);
                employeeBasePay = salerBasePay;
                pEmployee = new Saler(employeeId,
                                      employeeName,
                                      employeeSex,
                                      EmployeePost::SALER,
                                      inaugurationTime,
                                      workedMonths,
                                      employeeBasePay,
                                      salerComissionRatio,
                                      sales);
                (*pSales) += pEmployee;             //将销售添加到销售部门中

            }
        }
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------
    }
    catch(...)
    {
        THROW_EXCEPTION("生成公司数据错误");
    }
}

//rime 经理和其他职位都是继承与同一个基类, 并没有特别大的不同, 不需要特意写一个函数
//        如果需要单独一个函数, 我宁愿是生成一个基类对象, 然后把员工类型传入
void DataGenerator::generateManagerData(string name,
                                        EmployeePost employeePost,
                                        double sales,
                                        Manager &manager)
{
    try
    {
        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step1
        //声明&定义局部变量

        double basePayMax = 30000;                  //经理基本工资最大值
        double basePayMin = 20000;                  //经理基本工资最小值
        double comissionRatio = 0.05;               //经理的提成比例
        unsigned char workedMonthsMax = 36;         //工作月份最大值
        unsigned char workedMonthsMin = 1;          //工作月份的最小值
        double bonuses = 100000 / MONTHS;           //经理的奖金(每月)

        string employeeId{""};
        Sex sex;
        std::string inaugurationTime{""};
        int workedMonths{0};
        double basePay{0.0};
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------

        //>>>---------------------------------------------------------------------------------------------------------------------------------------------
        //step2
        //生成经理的数据

        time_t currentTime = time(NULL);
        tm * pTime = localtime(&currentTime);       //获取当前系统时间的地址

        employeeId = FormatConvertor::intToString(pTime->tm_year + 1990) +
                     FormatConvertor::intToString(pTime->tm_mon + 1) +
                     FormatConvertor::intToString(pTime->tm_mday) +
                     FormatConvertor::intToString(pTime->tm_hour) +
                     FormatConvertor::intToString(pTime->tm_min) +
                     FormatConvertor::intToString(pTime->tm_sec);
        sex = (Sex) RandomNumber::randomByte((unsigned char)Sex::MALE,
                                             (unsigned char)Sex::FEMALE);
        workedMonths =(int)RandomNumber::randomByte(workedMonthsMin,workedMonthsMax);
        inaugurationTime = FormatConvertor::intToString(
                    pTime->tm_year + 1990 - (workedMonths / MONTHS)) +
                FormatConvertor::intToString(
                    pTime->tm_mon + 1 - (workedMonths % MONTHS)) +
                FormatConvertor::intToString(pTime->tm_mday) +
                FormatConvertor::intToString(pTime->tm_hour) +
                FormatConvertor::intToString(pTime->tm_min) +
                FormatConvertor::intToString(pTime->tm_sec);
        basePay = RandomNumber::randomDouble(basePayMin,basePayMax);

        manager.setEmployeeId(employeeId);
        manager.setName(name);
        manager.setSex(sex);
        manager.setEmployeePost(employeePost);
        manager.setInaugurationTime(inaugurationTime);
        manager.setWorkedMonths(workedMonths);
        manager.setBasePay(basePay);
        manager.setBonuses(bonuses);
        manager.setCommissionRatio(comissionRatio);
        manager.setSales(sales);
        //<<<---------------------------------------------------------------------------------------------------------------------------------------------
    }
    catch(...)
    {
        THROW_EXCEPTION("生成经理数据错误");
    }
}

