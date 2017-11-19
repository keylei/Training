#include "qcustomexception.hpp"
#include <iostream>

using namespace SSDK::Exception;
using namespace std;

const QString QCustomException::m_exObjName= QString("exception");

//对应了ExceptionMessageBox在项目中的路径
//注意:这里需要根据路径设定
const  QUrl QCustomException::m_exQmlPath = QUrl(QStringLiteral("qrc:/SSDK/Exception/ExceptionMessageBox.qml"));

QCustomException::QCustomException(QObject *parent):
    QObject(parent)
{
}

void QCustomException::handleException(const QString& handlerName)
{
    auto selectedType = getHandlerTypeOnHandlerTrString(handlerName);
    auto handlers = this->m_customException.handlers();
    handlers[selectedType].handler();
}

const QString QCustomException::handlerOptionalMsg()
{
    auto handlers = this->m_customException.handlers();
    auto iter = handlers.begin();
    QString tempMsg;

    while(iter!=handlers.end())
    {
        auto handlerType = static_cast<HandlerType>(iter->first);
        auto handlerInfo = static_cast<HandlerInfo>(iter->second);
        tempMsg =tempMsg+ "<p><b>"+tr(m_handlerTranslatorMap[handlerType].toStdString().data())
                +"&nbsp;&nbsp;:&nbsp;&nbsp;</b>"+handlerInfo.displayMsg()+"</p>";
        iter++;
    }

    return tempMsg;
}

const QList<QString> QCustomException::handlerTypeNames()
{
    QList<QString> handlerNames;

    auto handler = this->m_customException.handlers();
    auto iterator = handler.begin();
    while(iterator!=handler.end())
    {
        std::string tempStr = (m_handlerTranslatorMap[iterator->first]).toStdString();
        handlerNames.append(tr(tempStr.data()));
        iterator++;
    }

    return handlerNames;
}

bool QCustomException::canShownStackTraceMsg()
{
    return m_customException.isStackTraceMsgShown();;
}
void QCustomException::setShownStackTraceMsg(bool isShownStackTrace)
{
     m_customException.setStackTraceShown(isShownStackTrace);
}

////This function is used to set m_handlers
// ExceptionHandlers QCustomException::handlers()const
//{
//    return  this->m_customException.handlers();
//}
////This function is used to set m_handlers
//void QCustomException::setHandlers(const ExceptionHandlers& handlers)
//{
//    this->m_customException.setHandlers(handlers);
//}

//>>>--------------------------------------------------------------------------------
//color function

QCustomException::HandlerColorType QCustomException::handlerColorType(QString handlerTypeStr)
{
    auto handlerType = getHandlerTypeOnHandlerTrString(handlerTypeStr);
    switch (handlerType)
    {
    case HandlerType::AI_Response:
        return HandlerColorType::HighLighted;
    default:
        return HandlerColorType::Normal;
    }

    return HandlerColorType::Normal;
}

//get HandlerType based on tr String,their map relation is in m_handlerTranslatorMap
//UI use tr String,C++ use normal Enum or std::string
//    1.C++ to qml is HandlerType to tr String
//    2.qml back to C++ is trString to HandlerType
HandlerType QCustomException::getHandlerTypeOnHandlerTrString (const QString& trString)
{
    auto iter = this->m_handlerTranslatorMap.begin();
    while(this->m_handlerTranslatorMap.end() != iter)
    {
        if(tr(m_handlerTranslatorMap[iter->first].toStdString().data()) == trString)
            break;

        ++iter;
    }

    return iter->first;
}

//<<<--------------------------------------------------------------------------------
