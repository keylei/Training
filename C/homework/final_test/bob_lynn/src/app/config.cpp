#include "config.hpp"

using namespace std;
using namespace App;
using namespace SSDK;


Config::Config()
{

}

Config::~Config()
{

}

void Config::readConfigFiles()
{
    try
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step1
        //读取路径下的存放配置文件路径的文件,如果不存在,则将存放设置文件的路径写入默认值
        QSettings configFile(this->m_appConfig,QSettings::IniFormat);

        if(!QFile::exists(this->m_appConfig))
        {
            configFile.setValue("AppSettingPath","../config/AppSetting.ini");
            configFile.setValue("CaptureSettingPath","../config/CaptureSetting.ini");
        }
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step2
        //读取文件Theme内容,将读取"appsetting.ini"和"capturesetting.ini"配置文件的路径
        QString appSettingPath = configFile.value("AppSettingPath").toString();
        QString captureSettingPath = configFile.value("CaptureSettingPath").toString();

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //step3
        //读取appsetting.ini和capturesetting.ini配置文件的路径
        this->m_appSetting.readAppSetting(appSettingPath);
        this->m_captureSetting.readCaptureSetting(captureSettingPath);
    }
    catch(SSDK::CustomException &ex)
    {
        //追加异常信息,并抛出
        ex.addMsg("加载配置文件错误!");
        THROW_EXCEPTION(ex.what());
    }
}



