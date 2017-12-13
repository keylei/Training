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

        }
    }
}
