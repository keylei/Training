import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    ColumnLayout {
        CheckBox {
            checked: true
            text: qsTr("First")
            tristate: true; // 有三种状态
        }
        CheckBox {
            text: qsTr("Second")
            tristate: true;
        }
        CheckBox {
            checked: true
            text: qsTr("Third")
        }
    }
}
