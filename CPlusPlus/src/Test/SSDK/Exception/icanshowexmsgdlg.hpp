#ifndef ICANSHOWEXCEPTIONMESSAGEDLG_H
#define ICANSHOWEXCEPTIONMESSAGEDLG_H

#include <memory>

#include <QObject>
#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickItem>

#include "GUI/qml.hpp"
#include "qcustomexception.hpp"
#include "Exception/customexception.hpp"

/**
 *  @brief
 *      This class is used to assist the pop-up exception Dlg.
 *          As usual, dialog which need to pop-up exception dlg have a lot of similar code,
 *      so this class is used to wrap these similar code.
 *
 *  @author rime
 *  @version 1.00 2017-03-21 rime
 *                note:create it
*/
class ICanShowExMsgDlg
{
public:

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //constructor & deconstructor

    ICanShowExMsgDlg();
    virtual ~ICanShowExMsgDlg();

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //normal function

    /**
     * @brief customException
     * @return
     *             返回当前的CustomException对象指针, 该指针并不是底层传上来的异常指针, 但是其内部成员的值和底层指针的值完全一样.
     *             通过该函数可以得到底层异常进一步的信息
     */
    SSDK::Exception::CustomException* pCustomException();

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //exception messageBox functions

    //create a "ExceptionMessageBox.qml" object and pop-up it

    /**
     * @brief createAndShowExMsgDlg
     *             新建一个不带Handler的窗体Exception窗体并弹出
     * @param engine
     * @param controlObjName
     * @param parentObjName
     * @param ex
     */
    void showExceptionMessageBox(
            QQmlApplicationEngine* engine,
            QString controlObjName,
            QString parentObjName,
            SSDK::Exception::CustomException& ex);

    /**
     * @brief createAndShowExMsgDlgWithHandlers
     *             新建一个带Handler的窗体Exception窗体并弹出
     * @param engine
     * @param controlObjName
     * @param parentObjName
     * @param ex
     * @param handlers
     */
    void showExceptionMessageBox(
            QQmlApplicationEngine* engine,
            QString controlObjName,
            QString parentObjName,
            SSDK::Exception::CustomException& ex,
            SSDK::Exception::ExceptionHandlers& handlers);

    /**
     * @brief closeExMsgDlg
     *             关闭异常窗体,
     *
     * 注意:
     *          如果窗体没有创建或者show, 不做任何操作
     */
    void closeExMsgDlg();

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

private:

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //member variant

    //是否包含了异常对象指针, 由于异常对象一开始在内存中是不存在的, 需要创建, 但是一旦创建以后就可以复用,没有必要
    //反复创建, 该成员就是用于指示是否需要创建异常对象指针
    bool m_isExMsgObjObtained{false};

    //异常对象指针
    std::shared_ptr<QCustomException>  m_exObj{nullptr};

    //异常窗体指针, 一旦创建了,就一直在内存中, 直到父窗体销毁
    std::shared_ptr<QQuickItem> m_exMsgDlg{nullptr};

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

    //>>>----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    //exception messageBox functions

    void createExMsgDlg(
            QQmlApplicationEngine* pEngine,
            QString controlObjName,
            QString exParentObjName);

    //<<<----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};

#endif // ICANSHOWEXCEPTIONMESSAGEDLG_H
