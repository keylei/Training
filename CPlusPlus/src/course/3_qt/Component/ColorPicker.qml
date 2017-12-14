import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

//独立文件定义Component
//1.我们在定义Component时要遵守一个约定，组件名必须和QML文件名一致，组件名第一个字母
//大写
//2.单独在文件内定义组件，不需要Component对象，只有在其它QML文档中嵌入式定义组件时
//才需要Component对象

Rectangle{
    id: rectColor;
    width: 50;
    height: 30;

    signal colorPicked(color clr);

    MouseArea{
        anchors.fill: parent;
        onClicked: {
            rectColor.colorPicked(rectColor.color);
            mouse.accepted = true;
            rectColor.focus = true;
        }
    }

    //按backSpace
    Keys.onReturnPressed: {
        rectColor.colorPicked(rectColor.color);
        event.accepted = true;
    }

    //按回车键
    Keys.onSpacePressed: {
        rectColor.colorPicked(rectColor.color);
        event.accepted = true;
    }

    onFocusChanged: {
        configureBorder();
    }

    Component.onCompleted: {
        configureBorder();
    }

    //实现在获取/失去焦点时重新设置边框的宽度和颜色
    function configureBorder(){
        rectColor.border.width = rectColor.focus ? 2 : 0;
        rectColor.border.color = rectColor.focus ? "#90D750" : "#808080";
    }
}
