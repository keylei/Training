import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    id: appWnd;
    visible: true;
    width:600;
    height: 600;
    color: "#EEEEEE";

    //来确定是否要加载ColorPicker
    property bool isColorPickerShow: false;

    Text{
        id: txtColor;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        text: "Hello World!";
        font.pixelSize: 32;
    }

    Button{
        id: btnCtrl;
        text: "Show";
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        onClicked: {
            if(appWnd.isColorPickerShow){
                ldrRed.sourceComponent = undefined;//设置sourceComponent为undefined和source为空两种方式都可以
                ldrBlue.source = "";
                appWnd.isColorPickerShow = false;
                btnCtrl.text = "Show";
            }
            else{
                ldrRed.source = "../Component/ColorPicker.qml";
                ldrRed.item.colorPicked.connect(onRedPicked);
                ldrBlue.source = "../Component/ColorPicker.qml";
                ldrBlue.item.colorPicked.connect(onBluePicked);
                ldrRed.focus = true;
                appWnd.isColorPickerShow = true;
                btnCtrl.text = "Hide";
            }
        }
    }

    Loader{
        id: ldrRed;
        anchors.left: btnCtrl.right;
        anchors.leftMargin: 4;
        anchors.bottom: btnCtrl.bottom;
        anchors.bottomMargin: 4;

        KeyNavigation.right: ldrBlue;
        KeyNavigation.tab: ldrBlue;

        onLoaded: {
            if( null != item){
                item.color = "red";
                item.focus = true;
            }
        }

        onFocusChanged: {
            if( null != item){
                item.focus = focus;
            }
        }
    }

    Loader{
        id: ldrBlue;
        anchors.left: ldrRed.right;
        anchors.leftMargin: 4;
        anchors.bottom: ldrRed.bottom;

        KeyNavigation.right: ldrRed;
        KeyNavigation.tab: ldrRed;


        onLoaded: {
            if( null != item){
                item.color = "blue";
            }
        }

        onFocusChanged: {
            if( null != item){
                item.focus = focus;
            }
        }
    }

    function onBluePicked(clr){
        txtColor.color = clr;
        if(!ldrBlue.focus){
            ldrBlue.focus = true;
            ldrRed.focus = false;
        }
    }

    function onRedPicked(clr){
        txtColor.color = clr;
        if(!ldrRed.focus){
            ldrRed.focus = true;
            ldrBlue.focus = false;
        }
    }
}
