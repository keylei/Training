#include "icanshowexmsgdlg.hpp"

using namespace std;
using namespace SSDK;
using namespace SSDK::Exception;

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//constructor & deconstructor

ICanShowExMsgDlg::ICanShowExMsgDlg()
{
}

ICanShowExMsgDlg::~ICanShowExMsgDlg()
{
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//normal functions

CustomException *ICanShowExMsgDlg::pCustomException()
{
    if(nullptr != this->m_exObj)
    {
        return &this->m_exObj.get()->customException();
    }
    else
    {
        return nullptr;
    }
}

//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//exception messagebox functions

void ICanShowExMsgDlg::createExMsgDlg(
        QQmlApplicationEngine* pEngine,
        QString controlObjName,
        QString exParentObjName)
{
    if(nullptr==m_exMsgDlg)
    {
        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //1. 获取最顶层对象的指针,通常为Application下第一个Item或者Rectange
        QObject* pRootObj;
        FIND_QML_ROOT_OBJ_PTR(controlObjName,pEngine,pRootObj);

        //>>>-------------------------------------------------------------------------------------------------------------------------------------
        //2.获取异常窗体的父窗体指针,其中父窗体指针的ObjectName由外部输入
        QObject* pParentObj;
        FIND_QML_CHILD_OBJ_PTR(exParentObjName,pRootObj,pParentObj);

        if(nullptr!=pParentObj)
        {
            //>>>-------------------------------------------------------------------------------------------------------------------------------------
            //3.创建异常窗体

            QQmlComponent component(pEngine, "qrc:/SSDK/Exception/ExceptionMessageBox.qml",pParentObj);
            QQuickItem *exMsgDlgObj = qobject_cast<QQuickItem*>(component.create());
            this->m_exMsgDlg = shared_ptr<QQuickItem>(exMsgDlgObj,[](QQuickItem* p){p->destroyed();});

            exMsgDlgObj->setParentItem(qobject_cast<QQuickItem*>(pParentObj));
            auto pQCustomException =dynamic_cast<QCustomException*>(exMsgDlgObj->findChild<QObject*>(QCustomException::m_exObjName));
            this->m_exObj = shared_ptr<QCustomException>(dynamic_cast<QCustomException*>(pQCustomException));
        }
    }
}

void ICanShowExMsgDlg::showExceptionMessageBox(
        QQmlApplicationEngine* pEngine,
        QString controlObjName,
        QString exParentObjName,
        CustomException& ex)
{
    //1.create a "ExceptionMessageBox.qml" object
    createExMsgDlg(pEngine,controlObjName,exParentObjName);

    auto pEx = this->m_exObj .get();
    auto pExMsgDlg = this->m_exMsgDlg.get();

    pEx->updateCustomException(ex);


    QMetaObject::invokeMethod(pExMsgDlg,"open");
}

void ICanShowExMsgDlg::showExceptionMessageBox(
        QQmlApplicationEngine* pEngine,
        QString controlObjName,
        QString exParentObjName,
        CustomException& ex,
        ExceptionHandlers& handlers)
{
    createExMsgDlg(pEngine,controlObjName,exParentObjName);

    auto pEx = this->m_exObj .get();
    pEx->updateCustomException(ex);
    pEx->setHandlers(handlers);

    auto pExMsgDlg = this->m_exMsgDlg.get();
    QMetaObject::invokeMethod(pExMsgDlg,"open");
}

void ICanShowExMsgDlg::closeExMsgDlg()
{
    if(nullptr!=this->m_exMsgDlg)
    {
        auto pExMsgDlg = this->m_exMsgDlg.get();
        QMetaObject::invokeMethod(pExMsgDlg,"close");
    }
}


//<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


