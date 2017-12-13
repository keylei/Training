import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    GroupBox {
        label: CheckBox {
            id: chkSync
            checked: true
            text: qsTr("Synchronize")
        }

        ColumnLayout {
            anchors.fill: parent
            enabled: chkSync.checked
            CheckBox { text: qsTr("E-mail") }
            CheckBox { text: qsTr("Calendar") }
            CheckBox { text: qsTr("Contacts") }
        }
    }
}
