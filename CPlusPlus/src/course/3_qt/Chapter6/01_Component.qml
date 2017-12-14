import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width:600;
    height: 600;

    //>>>----------------------------------------------------------------------------------------------------------
    //嵌入式的Component

    //Component本身不是Item的派生类(是一种类型)，必须被实例化后才可能被显示，实例化
    //一个嵌入在QML文档中定义的组件，可以使用Loader
    Component{
        id: compColor;

        //Component 只能包含一个顶层Item，而且在这个Item之外不能定义任何数据，除了id
        Rectangle{
            id: rectColorPicker;
            width: 50;
            height: 30;

            signal colorPicked( color clr );
            MouseArea{
                anchors.fill: parent;
                onPressed: rectColorPicker.colorPicked(rectColorPicker.color);
            }
        }
    }

    Text{
        id: txtClr;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        text: "Hello World!";
        font.pixelSize: 32;
    }

    Loader{
        id: ldrRed;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        sourceComponent: compColor; //设置为sourceComponent等于是构造了一个对象
        onLoaded: {
            item.color = "red";
        }
    }

    Loader{
        id: ldrBlue;
        anchors.left: ldrRed.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        sourceComponent: compColor;
        onLoaded: {
            item.color = "blue";
        }
    }

    Connections{
        target: ldrRed.item;
        //注意: 这里首字母变大写
        onColorPicked:{
            txtClr.color = clr;
        }
    }

    Connections{
        target: ldrBlue.item;
        //注意: 这里首字母变大写
        onColorPicked:{
            txtClr.color = clr;
        }
    }
}
