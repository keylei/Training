import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width:600;
    height: 600;

    Button{
        id: btnQuit;
        x: 0;
        y: 0;
        text: "Quit";

        //>>>----------------------------------------------------------------------------------------------------------
        //1. 信号处理器
        //这一对花括号实际上是一个匿名函数，除了这里，没有地方能够调用
        //一般是on<Signal>这种形式
        onClicked: {
            //Qt实际上是一个Global对象，它是Qt Quick导出到QML环境中的对象
            Qt.quit();
        }

        //>>>----------------------------------------------------------------------------------------------------------
        //2.附加信号处理器
        //<AttachingType>.on<Signal>语法
        focus: true;
        Keys.enabled: true;
        Keys.onEscapePressed: {
            Qt.quit();
        }
    }

    //>>>----------------------------------------------------------------------------------------------------------
    //3.Component附加信号
    //可以用来在Component创建完成或销毁时执行一些ECMAScript代码做一些初始化和反初始化
    //的工作
    Component.onCompleted: {
        console.log("Completed!");
    }

    Component.onDestruction: {
        console.log("Destruction!");
    }

    //>>>----------------------------------------------------------------------------------------------------------
    //4.Connections
    //用于场合
    //1. 需要将多个对象链接到同一个QML信号上
    //2. 需要在发出信号的对象作用域之外建立连接
    //3. 发射信号的对象没有在QML中定义(可能是C++导出的)
    Rectangle{
        id: rectChgClr;
        anchors.top: btnQuit.bottom;
        anchors.topMargin: 8;
        width: 320;
        height: 240;
        color: "gray";

        Text{
            id: txt1;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: parent.top;
            anchors.topMargin: 20;
            text:"One";
            color: "blue";
            font.pixelSize: 28;
        }

        Text{
            id: txt2;
            anchors.horizontalCenter: parent.horizontalCenter;
            anchors.top: txt1.bottom;
            anchors.topMargin: 8;
            text:"Two";
            color: "blue";
            font.pixelSize: 28;
        }

        Button{
            id: btnChgClr;
            anchors.top: txt2.bottom;
            anchors.topMargin: 8;
            anchors.horizontalCenter: parent.horizontalCenter;
            text: "Change";
        }

        //Connection也是一个对象
        Connections{
            target: btnChgClr;
            onClicked:{
                txt1.color = Qt.rgba(Math.random(), Math.random(),Math.random());
                txt2.color = Qt.rgba(Math.random(), Math.random(),Math.random());
            }
        }
    }

    //>>>----------------------------------------------------------------------------------------------------------
    //5. 定义自己的信号
    //    如果你自己定义新的QML类型，可以使用signal关键字给类型添加信号
    //    signal <name>[([<type><parameter name[,...]])]
    Component{
        id: compClr;

        Rectangle{
            id: rectClrPicker;
            width: 50;
            height: 30;
            anchors.bottom: parent.bottom;
            color: "red";

            //这里首字母小写
            signal clrPicked(color clr);

            //信号的定义可以在Connect中实现，也可以在当前对象中实现
            signal clrReceived(color clr);
            onClrReceived:{
                console.log("Received Color in signal! ", color);
            }

            MouseArea{
                anchors.fill: parent;
                onPressed: rectClrPicker.clrPicked(rectClrPicker.color);
            }

            //>>>----------------------------------------------------------------------------------------------------------
            //6.信号的连接
            Component.onCompleted: {
                //1.信号可以直接连接到一个函数
                clrPicked.connect(receiveColor);
                //2.信号连接信号
                clrPicked.connect(clrReceived);
            }

            function receiveColor(color)
            {
                console.log("Received Color in function! ", color);
            }
        }
    }

    Text{
        id: txtClr;
        anchors.horizontalCenter: parent.horizontalCenter;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        anchors.left: rectChgClr.right;
        anchors.leftMargin: 4;
        text: "Hello World!";
        font.pixelSize: 32;
    }

    Loader{
        id: ldrRed;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        sourceComponent: compClr;
        onLoaded: {
            item.color = "red";
        }
    }

    Loader{
        id: ldrBlue;
        anchors.left: ldrRed.right;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        sourceComponent: compClr;
        onLoaded: {
            item.color = "blue";
        }
    }

    Connections{
        target: ldrRed.item;
        //注意: 这里首字母变大写
        onClrPicked:{
            txtClr.color = clr;
        }
    }

    Connections{
        target: ldrBlue.item;
        //注意: 这里首字母变大写
        onClrPicked:{
            txtClr.color = clr;
        }
    }
}
