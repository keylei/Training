import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    //>>>----------------------------------------------------------------------------------------------------------
    //行编辑

    Text{
        id: txt1;
        text: "TextInput";
        anchors.centerIn: parent;
    }

    //讲下Widget和Control的区别：
    //http://doc.qt.io/qt-5/topics-ui.html#comparison
    //TextInput & TextEdit属于Widget
    //TextField & TextArea属于Control

    //具体如果想要看qt control有哪些控件， 在helper中输入control

    //TextInput是不带任何背景任何样式的，可以进行高度定制化, 属于Widget
    //接口更加复杂，需要指定背景，大小，默认行为等，适合开发自定义控件
    TextInput{
        id: txtin;
        width: 100;
        anchors.left: txt1.right;
        anchors.leftMargin: 8;
        anchors.bottom: txt1.bottom;
        validator: IntValidator{ top: 15; bottom: 6;}
        focus: true;


        onAccepted: {
            console.log(txtin.text);
        }
    }

    Text{
        id: txt2;
        text: "TextField";
        anchors.left: txt1.left;
        anchors.top: txt1.bottom ;
        anchors.topMargin: 10; // 这个值是为了保证文本和TextField进行下对齐
    }

    //TextField可以隐式的直接使用来自与布局/窗体的样式，不需要用户指定
    //任何样式，使用接口更加简单
    TextField{
        id: txtfld;
        width: 100;
        anchors.left: txtin.left;
        anchors.top: txtin.bottom;
        validator: IntValidator{ top: 15; bottom: 6;}

        onAccepted: {
            console.log(txtfld.text);
        }
    }

    //>>>----------------------------------------------------------------------------------------------------------
    //文本块

    //TextEdit和TextInput一样，来自与Widget，需要指定背景
    TextEdit{//这个不同于Lable/Text，还不能显示富文本
        id: txtedit;
        width: 240
        anchors.left: txt2.left;
        anchors.top: txt2.bottom;
        anchors.topMargin: 8;
        text: "<b>Hello</b> <i>World!</i>"
        font.family: "Helvetica"
        font.pointSize: 20
        color: "blue"
        focus: true
    }

    TextArea{
        id: txt;
        width: 240
        anchors.left: txtedit.left;
        anchors.top: txtedit.bottom;
        anchors.topMargin: 8;
        text: "<b>Hello</b> <i>World!</i>"
        font.family: "Helvetica"
        font.pointSize: 20
        color: "blue"
        focus: true
    }
}
