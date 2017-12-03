import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    Rectangle {
        id: rect;//id属性是唯一的, 在同一个QML文件中不同对象的id属性的值不能重复
        width:640;//int
        height:335;
        Image{
            source:"images/cat.jpeg";
        }

        //附加到一个对象上的额外属性， 附加属性放到最后集中赋值
        Keys.enabled: false;
    }

    Button{
        id:btnQuit
        text:"Quit";//string
        z:1.5;//real
        visible: true;//bool
        anchors.top: rect.bottom;

        //类似与C++中明确定义的函数，一般是on<Signal>这种形式
        onClicked: {
            Qt.quit();
        }
    }

    Item{
        id:list
        children: [
            //列表的属性是包含在方括号内,以逗号分隔的多个元素的集合
            Text{
                id:txtOne;
                text:"textOne";
            },
            Text{
                id:txtTwo;
                anchors.top: txtOne.bottom;
                text:"textTwo";
            }
        ]

        //附加信号处理器
        Component.onCompleted: {
            for(var i = 0; i <children.length;i++)
            {
                //        列表的访问和数组类似:
                //         1.可以用[value1,value,...,valueN]这种形式给list对象赋值
                //        2.length属性提供了列表内元素的个数
                //        3.列表内的元素通过数组下标来访问
                console.log("text of lable",i,":",children[i].text);
            }
        }
    }

    //在某些情况下使用一个"."符号或分组符号将相关的属性形成一个
    //逻辑组
    //    注意:分组属性一律放在一起集中赋值，如下例的font。禁止同一分组的属性被隔开赋值。
    Text{
        font.pixelSize: 18;
        font.bold: true;
        anchors.bottom: rect.bottom;
        text:"分组属性";
    }

    //属性初始化的顺序:
    //    ①id属性(如果有的话)
    //    ②数据源相关属性（如果有的话，source、componentSource…）
    //    ③Size相关属性（width，height，implictWidth、color…）
    //    ④显示相关属性（text，context…）
    //    ⑤布局相关属性（Row、Column、Grid…）
    //    ⑥其它属性
    //    ⑦附加属性
    //    ⑧信号处理器
    //    ⑨自定义属性
    Button {
        id: rectTarget;                     //id属性
        implicitWidth: 120;                //Size相关属性
        implicitHeight: 50;
        text: "Target";                //显示相关属性
        anchors.top:btnQuit.bottom;
        anchors.left: parent.left;             //布局相关参数

        //        …                              //其他相关
        Keys.enabled: false;                //附加属性
        signal clicked;                    //信号处理器

//        property alias iconSource: icon.source; //自定义属性
    }
}
