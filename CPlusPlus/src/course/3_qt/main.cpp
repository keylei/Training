#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext> //注意： 使用qml导出C++对象一定要加这一行
#include <QDebug>

#include "Chapter8/colormaker.hpp"
#include "Chapter8/changeqmlcolor.hpp"

int main(int argc, char *argv[])
{
    //>>>----------------------------------------------------------------------------------------------------------
    //Chapter1 - Chapter7

    //    //1.默认创建的以QGuiApplication方式
    //    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //    /*Qt中有3中类表示Application：
    //       *1.QCoreApplication: 基类
    //       *2.QGuiApplication:继承QCoreApplication，在其基础上增加了一些界面处理功能
    //       *3.QApplication:继承QGuiApplication，在其基础上增加了一些widget的处理功能
    //       */
    //    QGuiApplication app(argc, argv);

    //    //在软件中加载qml文件，因为Qt不仅仅是qml
    //      /*
    //       * 启动Qt Quick App模式
    //       * QQmlApplication 搭配Window
    //       * QQuickView 搭配View
    //       *
    //       * QQuickView显示Qml文档，对窗口的控制权在C++代码（如设置窗口标题，）
    //       * QQmlApplication 加载以window为根对象的QML文档，QML拥有对窗口的控制权
    //      */
    //    QQmlApplicationEngine engine;

    //     //必须以"qrc:"作为前缀
    //    engine.load(QUrl(QLatin1String("qrc:/Chapter7/06_Clip.qml")));
    //    if (engine.rootObjects().isEmpty())
    //        return -1;

    //>>>----------------------------------------------------------------------------------------------------------
    //Chapter 8 注册一个QML可用类型

    //    QGuiApplication app(argc, argv);

    //    //1.把C++类导出到QML环境中，使得可以创建qml实例
    //    //  第一个参数uri，指定一个包名，用于直接在QML环境中import用
    //    //  第二个参数是主版本号
    //    //  第三个参数是次版本号
    //    //  第四个参数为封装的类名。直接在QML声明的时候用
    //    //    qmlRegisterType<ColorMaker>("an.qt.ColorMaker", 1, 0, "ColorMaker");

    //    QQmlApplicationEngine engine;

    //    //2.把C++对象到处为QML属性
    //    engine.rootContext()->setContextProperty("colorMaker", new ColorMaker());

    //    engine.load(QUrl(QLatin1String("qrc:/Chapter8/02_CppObjToQml.qml")));
    //    if (engine.rootObjects().isEmpty())
    //        return -1;

    //>>>----------------------------------------------------------------------------------------------------------
    //3. 在C++中调用Qml对象

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load("qrc:/Chapter8/03_CallQml.qml");

    QObject* pRoot = nullptr;
    QList< QObject*> rootObjs = engine.rootObjects();
    int cnt = rootObjs.size();

    //1.查找根元素
    for (int i = 0; i < cnt; ++i)
    {
        if(rootObjs.at(i)->objectName() == "wndRoot")
        {
            pRoot = rootObjs.at(i);
            break;
        }
    }

    //这里不是很合理，其实就是改变颜色，封装成函数更好
    new ChangeQmlColor(pRoot);

    //2.查找Button元素
    QObject* pQuitBtn = pRoot->findChild<QObject*>("btnQuit");
    if(nullptr!=pQuitBtn)
    {
        //直接绑定了quit函数，是一个静态函数
        QObject::connect(pQuitBtn, SIGNAL(clicked()), &app, SLOT(quit()));
    }

    //3.查找Text元素
    QObject* pHelloTxt = pRoot->findChild<QObject*>("txtHelloWorld");
    if(nullptr!=pHelloTxt)
    {
       bool isSuccessful = QMetaObject::invokeMethod(pHelloTxt, "setText", Q_ARG(QString, "world hello"));
       qDebug() << "call setText return:" << isSuccessful;

       pHelloTxt->setProperty("color", QColor::fromRgb(255, 0, 0));
       isSuccessful = QMetaObject::invokeMethod(pHelloTxt, "doLayout");
       qDebug() << "call doLayout return:" << isSuccessful;
    }

    return app.exec();
}
