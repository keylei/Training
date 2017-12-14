import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

//在别的文件中导入独立文件的Component，需要在一开始import相对路径
import "../Component"

ApplicationWindow
{
    visible: true;
    width:600;
    height: 600;


    Text{
        id: txtClr;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        text: "Hello World!";
        font.pixelSize: 32;
    }

    ColorPicker{
        id: pickerRed;
        color: "red";
        focus: true;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        //这个键能够自定支持左右键切换
        KeyNavigation.right: pickerBlue;
        KeyNavigation.tab: pickerBlue;
        onColorPicked: {
            txtClr.color = clr;//这里绑定一个匿名代码块实现
        }
    }

    //这里需要特别注意的是，实例的ID和顶层Item的id是各自独立的，这也好理解，一个是类型ID
    //一个是实例ID
    ColorPicker{
        id: pickerBlue;
        color: "blue";
        anchors.left: pickerRed.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        KeyNavigation.left: pickerRed;
        KeyNavigation.tab: pickerPink;
        KeyNavigation.right: pickerPink;
    }

    ColorPicker{
        id: pickerPink;
        color: "pink";
        anchors.left: pickerBlue.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;

        KeyNavigation.left: pickerBlue;
        KeyNavigation.tab: pickerRed;
    }

    Component.onCompleted: {
        pickerBlue.colorPicked.connect(setTextColor);//通过绑定函数实现
        pickerPink.colorPicked.connect(setTextColor);
    }

    function setTextColor(clr)
    {
        txtClr.color = clr;
    }
}
