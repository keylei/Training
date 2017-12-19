import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow {
    id: wnd;
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Component.onCompleted: {
        // 连接信号和槽
//        translator.langTypeChanged.connect(  Qt. );
    }

    // 标题
    Text {
        id: label;
        text: qsTr("hello world");
        anchors.centerIn: parent

    }

    Text {
        id: label2;
        text: qsTr("lalala");
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 10;
        anchors.left: parent.left;
        anchors.leftMargin: 10;
    }

    Button {
        id: btnChgLang;
        x: 100;
        y: 20;
        text: qsTr("translate");

        // 鼠标区域
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if(translator.langType == 0)
                {
                    translator.langType = 1;
                }
                else
                {
                    translator.langType = 0;
                }
            }
        }
    }


}
