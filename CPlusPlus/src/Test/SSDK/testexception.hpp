#ifndef TESTEXCEPTION_H
#define TESTEXCEPTION_H

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "unittester.hpp"
#include "Exception/customexception.hpp"
#include "Exception/exceptionDemoDlg.hpp"

namespace UnitTester
{
    namespace SSDK
    {
        class TestException:public QObject
        {
            Q_OBJECT


        private slots:

            /**
             * @brief initTestCase
             *             初始化测试, 这里初始化一个异常界面
             *
             * 注意:
             *         1.这里可以支持随意点击, 只有点击了右上角的关闭才会退出该函数
             *         2.在实际使用中,qml文件在项目中的位置的相对关系会发生变化, engine.load后面的路径按照实际情况进行修改
             *         3.和2一样, 实际使用中,还有一处路径需要修改, 在qcustomexception.cpp中的m_exObjName也需要对应修改
             */
            void initTestCase()
            {
                int argc = 0;
                char** argv = nullptr;
                auto app =  std::shared_ptr<QGuiApplication>(new QGuiApplication(argc,argv));

                QQuickStyle::setStyle("Material");

                //QCustomException需要作为类型在QML环境中创建实例
                qmlRegisterType<QCustomException>("qCustomException", 1, 0, "QCustomException");

                QQmlApplicationEngine engine;//对于需要显示异常的界面, 需要调用setContextProperty把C++对象传入QML中
                engine.rootContext()->setContextProperty("exceptionDemoDlg",&m_exceptionDemoDlg);

                engine.load(QUrl(QStringLiteral("qrc:/SSDK/Exception/ExceptionDemoDlg.qml")));
                m_exceptionDemoDlg.setEngine(&engine);
                app->exec();
            }

            void cleanupTestCase()
            {

            }

        private:
             std::shared_ptr<QGuiApplication> app;
            ExceptionDemoDlg m_exceptionDemoDlg;

        };//End ofTestException

        //rime170523 这是带UI的界面, 正常情况下不需要测试
        DECLARE_TEST(TestException);
    }//End of namespace SSDK
}//End of namespace UnitTester

#endif // TESTEXCEPTION_H
