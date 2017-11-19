//#include <iostream>

//#include <QSettings>
//#include <QFile>

//#include "customexception.hpp"

//using namespace std;

//void writeAppSetting(const QString& path)
//{
//    QSettings configFile(path, QSettings::IniFormat);

//    configFile.setValue("Theme", "Black");
//    configFile.setValue("Lang", "CN");
//}
//void readAppSetting(const QString& path)
//{
//    try
//    {
//        if(!QFile::exists(path))
//        {
//            //假如路径不存在的话, 那么重新创建一个配置文件, 参数使用默认值就可以了
//            cout << "没有该文件, 写入默认值"<<endl;
//            writeAppSetting(path);

//            cout << "重新读取"<<endl;
//            readAppSetting(path);
//            return;
//        }
//        else
//        {
//            //文件路径存在, 没有问题
//            QSettings configFile(path, QSettings::IniFormat);

//            //读取Theme, 如果不正确的话就写入默认值
//            QString theme =  configFile.value("Theme").toString();
//            if(theme != "Black" && theme != "White")
//            {
//                cout << "读取Theme失败"<<endl;
//                configFile.setValue("Theme", "Black");
//            }
//            else
//            {
//                cout << "读取Theme成功:"<<theme.toStdString()<<endl;
//            }

//            //读取Lang,如果不正确的话就写入默认值
//            QString lang =  configFile.value("Lang").toString();
//            if(lang != "CN" && lang != "EN")
//            {
//                cout << "读取Lang失败"<<endl;
//                configFile.setValue("Lang", "CN");
//            }
//            else
//            {
//                cout << "读取Lang成功:"<<lang.toStdString()<<endl;
//            }
//        }
//    }
//    catch(const CustomException& ex)
//    {
//        THROW_EXCEPTION("Unknown Error!");
//    }
//}

//void writeCalibration(const QString& path)
//{
//    QSettings configFile(path, QSettings::IniFormat);

//    configFile.setValue("Image/Width", "4096");
//    configFile.setValue("Image/Height", "3072");
//}
//void readCalibration(const QString& path)
//{
//    try
//    {
//        if(!QFile::exists(path))
//        {
//            //假如路径不存在的话, 直接中止启动，退出软件
//            THROW_EXCEPTION("没有标定文件，直接退出!");
//        }
//        else
//        {
//            //文件路径存在, 没有问题
//            QSettings configFile(path, QSettings::IniFormat);

//            //读取图像的宽度
//            int width =  configFile.value("Image/Width").toInt();
//            if(width <= 0)
//            {
//                THROW_EXCEPTION("读取Image/Width失败!");
//            }
//            else
//            {
//                cout << "读取Image/Width成功:"<<width<<endl;
//            }

//            //读取图像的高度
//            int height =  configFile.value("Image/Height").toInt();
//            if(height <=0)
//            {
//                THROW_EXCEPTION("读取Image/Height失败!");
//            }
//            else
//            {
//                cout << "读取Image/Height成功:"<<height<<endl;
//            }
//        }
//    }
//    catch(const CustomException& ex)
//    {
//        cout << ex.what()<<endl;
//        cout << "检测功能不可用， 请重新标定！"<<endl;
//    }
//}

//int main()
//{
//    //>>>----------------------------------------------------------------------------------------------------------
//    //1. 对于非重要的配置文件(不需要给予提示)
//    //    writeAppSetting("app.ini");
//    //    readAppSetting("app.ini");

//    //>>>----------------------------------------------------------------------------------------------------------
//    //2. 对于重要的配置文件(给予提示，直接退出)
//    writeCalibration("calibration.ini");
//    readCalibration("calibration.ini");

//    return 0;
//}
