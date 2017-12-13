import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    TabBar {
        id: bar
        width: parent.width
        TabButton {
            text: qsTr("Home")
        }
        TabButton {
            text: qsTr("Discover")
        }
        TabButton {
            text: qsTr("Activity")
        }
    }

    StackLayout {
        width: parent.width;
        anchors.top: bar.bottom;
        anchors.topMargin: 20;
        currentIndex: bar.currentIndex;
        Rectangle {
            id: tabHome;
            anchors.fill: parent;
            Text{
                text:"Home";
                anchors.centerIn: parent;
            }
        }
        Item {
            id: tabDiscovery;
            anchors.fill: parent;
            Text{
                text:"Discovery";
                anchors.centerIn: parent;
            }
        }
        Item {
            id: tabActivity;
            anchors.fill: parent;
            Text{
                text:"Activity";
                anchors.centerIn: parent;
            }
        }
    }
}
