#ifndef MAINUI_H
#define MAINUI_H

#include <iostream>
#include <memory>

#include <QObject>
#include <QMessageBox>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>

#include "qcustomexception.hpp"
#include "icanshowexmsgdlg.hpp"
#include "TypeTraits/typetraits.hpp"
#include  "Exception/handlerinfo.hpp"

/**
 * @brief The SDK class
 *             用来模拟最底层的类
 */
class SDK
{
public:
    void load()
    {
        try
        {
            THROW_EXCEPTION_WITH_OBJ("Load Error!");
        }
        CATCH_AND_RETHROW_EXCEPTION_WITH_OBJ("SSDK Exception occur!");
    }

    //测试静态函数,因为静态函数获取不到this指针
     static void  write();
};


/**
 * @brief The Fov class
 *              用来模拟中间层的数据结构, 这种类可以在上层实现
 */
class Fov
{
public:
    void inspect()
    {
        THROW_EXCEPTION_WITH_OBJ("Get Fov Data Failed!");
    }
};

/**
 * @brief The Vision class
 *              用来模拟硬件, 这种类Handler需要在类内实现, 同时继承了IDispose接口, 外部可以调用dispose函数
 */
class Vision: public SSDK::Exception::IDisposal
{
public:
    void snap()
    {
        using namespace SSDK::Exception;

        auto responseFunc = []{   std::cout<<"response..."<<std::endl;};
        auto ignoreFunc = []{   std::cout<<"ignore ..."<<std::endl;   };
        auto retryFunc = []{   std::cout<<"retry ..."<<std::endl;   };
        auto abortFunc = []{  std:: cout<<"abort ..."<<std::endl;   };

        SSDK::Exception::HandlerInfo responseHandlerInfo(HandlerType::AI_Response, std::string("Response..."),responseFunc);
        SSDK::Exception::HandlerInfo ignoreHandlerInfo(HandlerType::Ignore,  std::string("Ignore..."),ignoreFunc);
        SSDK::Exception::HandlerInfo retryHandlerInfo(HandlerType::Retry,  std::string("Retry..."),retryFunc);
        SSDK::Exception::HandlerInfo abortHandlerInfo(HandlerType::Abort,  std::string("Abort..."),abortFunc);

        SSDK::Exception::ExceptionHandlers handlers;
        handlers.emplace( responseHandlerInfo.handlerType(),responseHandlerInfo);
        handlers.emplace( ignoreHandlerInfo.handlerType(),ignoreHandlerInfo);
        handlers.emplace( retryHandlerInfo.handlerType(),retryHandlerInfo);
        handlers.emplace( abortHandlerInfo.handlerType(),abortHandlerInfo);

        THROW_EXCEPTION_WITH_HANDLERS_WITH_OBJ("snap error!",handlers);
    }

    virtual void dispose()override
    {
        std::cout<<"vision dispose..."<<std::endl;
    }
};

class ExceptionDemoDlg:public QObject,public ICanShowExMsgDlg
{
    Q_OBJECT

public:
    ExceptionDemoDlg();
    virtual ~ExceptionDemoDlg();

    Q_INVOKABLE void showSDKException();
    Q_INVOKABLE void showJobException();
    Q_INVOKABLE void showHwException();
    Q_INVOKABLE void showStaticFunctionException();

    void setEngine(QQmlApplicationEngine* pEngine)
    {
        if(nullptr!= pEngine && pEngine != this->m_engine.get())
            this->m_engine = std::shared_ptr<QQmlApplicationEngine>(pEngine);
    }
    QQmlApplicationEngine* pEngine()
    {
        return m_engine.get();
    }

signals:

    //This signal is emitted DECLARE_TESTfor one exception is catched
    void exceptionCatched(const QObject& exception);

private:    

    /**
      * 由于m_objectName和m_engine都是和Qml深入绑定, 之所有没有放在基类ICanShowExMsgDlg中
      * 是因为即使不需要show异常窗体的界面仍然有可能会使用到这两个成员变量
      */

    /**
     * @brief m_objectName
     *             该窗体的ObjectName, 在Qml和C++数据交互的时候会用到
     */
    const static QString m_objectName;

    /**
     * @brief m_engine
     *              最上层界面的QQmlApplicationEngine,该参数由主Application赋值
     */
    std::shared_ptr<QQmlApplicationEngine> m_engine;
};

#endif // MAINUI_H
