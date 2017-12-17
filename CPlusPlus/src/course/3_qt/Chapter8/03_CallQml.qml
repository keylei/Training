import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow
{
    //在QObject有一个objectName，这个对象的名字属性，就可以用于查找对象
    objectName: "wndRoot";
    visible: true;
    width: 400;
    height: 400;

    Text{
        objectName: "txtHelloWorld";
        text: "Hello World";
        anchors.centerIn: parent;
        font.pixelSize: 26;
    }

    Button{
        objectName: "btnQuit";
        anchors.right: parent.right;
        anchors.rightMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        text: "quit";
    }
}
