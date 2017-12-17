import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
//import an.qt.ColorMaker 1.0

ApplicationWindow
{
    visible: true;
    width: 400;
    height: 400;

    Text{
        id: txtTime;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        font.pixelSize: 26;
    }

    Rectangle{
        id: rectColor;
        anchors.centerIn: parent;
        width: 200;
        height: 200;
        color: "blue";
    }

    Button{
        id: btnStart;
        text: "Start";
        anchors.top: txtTime.bottom;
        anchors.topMargin: 4;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.botom;
        anchors.bottomMargin: 4;
        onClicked: {
            colorMaker.start();
        }
    }

    Button{
        id: btnStop;
        text: "Stop";
        anchors.top: txtTime.bottom;
        anchors.topMargin: 4;
        anchors.left: btnStart.right;
        anchors.leftMargin: 4;
        anchors.bottom: btnStart.botom;
        onClicked: {
            colorMaker.stop();
        }
    }

    function changeAlgorithm(button, algorithm){
        switch(algorithm){
        case 0:
            button.text = "RandomRGB";
            break;
        case 1:
            button.text = "RandomRed";
            break;
        case 2:
            button.text = "RandomGreen";
            break;
        case 3:
            button.text = "RandomBlue";
            break;
        case 4:
            button.text = "LinearIncrease";
            break;
        }
    }

    Button{
        id: btnAlg;
        text: "RandomRGB";
        anchors.top: txtTime.bottom;
        anchors.topMargin: 4;
        anchors.left: btnStop.right;
        anchors.leftMargin: 4;
        anchors.bottom: btnStart.bottom;
        onClicked: {
            var alg = (colorMaker.algorithm()+1)%5;
            changeAlgorithm(btnAlg, alg);
            colorMaker.setAlgorithm(alg);
        }
    }

    Component.onCompleted: {
        colorMaker.currentColor = Qt.rgba(0,180,120,255);

        //因为没有导入类型，所以无法使用类成员的LINEAR_INCREASE
        //        colorMaker.setAlgorithm(ColorMaker.LINEAR_INCREASE);
        colorMaker.setAlgorithm(2);
        changeAlgorithm(btnAlg, colorMaker.algorithm());
    }

    Connections{
        target: colorMaker;
        onCurrentTime:{ //currentTime信号是在colormaker.hpp定义的信号
            txtTime.text = strTime;
            txtTime.color = colorMaker.timeColor;
        }
    }

    Connections{
        target: colorMaker;
        onColorChanged:{
            rectColor.color = colorMaker.currentColor;
        }
    }
}
