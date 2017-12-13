import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width:360;
    height: 600;

    //假如GridLayout缩放了，其所有的子Item会重新排列，
    //如果仅仅想要一行或者一列，使用RowLayout/ColumnLayout就可以了
    //默认所有的元素会根据fow属性进行排列，flow默认从做到右
    //假如列属性指定了，它被认为是一行所能拥有的最大列数

    //列属性只有在flow从左到右是才使用
    //行属性只有在flow从上到下时才使用
    //能够通过 Layout.row/Layout.column指定存放的单元格
    //通过Layout.rowSpan/ Layout.columnSpan 属性指定行和列间隔

//    Text {
//        id: centerText;
//        text: "A Single Text.";
//        anchors.centerIn: parent;
//        font.pixelSize: 24;
//        font.bold: true;
//    }

    GridLayout {
        anchors.margins: 10;
        columns: 3;
        width: 360;
        height:  500;

        Rectangle { color: "red"; width: 200; height: 200 }
        Rectangle { color: "green"; width: 80; height: 100 }
        Rectangle { color: "blue"; width: 200; height: 80 }
        Rectangle { color: "cyan"; width: 100; height: 200 }
        Rectangle { color: "magenta"; width: 40; height: 40 }
        Rectangle { color: "black"; width: 40; height: 160 }
    }
}
