import QtQuick 2.2
import QtQuick.Controls 2.2
//import QtQuick.Layouts 1.3

ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    //    https://doc.qt.io/qt-5/qml-qtquick-controls2-scrollbar.html

    //>>>----------------------------------------------------------------------------------------------------------
    //1.Attaching ScrollBar to a Flickable
    Flickable{
        id: flick;
        x: 300;
        y: 0;
        width: 200;
        height: 200;
        clip: true;
        contentWidth: image.width;
        contentHeight: image.height;
        ScrollBar.vertical: ScrollBar {
               parent: flick.parent
               anchors.top: flick.top;
               anchors.left: flick.right;
               anchors.bottom: flick.bottom;
           }

        ScrollBar.horizontal: ScrollBar {
               parent: flick.parent
               anchors.left: flick.left;
               anchors.right: flick.right;
               anchors.top: flick.bottom;
           }

        Image{
            id: image;
            source: "../Images/cat.jpeg";
        }
    }

    //>>>----------------------------------------------------------------------------------------------------------
    //2.No-attached Scroll Bars
    Rectangle {
        id: rect;
        x: 100;
        y: 500;
        clip: true; //如果这个为false的话，那么其中的元素大小如果超过父控件的话，会超出这个父控件
        width: 200;
        height: 200;
        border.color: "black";
        anchors.centerIn: parent;

        Text {
            id: txt;
            text: "<p><b>R</b>ime</p><p><i>P</i>lato</p>";
            font.pixelSize: 100;
            x: -hbar.position * width; //这个x，y设定是为了后期能够随着ScrollBar自动调整Txt的位置
            y: -vbar.position * height;
        }

        ScrollBar {
            id: vbar;
            hoverEnabled: true;
            active: hovered || pressed;
            orientation: Qt.Vertical;
            size: rect.height / txt.height; //0-1 是一个相对长度
            anchors.top: parent.top;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
        }

        ScrollBar {
            id: hbar;
            hoverEnabled: true;
            active: hovered || pressed;
            orientation: Qt.Horizontal;
            size: rect.width / txt.width;
            anchors.left: parent.left;
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
        }
    }
}
