import QtQuick 2.7
import QtQuick.Controls 2.0

ApplicationWindow
{
    visible: true;
    width: 300;
    height: 600;

    Rectangle{
        visible: true;

        Rectangle{
            id: rect1;
            anchors.left: parent.left;
            anchors.leftMargin: 20;
            anchors.top: parent.top;
            anchors.topMargin: 20;
            width: 120;
            height: 120;
            gradient: Gradient{
                GradientStop{ position: 0.0; color: "#202020"; }
                GradientStop{ position: 1.0; color: "#A0A0A0"; }
            }
        }

        Rectangle{
            id: rect2;
            anchors.left: rect1.right;
            anchors.leftMargin: 20;
            anchors.top: rect1.top;
            width: 120;
            height: 120;
            rotation: 90;
            gradient: Gradient{
                GradientStop{ position: 0.0; color: "#202020"; }
                GradientStop{ position: 1.0; color: "#A0A0A0"; }
            }
        }

        Rectangle{
            color: "blue";
            anchors.top: rect1.bottom;
            anchors.topMargin: 20;
            anchors.left: parent.left;
            anchors.leftMargin: 20;
            width: 120;
            height: 120;

            Rectangle{
                anchors.centerIn: parent;//centerIn标示将一个Item居中放置到另一个Item内
                width: 100;
                height: 100;
                radius: 8;
                antialiasing: true;
                color: "red";
                focus: true;//这个属性必须安置为true，否则按键将不被响应

                Keys.enabled: true;
                Keys.onEscapePressed: Qt.quit();
                Keys.onPressed: {
                    switch(event.key){
                    case Qt.Key_0:
                    case Qt.Key_1:
                    case Qt.Key_2:
                    case Qt.Key_3:
                    case Qt.Key_4:
                    case Qt.Key_5:
                    case Qt.Key_6:
                    case Qt.Key_7:
                    case Qt.Key_8:
                    case Qt.Key_9:
                        event.accepted = true;//如果一个按键被处理，event.accepted应该为true，以免继续被传递
                        keyView.text = event.key - Qt.Key_0;
                        break;
                    }
                }

                Text{
                    id: keyView;
                    font.bold: true;
                    font.pixelSize: 24;
                    text: qsTr("text");
                    anchors.centerIn: parent;
                }
            }
        }
    }
}
