import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    ComboBox {
        id: cmbFruits
        editable: true //ComboBox可以编辑
        model: ListModel {
            id: model
            ListElement { text: "Banana" }
            ListElement { text: "Apple" }
            ListElement { text: "Coconut" }
        }
        onAccepted: {
            if (find(editText) === -1)//通过find方法查找列表中的一个条目的索引，返回-1标示不在列表中
                model.append({text: editText})
        }
    }

    ComboBox {
        id: cmbKey
        anchors.top: cmbFruits.bottom;
        textRole: "key"
        model: ListModel {
            ListElement { key: "First"; value: 123 }
            ListElement { key: "Second"; value: 456 }
            ListElement { key: "Third"; value: 789 }
        }
        onActivated: {
            console.log(currentIndex);
            console.log(displayText);
            console.log(currentText);
            console.log(textRole);
            var data = cmbKey.model.get(currentIndex);
//            console.log(data);
            console.log(data.value);
        }

    }
}
