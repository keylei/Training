import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width:600;
    height: 600;

    Rectangle{
        anchors.fill: parent;
        focus: true;

        Keys.enabled:  true;
        Keys.onEscapePressed: {
            Qt.quit();
        }

        //        设置按键事件传递的顺序，某个QML对象在这个列表属性中时，即使没有设置focus为
        //        true也能响应按键事件，如果某个按键事件被列表属性中前面的Item处理了，
        //        后面的Item就不会再收到这个按键信号。
        Keys.forwardTo: [ txtMove,  chkLikeQt ];

        Text{
            id: txtMove;
            width: 200;
            height: 30;
            text: "Moving Text";
            color: "blue";
            font { bold: true; pixelSize: 24; }
            Keys.enabled: true;

            Keys.onPressed: {
                switch(event.key){
                case Qt.Key_Left:
                    x -= 10;
                    break;
                case Qt.Key_Right:
                    x += 10;
                    break;
                case Qt.Key_Up:
                    y -= 10;
                    break;
                case Qt.Key_Down:
                    y += 10;
                    break;
                default:
                    return;
                }
                event.accepted = true;// 一旦item接受的按键，后续的控键不会再接受到这些键
            }
        }

        CheckBox{
            id: chkLikeQt;
            text: "Like Qt Quick";
            anchors.left: parent.left;
            anchors.leftMargin: 10;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 10;
            z: 1;
        }
    }
}
