#include <iostream>

#include <QString>

#include "./App/appsetting.hpp"
#include "./App/capturesetting.hpp"
#include "./App/mainWindow.hpp"

#define APP_SETTING_PATH "../AppSetting.ini"
#define CAPTURE_SETTING_PATH "../CaptureSetting.ini"
#define JOB_FOLDER_PATH "../data/"

//rime -1 如何配置路径没有交代

using namespace std;

int main()
{
    try
    {
        //rime -1 试问那个软件会把MainWindow作为启动软件
        //rime -1  start函数偏动词一点，如果
        App::MainWindow appStart;

        // 加载配置文件
        appStart.loadSetting( APP_SETTING_PATH,CAPTURE_SETTING_PATH );

        // 扫描程式文件夹下是否有程式文件
        appStart.scanJobFolder(JOB_FOLDER_PATH );//rime -1 按照单一性的原则，扫描目录就是扫描目录，不应该干加载程式的活，所以这里不合适

        // 在屏幕上打印程式信息
        appStart.inspectionData().print();
    }
    catch ( SDK::CustomException& ex)
    {
        std::cout << ex.what() << std::endl;
    }


    return 0;
}

