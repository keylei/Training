import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width:360;
    height: 600;

    RowLayout {
        anchors.fill: parent;
        spacing: 6;

        Rectangle {
            color: 'teal';
            Layout.fillWidth: true; //只有这个为true，放缩放Layout时，大小才会发生变化
            Layout.minimumWidth: 50;//最小宽度
            //代表了默认的宽度，-1表示忽略，layout将使用implicitWidth代替，默认为-1
            Layout.preferredWidth: 100;
            Layout.maximumWidth: 300;
            Layout.minimumHeight: 150;
            Text {
                anchors.centerIn: parent;
                text: parent.width + 'x' + parent.height;
            }
        }
        Rectangle {
            color: 'plum';
            Layout.fillWidth: true;
            Layout.minimumWidth: 100;
            Layout.preferredWidth: 200;
            Layout.preferredHeight: 100;
            Text {
                anchors.centerIn: parent;
                text: parent.width + 'x' + parent.height;
            }
        }
    }
}
