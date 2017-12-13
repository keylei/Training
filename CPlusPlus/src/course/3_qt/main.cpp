#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    //1.默认创建的以QGuiApplication方式
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    /*Qt中有3中类表示Application：
       *1.QCoreApplication: 基类
       *2.QGuiApplication:继承QCoreApplication，在其基础上增加了一些界面处理功能
       *3.QApplication:继承QGuiApplication，在其基础上增加了一些widget的处理功能
       */
    QGuiApplication app(argc, argv);

    //在软件中加载qml文件，因为Qt不仅仅是qml
      /*
       * 启动Qt Quick App模式
       * QQmlApplication 搭配Window
       * QQuickView 搭配View
       *
       * QQuickView显示Qml文档，对窗口的控制权在C++代码（如设置窗口标题，）
       * QQmlApplication 加载以window为根对象的QML文档，QML拥有对窗口的控制权
      */
    QQmlApplicationEngine engine;

     //必须以"qrc:"作为前缀
    engine.load(QUrl(QLatin1String("qrc:/Chapter5/04_Timer.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    //进入app的循环事件，直到其内部调用exit()函数退出
    return app.exec();
}
