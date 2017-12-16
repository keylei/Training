#include "appsetting.hpp"

using namespace App;
using namespace std;


AppSetting::AppSetting()
{
    //初始化成员变量
    this->m_companyName = "";
    this->m_laneMode = LaneMode::SINGLE_LANE ;
    this->m_lang = Lang::CN ;
    this->m_machineType = MachineType::AOI ;
    this->m_theme = Theme::BLACK ;
}

AppSetting::~AppSetting()
{

}

void AppSetting::readAppSetting(const QString& path)
{
    try
    {
        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //step1
        if(!QFile::exists(path))  //判断配置文件在目录中是否存在,如果不存在写入默认值
        {
            writeAppSetting(path);
        }
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

        //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        //step2
        else   //如果配置文件存在,则读取文件中相应的数据
        {
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //step2.1
            //读取文件Theme内容,并判断是否在枚举中,如果不在则写入默认值
            QSettings configFile(path,QSettings::IniFormat);

            QString theme = configFile.value("Theme").toString();

            //判断当前主题是否在枚举中,如果不在,则写入默认值
            if( theme.toUpper().toStdString() == VAR_TO_STR(Theme::BLACK) )
            {
                this->m_theme = Theme::BLACK;
            }
            else if (theme.toUpper().toStdString() != VAR_TO_STR(Theme::WHITE))
            {
                this->m_theme = Theme::WHITE;
            }
            else
            {
                string theme = VAR_TO_STR(Theme::BLACK);
                configFile.setValue("Theme",theme.c_str());
                this->m_theme = Theme::BLACK;
            }

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //step2.2
            //读取文件Lang内容,并判断是否在枚举中,如果不在则写入默认值
            QString lang = configFile.value("Lang").toString();

            if(lang.toUpper().toStdString() == VAR_TO_STR(Lang::CN))
            {
                this->m_lang = Lang::CN;
            }
            else if ( lang.toUpper().toStdString() == VAR_TO_STR(Lang::EN) )
            {
                this->m_lang = Lang::EN;
            }
            else
            {
                string lang =  VAR_TO_STR(Lang::CN);
                configFile.setValue("Lang",lang.c_str());
                this->m_lang = Lang::CN;
            }

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //step2.3
            //读取文件LaneMode内容,并判断是否在枚举中,如果不在则写入默认值

            QString laneMode = configFile.value("LaneMode").toString();

            if(laneMode.toUpper().toStdString() == VAR_TO_STR(LaneMode::SIMULATOR))
            {
                this->m_laneMode = LaneMode::SIMULATOR;
            }
            else if (laneMode.toUpper().toStdString() == VAR_TO_STR(LaneMode::SINGLE_LANE))
            {
                this->m_laneMode = LaneMode::SINGLE_LANE;
            }
            else if(laneMode.toUpper().toStdString() == VAR_TO_STR(LaneMode::DUAN_LANE))
            {
                this->m_laneMode = LaneMode::DUAN_LANE;
            }
            else
            {
                string laneMode = VAR_TO_STR(LaneMode::SINGLE_LANE);
                configFile.setValue("LaneMode",laneMode.c_str());
                this->m_laneMode = LaneMode::SINGLE_LANE;
            }

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //step2.4
            //读取文件MachineType内容,并判断是否在枚举中,如果不在则写入默认值
            QString machineType = configFile.value("MachineType").toString();

            if( machineType.toUpper().toStdString() == VAR_TO_STR(MachineType::AOI))
            {
                this->m_machineType = MachineType::AOI;
            }
            else if (machineType.toUpper().toStdString() == VAR_TO_STR(MachineType::SPI))
            {
                this->m_machineType = MachineType::SPI;
            }
            else
            {
                string machineType = VAR_TO_STR(MachineType::AOI);
                configFile.setValue("MachineType",machineType.c_str());
                this->m_machineType = MachineType::AOI;
            }

            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //step2.5
            //读取文件CompanyName内容,并判断是否在枚举中,如果不在则写入默认值
            this->m_companyName = configFile.value("Company").toString();
        }
        //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    }
    catch(const exception &ex)        //如果捕获异常,则输出异常信息
    {
        THROW_EXCEPTION(ex.what());
    }
}

void AppSetting::writeAppSetting(const QString &path)
{
    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //将类QSettings实例化一个对象
    //path:存放文件的路径
    //QSettings::IniFormat: 为存放文件的格式
    QSettings configFile(path,QSettings::IniFormat);

    //将配置文件的"Theme","CompanyName","MachineType","LaneMode","Lang"写入默认值
    string theme = VAR_TO_STR(Theme::BLACK);
    configFile.setValue("Theme",theme.c_str());

    string machineType = VAR_TO_STR(MachineType::AOI);
    configFile.setValue("MachineType",machineType.c_str());

    string laneMode = VAR_TO_STR(LaneMode::SINGLE_LANE);
    configFile.setValue("LaneMode",laneMode.c_str());

    string lang = VAR_TO_STR(Lang::CN);
    configFile.setValue("Lang",lang.c_str());

    configFile.setValue("Company","Scijet");
    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}
