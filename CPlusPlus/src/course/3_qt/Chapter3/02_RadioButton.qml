import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    GroupBox {
        id: group2
        title: qsTr("Tab Position")
        Layout.fillWidth: true
        RowLayout {
            RadioButton {
                id: topButton
                text: qsTr("Top")
                checked: true
                Layout.minimumWidth: 100
            }
            RadioButton {
                id: bottomButton
                text: qsTr("Bottom")
                Layout.minimumWidth: 100
            }
        }
    }
}
