#include <iostream>

#include "app/config.hpp"
#include "app/mainwindow.hpp"

using namespace std;
using namespace App;
using namespace Job;

int main()
{
    try
    {
        //定义一个类对象
        Config config;
        config.readConfigFiles();

        //读取程式
        QString jobDir = "../data/";

        MainWindow mainWindow;
        mainWindow.loadJob(jobDir);            //读取目录下的检测程式
        //将检测数据显示在终端上
        mainWindow.inspectionData().board().measuredObjs().print();
        //将检测数据写入到xml文件中
        QString filePath = jobDir +"V2.xml";
        mainWindow.inspectionData().writeToXml(filePath);
    }
    catch(SSDK::CustomException &ex)
    {
        ex.addMsg("捕获到异常，继续上抛以显示到终端!");
        THROW_EXCEPTION(ex.what());
    }
    return 0;
}
