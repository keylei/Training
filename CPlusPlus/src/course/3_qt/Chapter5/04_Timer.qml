import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width:600;
    height: 600;

    //QtObject是仅仅包含一个objectName属性的不可见对象，在仅仅想要一个包含自定义属性
    //的轻量级对象是非常有用的
    QtObject{
        id: objTimer;
        property  int  counter;
        Component.onCompleted: {
            objTimer.counter = 10;
        }
    }

    Text{
        id: txtShow;
        anchors.centerIn: parent;
        color: "blue";
        font.pixelSize: 40;
    }

    Timer{
        id: timer;
        interval: 1000;
        repeat: true;
        triggeredOnStart: true;
        onTriggered: {
            txtShow.text = objTimer.counter;
            objTimer.counter -= 1;
            if( objTimer.counter < 0 ){
                timer.stop();
                txtShow.text = "Clap Now";
            }
        }
    }

    Button{
        id: btnStart;
        anchors.top: timer.bottom;
        anchors.topMargin: 20;
        anchors.horizontalCenter: txtShow.horizontalCenter;
        text: "Start";
        onClicked: {
            objTimer.counter = 10;
            timer.start();
        }
    }
}
