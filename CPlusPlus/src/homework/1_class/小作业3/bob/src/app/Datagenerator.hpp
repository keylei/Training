#ifndef DATAGENERATION_HPP
#define DATAGENERATION_HPP

#include <time.h>
#include <ctime>

#include "../sdk/RandomNumber.hpp"
#include "../sdk/FormatConvertor.hpp"
#include "../job/Company.hpp"
#include "../job/Administrator.hpp"
#include "../job/Engineer.hpp"
#include "../job/Manager.hpp"
#include "../job/Saler.hpp"

#define MONTHS 12                       //表示一年有12个月

namespace App
{
    /**
     *  @brief  DataGenerator
     *          数据生成器,例如生成一个公司信息数据
     *  @author bob
     *  @version 1.00 2017-11-30 bob
     *                note:create it
     */
    class DataGenerator
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //constructor & destructor

        /**
        *  @brief  构造函数
        *  @param  N/A
        *  @return N/A
        */
        DataGenerator();

        /**
        *  @brief  析构函数
        *  @param  N/A
        *  @return N/A
        */
        ~DataGenerator();
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //member functions

        /*
        *  @brief   generateCompanyData
        *           随机生成一个公司员工数据,具体信息如下:
        *               1.公司的名称,销售额
        *               2.生成公司的部门信息,如部门名称,部门员工
        *               3.生成每个部门员工的列表
        *  @param   administratorCnt:行政人员的数量
        *           engineerCnt:工程师的数量
        *           salerCnt:销售员的数量
        *           company:生成公司的数据,
        *  @return  N/A
        */
        static void generateCompanyData(int administratorCnt, //rime 这种生成一个特定的数据结构就不需要加Data后缀了, 如果加Data一般指的内置类型
                                        int engineerCnt,
                                        int salerCnt,
                                        Job::Company& company);
        /*
        *  @brief   generateManagerData
        *           随机生成一个公司部门经理数据,具体信息如下:
        *               经理的名称,性别,部门,ID,提成,公司总销售额,奖金等
        *  @param   name:经理的名字
        *           EmployeePost:经理的职位类型
        *           sales:公司的销售额
        *           manager:需要生成数据的经理
        *  @return  N/A
        */
        static void generateManagerData(string name,
                                        Job::EmployeePost employeePost,
                                        double sales,
                                        Job::Manager& manager);
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    };
}//End of namespace App

#endif // DATAGENERATION_HPP
