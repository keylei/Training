#ifndef APPSETTING_HPP
#define APPSETTING_HPP

#include <iostream>

#include <QSettings>
#include <QFile>
#include <QMetaEnum>

#include "../SDK/customexception.hpp"
#include "../SDK/formatconversion.hpp"

namespace App
{
    //>>>------------------------------------------------------------------------------------
    //enum
    enum class MachineName// 机器名称,包括AOI和SPI两种
    {
        AOI,
        SPI
    };
    enum class Theme// 界面主题,包括黑色和白色两个主题
    {
        BLACK,
        WHITE
    };
    enum class Language// 语言种类,包括英文和中文两种语言
    {
        EN,
        CN
    };
    enum class LaneMode// 机器种类,包括模拟器、单轨机和双轨机
    {
        SIMULATOR,      // 模拟器,模拟机器运行的电脑
        SINGLE_LANE,    // 单轨机,只有一条轨道的机器
        DUAL_LANE       // 双轨机,有两条轨道的机器
    };


    /**
     *  @brief AppSetting
     *
     *          AppSetting类是检查配置文件的类,所检查的配置文件包括主题、语言等
     *      不是程序运行时所必需的配置;如果不存在则直接创建默认的配置,存在则配
     *      置是否正确,不正确则使用默认参数.
     *
     *      类的成员变量包含:
     *          1.公司名   2.机器名   3.主题    4.语言    5.机器类型
     *      类的成员函数包含:
     *          1.加载配置文件    2.读取配置文件    3.写入配置文件
     *      使用操作:
     *          将配置文件路径传入loadAppSetting()函数,读取配置文件中的配置:
     *              a.配置文件不存在则自动生成默认配置文件
     *              b.配置文件存在但参数不正确则自动改为默认配置
     *
     *  @author peter
     *  @version 1.00 2017-11-22 peter
     *                note:create it
     */
    class AppSetting
    {
    public:
        //>>>--------------------------------------------------------------------------------
        // constructor & destructor
        /**
         * @brief AppSetting
         *      默认构造函数
         * @param N/A
         * @return N/A
         */
        AppSetting();
        /**
         * @brief ~CaptureSetting
         *      析构函数
         * @param N/A
         * @return N/A
         */
        virtual ~AppSetting();

        //>>>--------------------------------------------------------------------------------
        // load function
        /**
         *  @brief loadAppSetting
         *      加载UI界面的配置文件
         *  @param path
         *      待加载的配置文件路径
         *  @return N/A
         */
        void loadAppSetting(const QString& path);

    private:
        //>>>--------------------------------------------------------------------------------
        // read & write function
        /**
         *  @brief readAppSetting
         *      配置文件存在时,读取配置文件中的信息
         *  @param path
         *      待读取的配置文件路径
         *  @return N/A
         */
        void readAppSetting( const QString& path );
        /**
         *  @brief writeAppSetting
         *      配置文件不存在时,将默认配置信息写到文件中
         *  @param path
         *      待写入的配置文件路径
         *  @return N/A
         */
        void writeAppSetting( const QString& path );

    private://rime -1 成员变量的注释偏少
        std::string m_companyName {"SciJet"};
        MachineName m_machineName {MachineName::AOI};
        Theme m_theme {Theme::WHITE};
        Language m_lang {Language::EN};
        LaneMode m_laneMode {LaneMode::DUAL_LANE};
    };

}//End of namespace App

#endif //APPSETTING_HPP













