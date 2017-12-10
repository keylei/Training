#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

#include <QDir>
#include <QFileInfo>
#include <QSettings>
#include <QString>

#include "appsetting.hpp"
#include "capturesetting.hpp"

#include "../SDK/randomdigit.hpp"
#include "../Job/inspectiondata.hpp"

namespace App
{
    /**
     *  @brief MainWindow
     *
     *          MainWindow类可以加载配置文件和扫描指定程式文件夹内程式文件;没有
     *      程式文件时,将自动调用类中的私有成员函数,生成默认的程式文件,并写入随
     *      机生成的数据.
     *
     *      类的成员变量包含:
     *          1.数据类型为AppSetting的成员(非软件运行必需的配置文件类)
     *          2.数据类型为CaptureSetting的成员(软件运行必需的配置文件类)
     *          3.数据类型为InspectionData的成员(检测程式文件数据的类)
     *      类的成员函数功能包含:
     *          1.加载配置文件
     *          2.扫描程式文件
     *      使用操作:
     *          1.传入配置文件路径给loadSetting()函数,检测配置是否正确.
     *          2.将存放程式文件夹路径传入scanJobFolder()函数,
     *              a.没有程式文件则自动生成默认文件,并写入随机生成的数据
     *              b.有则将程式文件打印在终端,用户选择程式文件并输出为xml文件
     *
     *  @author peter
     *  @version 1.00 2017-11-22 peter
     *                note:create it
     */
    class MainWindow
    {
    public:
        //>>>--------------------------------------------------------------------------------
        // constructor & destructor function
        /**
         * @brief MainWindow
         *      默认构造函数
         * @param N/A
         * @return N/A
         */
        MainWindow();
        /**
         * @brief ~MainWindow
         *      析构函数
         * @param N/A
         * @return N/A
         */
        virtual~MainWindow();

        //>>>--------------------------------------------------------------------------------
        // get function
        Job::InspectionData inspectionData(){return this->m_inspectionData;}

        //>>>--------------------------------------------------------------------------------
        // load & scan function
        /**
         * @brief loadSetting
         *      加载配置文件:
         *          1.appSetting的配置文件
         *          2.captureSetting的配置文件
         * @param appSettingPath
         *      appSetting配置文件的路径
         * @param captureSettingPath
         *      captureSetting配置文件的路径
         * @return N/A
         */
        void loadSetting( const QString& appSettingPath,
                          const QString& captureSettingPath );
        /**
         * @brief scanJobFolder
         *      扫描程式文件目录下是否有程式文件
         *          1.没有程式文件则自动创建,写入默认值
         *          2.有程式文件则加载程式文件,读取数据信息
         * @param path
         *      待扫描的存放程式文件的文件夹路径
         * @return N/A
         */
        void scanJobFolder(const QString& path);//rime -1 既然loadSetting写文件名，为什么这里不写明了呢


    private:
        //>>>--------------------------------------------------------------------------------
        // generate data
        /**
         * @brief generateObjsRandomly
         *      生成随机数据,当前数据包括:
         *          1.默认的版本号.最后的编辑时间
         *          2.默认的job程式名.原点位置.尺寸大小
         *          3.随机的原件信息(原件名.中心点位置.长宽尺寸)
         * @param chipCnt
         *          需要生成数据的chip原件数量
         * @param icCnt
         *          需要生成数据的ic原件数量
         * @return N/A
         */
        void generateObjsRandomly(int chipCnt,int icCnt);


    private:  //rime -1 成员变量没有任何注释
        App::AppSetting m_appSetting;
        App::CaptureSetting m_captureSetting;
        Job::InspectionData m_inspectionData;
    };
}//End of namespace App


#endif // APPLICATION_HPP
