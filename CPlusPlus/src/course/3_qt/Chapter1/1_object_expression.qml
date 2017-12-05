import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    Rectangle {
        id: rect;
        width:640;
        height:335;
        Image{
            source:"../images/cat.jpeg";
        }
    }

    Button{
        text:"Quit";
        anchors.top: rect.bottom;// 注意,这里不能用表达式, 如果用了表达式会出错
        //通过id可以引用对象
        width: rect.width/3;//这里可以使用表达式, 直接为rect的1/3宽度
    }
}
