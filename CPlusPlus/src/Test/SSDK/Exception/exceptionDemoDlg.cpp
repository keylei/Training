#include <memory>
#include <QQuickStyle>

#include "QQmlComponent"
#include "QQuickItem"

#include "TypeTraits/typetraits.hpp"

#include "exceptionDemoDlg.hpp"

using namespace SSDK::Exception;
using namespace SSDK::GUI;
using namespace SSDK::TypeTraits;
using namespace SSDK;
using namespace std;

ExceptionDemoDlg:: ExceptionDemoDlg()
{
    this->setObjectName(TypeTraits::TypeTraits::typeName(this).get());
}
ExceptionDemoDlg::~ExceptionDemoDlg()
{

}

void ExceptionDemoDlg::showSDKException()
{
    try
    {
        SDK sdk;
        sdk.load();
    }
    catch(CustomException& ex)
    {
        ex.setStackTraceShown(true);
        this->showExceptionMessageBox(
                    this->m_engine.get(),
                    this->objectName(),
                    QString("rectMain"),
                    ex);
    }
}
void ExceptionDemoDlg::showJobException()
{
    try
    {
        Fov fov;
        fov.inspect();
    }
    catch(CustomException& ex)
    {
        auto responseFunc = []{   cout<<"response..."<<endl;  };
        auto ignoreFunc = []{   cout<<"ignore ..."<<endl;};
        HandlerInfo responseHandlerInfo(HandlerType::AI_Response,tr("Response..."),responseFunc);
        HandlerInfo ignoreHandlerInfo(HandlerType::Ignore,tr("Ignore..."),ignoreFunc);
        ExceptionHandlers handlers;
        handlers.emplace(responseHandlerInfo.handlerType(),responseHandlerInfo);
        handlers.emplace(ignoreHandlerInfo.handlerType(),ignoreHandlerInfo);
        ex.setDisplayMsg(tr("Fov Inspect Error!"));
        this->showExceptionMessageBox(this->m_engine.get(),this->objectName(),QString("rectMain"),ex,handlers);

        this->pCustomException()->dispose();
    }
}
void ExceptionDemoDlg::showHwException()
{
    Vision vision;//一定要放在catch外面, 否则的话在catch里面调用到dispose的时候, vision可能已经被销毁
    try
    {
        vision.snap();
    }
    catch(CustomException& ex)
    {
        ex.setDisplayMsg(tr("Snap Error!"));
        ex.setStackTraceShown(false);

        ex.setHandlerDisplayMsg(HandlerType::Ignore,tr("Ignore and go on!"));
        ex.setHandlerDisplayMsg(HandlerType::AI_Response,tr("Smart Response, then click close and retry!"));
        ex.setHandlerDisplayMsg(HandlerType::Retry,tr("Retry snap Fov!"));
        ex.setHandlerDisplayMsg(HandlerType::Abort,tr("Abort snap Fov,then click close!"));

        this->showExceptionMessageBox(this->m_engine.get(),this->objectName(),QString("rectMain"),ex);
        this->pCustomException()->dispose();
    }
}
void ExceptionDemoDlg::showStaticFunctionException()
{
    try
    {
        SDK::write();
    }
    catch(CustomException& ex)
    {
        ex.setStackTraceShown(true);
        this->showExceptionMessageBox(
                    this->m_engine.get(),
                    this->objectName(),
                    QString("rectMain"),
                    ex);
    }
}

void SDK::write()
{
    THROW_EXCEPTION_WITHOUT_OBJ("Write Error!");
}
