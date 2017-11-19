#ifndef QCUSTOMEXCEPTION_H
#define QCUSTOMEXCEPTION_H

#include <memory>
#include <vector>

#include <QObject>
#include <QUrl>

#include "Exception/customexception.hpp"
#include "Exception/handlerinfo.hpp"

/**
 *  @brief
 *      This class is used to wrap CustomException which in SSDK, it can be loaded to qml enviroment
 *
 *  @author rime
 *  @version 1.00 2017-04-04 rime
 *                note:create it
*/
class QCustomException: public QObject
{
    Q_OBJECT
    Q_ENUMS(HandlerColorType)

public:

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //enum & using

    using ExceptionHandlers = SSDK::Exception::ExceptionHandlers;

    //it determines handler button color
    enum HandlerColorType
    {
        HighLighted,
        Close,
        Normal
    };

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //member variant

    static const QString m_exObjName;//represent id name in qml as "exception"
    static const QUrl m_exQmlPath;// QUrl("qrc:/ExceptionMessageBox.qml");

    /**
     * Because translation must be in app project, so use a map to translate HandlerType

       Note:Remember update this map when HandlerType changed !!!*/
    std::map<SSDK::Exception::HandlerType,QString> m_handlerTranslatorMap
    {
        {SSDK::Exception::HandlerType::AI_Response,QT_TR_NOOP("AI_Response")},
        {SSDK::Exception::HandlerType::Retry,QT_TR_NOOP("Retry")},
        {SSDK::Exception::HandlerType::Ignore,QT_TR_NOOP("Ignore")},
        {SSDK::Exception::HandlerType::Abort,QT_TR_NOOP("Abort")}
        //        {Sung::SDK::Exception::HandlerType::Close,QT_TR_NOOP("Close")}
    };

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //construct & deconstructor

    QCustomException(QObject *parent = 0);
    ~QCustomException(){}

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //get & set & update functions

    Q_INVOKABLE const QString exObjName()const{return m_exObjName;}

    Q_INVOKABLE bool canShownStackTraceMsg();
    Q_INVOKABLE void setShownStackTraceMsg(bool isShownStackTrace);

    //This function is used to set m_handlers
    ExceptionHandlers handlers()const {return  this->m_customException.handlers();}
    //This function is used to set m_handlers
    void setHandlers(const ExceptionHandlers& handlers){this->m_customException.setHandlers(handlers);}

    /**
     * @brief pCustomException
     * @return
     *             返回当前的CustomException对象指针,.
     *
     */
    SSDK::Exception::CustomException& customException()
    {
        return m_customException;
    }

    /**
     * This function is used to update CustomException's pointer
       Once receive a new exception,this function must be called to update pointer
     */
    void updateCustomException(SSDK::Exception::CustomException& customException)
    {
        this->m_customException = customException;
    }

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //exception message functions

    /**
     * This function is used to get exceptionMsg,
     *  1.if STACKTRACE_MSG ,exceptionMsg is m_stackTraceMsg
     *  2.if m_isStackTraceShown is false,exceptionMsg is m_orgMsg
    */
    Q_INVOKABLE const  QString exceptionMsg() const
    {
        return QString::fromStdString(m_customException.getExceptionMsg());
    }

    Q_INVOKABLE const  QString displayMsg() const
    {
        return this->m_customException.displayMsg();
    }


    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //handler functions

    /**
      *设置Handler的颜色属性, 颜色类别由HandlerColorType决定. 根据不同的Handler设置不同的颜色
      */
    Q_INVOKABLE HandlerColorType handlerColorType(QString handlerTypeStr);


    /**
     *根据Handler的Name调用对应的Handler处理异常, 此函数是在qml中被调用
     */
    Q_INVOKABLE void handleException(const QString& handlerName);

    /**
     *得到Handler的处理信息, 此信息是格式化显示在界面上的Handler信息
     */
    Q_INVOKABLE  const QString handlerOptionalMsg() ;

    /**
     * 得到Handlers的Name, 是QString类型, 只要考虑到更好的支持翻译
    */
    Q_INVOKABLE const QList<QString> handlerTypeNames();

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private:

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //memory variant

    QList<QString> m_handlerTypeNames{nullptr};

    /**
     * This variant holds CustomException's pointer from lower level,
     *   1.Once receive a new exception,this pointer must update
     *   2.Because m_pCustomException is from CustomException's reference, it need not to delete
     */
    SSDK::Exception::CustomException m_customException;

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //handler functions

    /**
     * get HandlerType based on tr String,their map relation is in m_handlerTranslatorMap
     * UI use tr String,C++ use normal Enum or std::string
     *    1.C++ to qml is HandlerType to tr String
     *    2.qml back to C++ is trString to HandlerType
     */
    SSDK::Exception::HandlerType getHandlerTypeOnHandlerTrString(const QString& trString);

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};


#endif // QCUSTOMEXCEPTION_H
