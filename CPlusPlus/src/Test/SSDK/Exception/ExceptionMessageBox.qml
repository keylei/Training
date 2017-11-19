import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Window 2.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import qCustomException 1.0
import QtQuick.Controls 1.4

Item
{
    //>>>--------------------------------------------------------------------------------
    //Related to property

    id:exceptionMsgDlg;
    width:handlerBtnWidth*3+75;//以放置3个按钮，并保证一定的边距
    height: 600;

    property var dynamicHandlersBtns: new Array();
    property int handlerBtnWidth:120;

    //<<<--------------------------------------------------------------------------------

    //>>>--------------------------------------------------------------------------------
    //Related to UI

    Popup {
        id:exceptionPopup;
        focus:true;
        modal: true;
        closePolicy: Popup.NoAutoClose;
        visible: false;
        implicitWidth:exceptionMsgDlg.width;
        implicitHeight: exceptionMsgDlg.height;

        GridLayout{
            id:gridMain;
            rows:3;
            width:parent.width;
            height: parent.height;
            anchors.top: parent.top;
            anchors.bottom: parent.bottom;

            GridLayout{
                id:gridTxts
                Layout.row:0;
                rows:4;
                height:parent.height*2/3;
                anchors.top: parent.top;

                Label {
                    id:txtMessage;
                    Layout.row: 0;
                    Layout.margins: 20;
                    anchors.top: parent.top;
                    anchors.topMargin: 20;
                    color:"#F50057";
                    text:qsTr("Message")+"\n"
                    font.pixelSize: 20;
                    font.family: "Roboto";
                    //                        font.bold: true;
                    horizontalAlignment: Label.AlignLeft;
                    verticalAlignment: Label.AlignVCenter;
                    wrapMode:Text.WrapAnywhere;
                }

                Flickable {
                    id: flickExMsg;
                    Layout.margins: 10;
                    width:exceptionPopup.width-4*Layout.margins;
                    height: 150;
                    anchors.top:txtMessage.bottom;
                    anchors.left: txtMessage.left;
                    contentHeight: txtExptionMsg.paintedHeight;
                    clip: true;

                    ScrollBar.vertical: ScrollBar {
                        id: vbar;
                        visible: true;
                        active: txtExptionMsg.paintedHeight>flickExMsg.height;
                    }


                    Label {
                        id: txtExptionMsg;
                        focus: false;
                        wrapMode: Text.WrapAnywhere;
                        width:flickExMsg.width;
                        clip:true;
                    }
                }

                Label {
                    id:txtHandler;
                    Layout.row: 2;
                    Layout.margins: 20;
                    anchors.top:flickExMsg.bottom;

                    color:"#3F51B5";
                    text:qsTr("Handlers")+"\n";
                    font.pixelSize: 20;
                    //                        font.bold: true;
                    horizontalAlignment: Label.AlignLeft;
                    verticalAlignment: Label.AlignVCenter;
                    wrapMode:Text.WrapAnywhere;
                }

                Flickable {
                    id: flickHandlerNames;
                    width:exceptionPopup.width-4* Layout.margins;
                    height: 150;
                    Layout.margins: 10;
                    anchors.top:txtHandler.bottom;
                    anchors.left: txtHandler.left;
                    contentHeight: txtHandleInfo.paintedHeight;
                    clip: true;

                    ScrollBar.vertical: ScrollBar {
                        visible: true;
                        active: txtHandleInfo.paintedHeight>flickHandlerNames.height;
                    }


                    Label {
                        id: txtHandleInfo;
                        width:flickHandlerNames.width;
                        focus: false;
                        wrapMode: Text.WordWrap
                    }
                }
            }

            GridLayout{
                id:gridBtns;
                rows:2;
                columns:3;
                Layout.row: 1;
                Layout.margins: 20;
                //                    anchors.bottom: parent.bottom;
                anchors.bottomMargin: Layout.margins;

                Material.accent:exceptionMsgDlg.Material.accent;
            }
            //            }
        }//End of rectMain
    }

    QCustomException{
        id:exception;
        objectName:exception.exObjName();
    }

    //<<<--------------------------------------------------------------------------------

    //>>>--------------------------------------------------------------------------------
    //Related to function

    function open(){
        //1.Set x,y, make exception msg dlg in parent center
        exceptionMsgDlg.x = -10+(parent.width-exceptionMsgDlg.width)/2;
        exceptionMsgDlg.y = -10+(parent.height-exceptionMsgDlg.height)/2;

        //2.Show Expection Message and Handler Message
        var titleMsg = exception.displayMsg();
        var canShownStackTrace = exception.canShownStackTraceMsg();
        var isDarkStype = (exceptionMsgDlg.Material.theme === Material.Dark);
        if(isDarkStype){
            txtExptionMsg.color = Qt.rgba(1,1,1,1);
            txtHandleInfo.color = Qt.rgba(1,1,1,1);
        }
        else{
            txtExptionMsg.color = Qt.rgba(0,0,0,1);
            txtHandleInfo.color = Qt.rgba(0,0,0,1);
        }

        txtExptionMsg.text = "";
        if(canShownStackTrace){
            if("" === titleMsg)
                txtExptionMsg.text =exception.exceptionMsg();
            else//Use rich text
                txtExptionMsg.text ='<p><i><font size="5">'+titleMsg+"</font></i></p>"+
                        "<p></p>"+
                        exception.exceptionMsg();
        }
        else{
            if("" != titleMsg){
                txtExptionMsg.text ='<p><i><font size="5">'+titleMsg+"</font></i></p>"+
                        "<p></p>";
            }
        }

        txtHandleInfo.text = "";
        txtHandleInfo.text = exception.handlerOptionalMsg();

        //3.Create Button
        var btnNamesList = exception.handlerTypeNames();
        var handlersCnt = btnNamesList.length;

        if(handlersCnt === 0){
            txtHandler.visible = false;
        }
        else{
            txtHandler.visible = true;
        }

        for(var i = 0;i < handlersCnt;++i){
            var btnName = String(btnNamesList[i]);
            var colorType =  exception.handlerColorType(btnName);
            var isHighlighted = false;

            switch(colorType){
            case QCustomException.HighLighted:
                isHighlighted = true;
                break;
            default:
                isHighlighted = false;
                break;
            }

            var qmlCreateString=
                    'import QtQuick.Controls 2.0;'+
                    'import QtQuick.Controls.Material 2.0;'+
                    'Button{'+
                    'id:btn'+btnName+';'+
                    'text:'+'"'+btnName+'"'+';'+
                    'implicitHeight: 50;'+
                    'implicitWidth:'+ handlerBtnWidth +';'+
                    'highlighted:'+isHighlighted +';'+
                    'property int handleTypeIndex:0;'+
                    'onClicked: {'+
                    '   exception.handleException(text)'+
                    '}'+
                    '}';

            var btn = Qt.createQmlObject(qmlCreateString, gridBtns);
            dynamicHandlersBtns[i] = btn;
        }

        //不管有多少个Handler，最终始终增加一个close按钮，用于推出界面
        var closeBtnCreateString =
                'import QtQuick.Controls 2.0;'+
                'import QtQuick.Controls.Material 2.0;'+
                'Button{'+
                'implicitHeight: 50;'+
                'implicitWidth:'+ handlerBtnWidth +';'+
                'highlighted:true;'+
                'Material.accent: Material.Orange;'+
                'onClicked: {'+
                '    close();'+
                '    ;'+
                '}'+
                '}';

        var btnControl = Qt.createQmlObject(closeBtnCreateString, gridBtns);
        btnControl.text = qsTr("Close");
        dynamicHandlersBtns[dynamicHandlersBtns.length] =  btnControl;

        //4.open Popup
        exceptionPopup.open();

        var  w = exceptionPopup.width;
        var h = exceptionPopup.height;
    }

    function close(){
        var cnt = dynamicHandlersBtns.length;
        while(cnt != 0){
            var deleted = exceptionMsgDlg.dynamicHandlersBtns.splice(-1, 1);
            deleted[0].destroy();
            cnt = dynamicHandlersBtns.length;
        }

        exceptionPopup.close();
    }

    //<<<--------------------------------------------------------------------------------

}
