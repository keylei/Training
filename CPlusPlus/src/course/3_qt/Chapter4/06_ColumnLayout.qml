import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width:360;
    height: 600;


    ColumnLayout{
        spacing: 2;
        anchors.fill: parent;

        Rectangle {
            Layout.alignment: Qt.AlignCenter
            color: "red"
            Layout.preferredWidth: 100
            Layout.preferredHeight: 100

            Text {
                anchors.centerIn: parent;
                text: parent.width + 'x' + parent.height;
            }
        }

        Rectangle {
            Layout.alignment: Qt.AlignRight
            color: "green"
            Layout.preferredWidth: 100
            Layout.preferredHeight: 150

            Text {
                anchors.centerIn: parent;
                text: parent.width + 'x' + parent.height;
            }
        }

        Rectangle {
            Layout.alignment: Qt.AlignBottom
            Layout.fillHeight: true//只有这个为true，放缩放Layout时，大小才会发生变化
            color: "blue"
            Layout.preferredWidth: 150
            Layout.preferredHeight: 80

            Text {
                anchors.centerIn: parent;
                text: parent.width + 'x' + parent.height;
            }
        }
    }
}
