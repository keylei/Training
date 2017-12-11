import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    //如果明确知道QML对象的属性类型，直接指定类型(放弃var)，这会提高效率
    property real angle: 90;

    Text{
        width: 150;
        height: 100;
        wrapMode: Text.WordWrap;
        font.bold: true;
        font.pixelSize: 24;
        font.underline: true;
        text:"Hello";
        anchors.centerIn: parent;
        color: "blue";
    }

    Button{
        text: "QML Basic Type";
        onClicked:{

            console.log(angle);

            console.log("%1 visual children:" .arg(children.length));
            for(var i = 0; i < children.length; i++){
                console.log( children[i] );
            }
        }
    }
}
