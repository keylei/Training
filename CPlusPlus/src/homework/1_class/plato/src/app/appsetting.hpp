#ifndef APPSETTING_HPP
#define APPSETTING_HPP

#include <QSettings>
#include <QFile>

#include "../sdk/customexception.hpp"
#include "../sdk/formatconvertion.hpp"

namespace App
{
    //软件的主题为枚举类型,其值为Black,White
    enum class Theme
    {
        BLACK ,
        WHITE
    };
    //软件的语言为枚举类型,其值为CN,EN
    enum class Lang
    {
        CN,
        EN
    };
    //软件运行模式(有SIMULATOR(离线),SINGLELANE(单轨模式),DUAN_LANE(双轨模式))
    enum class LaneMode
    {
        SIMULATOR,
        SINGLE_LANE,
        DUAN_LANE
    };
    //设备的工作模式为枚举类型,其值为SPI,AOI
    enum class MachineType
    {
        SPI,
        AOI
    };

    /**
     *  @brief AppSetting
     *         软件应用程序的相关设置:
     *         如软件的语言,主题,轨道模式,检测模式,公司名称等数据
     *  @author bob
     *  @version 1.00 2017-11-21 bob
     *                note:create it
     */
    class AppSetting
    {
    public:
        //>>>----------------------------------------------------------------------------------------------------------------------------
        //constructor & deconstructor
        //初始化成员变量
        AppSetting();

        ~AppSetting();
        //>>>----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        // get & set functions
        //设置 & 获取软件的主题
        void setTheme(App::Theme theme){ this->m_theme = theme;}
        App::Theme theme(){return this->m_theme;}

        //设置 & 获取软件的语言
        void setLang(App::Lang lang){ this->m_lang = lang;}
        App::Lang lang(){return this->m_lang;}

        //设置 & 获取软件的检测模式(SPI为检测锡膏,AOI为检测贴片元件)
        void setLaneMode(App::LaneMode laneMode){ this->m_laneMode = laneMode;}
        App::LaneMode laneMode(){return this->m_laneMode;}

        //设置 & 获取当前软件
        void setMachineType(App::MachineType machineType)
        {
            this->m_machineType = machineType;
        }
        App::MachineType machineType(){return this->m_machineType;}
        //>>>----------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------
        //成员函数    读写配置文件中的数据
        /*
            *  @brief  readAppSetting
            *          读取指定目录下的文件,判断文件目录是否存在,则写入默认配置文件
            *          如果文件数据不正确,则将数据写入默认值
            *  @param  path:读取文件的路径,如(./app.ini)
            *  @return  N/A
            */
        void readAppSetting(const QString& path);

        /*
            *  @brief  writeAppSetting
            *          将根据数据格式将数据写入指定路径下的文件
            *  @param  path:写入数据文件的路径,如(./app.ini)
            *  @return  N/A
            */
        void writeAppSetting(const QString& path);
        //<<<---------------------------------------------------------------------------------------------------------------------------

    private:
        //>>>---------------------------------------------------------------------------------------------------------------------------
        //成员变量
        Theme m_theme;               //软件主题,(有BLACK & WHITE两种)
        Lang m_lang;                 //软件语言,(有CN & EN 两种)
        //软件运行的模式(有SIMULATOR(离线),SINGLELANE(单轨模式),DUAN_LANE(双轨模式))
        LaneMode m_laneMode;
        MachineType m_machineType;  //设备的工作模式(SPI(检测锡膏),AOI(检测贴片元件))
        QString m_companyName;      //公司名称,(目前有Scijet,Sung两种)
    };
} //End of namespace App

#endif // APPSETTING_HPP
