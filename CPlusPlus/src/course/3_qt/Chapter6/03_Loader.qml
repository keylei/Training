import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow
{
    visible: true;
    width:600;
    height: 600;

    //>>>----------------------------------------------------------------------------------------------------------
    //1.通过source加载组件
    //前面已经讲过，这里不讲阐述

    //>>>----------------------------------------------------------------------------------------------------------
    //2.从文件加载组件
    // 同样使用Loader加载，只要指定Loader的source属性即可
    Text{
        id: txtColor;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        text: "Hello World!";
        font.pixelSize: 32;
    }

    Loader{
        id: ldrRed;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        //这里直接设置为相对路径就可以了
        source: "../Component/ColorPicker.qml";

        onLoaded: {
            item.color = "red";
            item.focus = true;
        }

        onFocusChanged: {
            item.focus = focus;
        }
    }

    Loader{
        id: ldrBlue;
        anchors.left: ldrRed.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        //这里直接设置为相对路径就可以了
        source: "../Component/ColorPicker.qml";

        onLoaded: {
            item.color = "blue";
        }

        onFocusChanged: {
            item.focus = focus;
        }
    }

    Connections{
        target: ldrRed.item;
        //注意: 这里首字母变大写
        onColorPicked:{
            txtColor.color = clr;
            if(!ldrRed.focus){
                ldrRed.focus = true;
                ldrBlue.focus = false;
            }
        }
    }

    Connections{
        target: ldrBlue.item;
        //注意: 这里首字母变大写
        onColorPicked:{
            txtColor.color = clr;
            if(!ldrBlue.focus){
                ldrBlue.focus = true;
                ldrRed.focus = false;
            }
        }
    }
}
