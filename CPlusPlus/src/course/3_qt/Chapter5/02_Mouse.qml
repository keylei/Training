import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width:600;
    height: 600;

    //  按下左键改变矩形的颜色，右键退出应用
    MouseArea{
        anchors.fill: parent; //MouseArea本身就是一个Item对象，有anchor属性
        //设定接受哪些鼠标按键产生的事件(左键/右键/中键)，这里表示接受左键和右键
        acceptedButtons: Qt.LeftButton | Qt.RightButton;
        //设置是否接受鼠标事件，默认为true
        enabled: true;

        onClicked: {
            if(mouse.button === Qt.RightButton){
                Qt.quit();
            }
            else if( mouse.button === Qt.LeftButton){
                color = Qt.rgba(
                            (mouse.x % 255) / 255.0,
                            (mouse.y % 255) / 255.0,
                            0.6,
                            1);
            }
        }

        onDoubleClicked: {
            color = "gray";
        }
    }
}
