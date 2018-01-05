import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    id: appWnd;
    visible: true;
    width:600;
    height: 600;
    color: "#EEEEEE";

    //QML支持在ES中动态创建对象，这对于延迟对象的创建，缩短应用启动的时间很有帮助
    //ES中有2中方式可以动态地创建对象
    //1.使用Qt.CreateComponent()动态地创建一个组件对象，然后使用Component的createObject()
    //   方法创建对象
    //2.使用Qt.CreateQmlObj()从一个Qml字符串直接创建一个对象

    //>>>----------------------------------------------------------------------------------------------------------
    //1.使用Qt.createComponent()
    // 在QML文件中定义了一个组件，想动态的创建它的实例
    // 函数原型如下:
    //           object createComponent(url, mode, parent);
    //一旦拥有了组件对象，可以调用createObject()方法创建一个组件的实例
    Rectangle{
        id: rect1;
        width: 300;
        height: 200;
        property  int count: 0;
        property Component component: null;
        property  var dynamicObjs: new Array();

        Text{
            id: txtColor;
            text: "Hello World";
            anchors.centerIn: parent;
            font.pixelSize: 24;
        }

        function changeTextColor(clr){
            txtColor.color = clr;
        }

        function createColorPicker(clr){
            //1.通过Qt.createComponent创建对象
            //            //1.1这一步只是第一步，把组件加载进来，是createObject的前提
            //            if(rect1.component == null){
            //                rect1.component = Qt.createComponent("../Component/ColorPicker.qml");
            //            }

            //            //1.2 需要使用createObject创建实例，没创建一个实例，进来绑定信号
            //            var colorPicker;
            //            if(rect1.component.status == Component.Ready){
            //                colorPicker = rect1.component.createObject(rect1, {"color": clr, "x": rect1.count * 55, "y": 10});
            //                colorPicker.colorPicked.connect(rect1.changeTextColor);
            //            }

            //2.从QML字符串创建Component
            //需要在运行过程中根据应用的状态适时地生成用于描述对象的QML字符串，进而根据
            //这个QML字符串创建对象
            var createString =
                    'import QtQuick 2.7;'+
                    'import QtQuick.Controls 2.2;'+
                    'import QtQuick.Controls.Material 2.0;'+
                    'import  "../Component";'+
                    'ColorPicker{'+
                        'color:  ' + '"'+clr +'"'+ ';'+
                        'x: ' + rect1.count * 55+';'+
                        'y: 10;'+
                        'onColorPicked:{'+
                            'rect1.changeTextColor(color);'+
                        '}'+
                    '}';

            var colorPick = Qt.createQmlObject(createString, rect1);

            rect1.count++;
            rect1.dynamicObjs[ rect1.dynamicObjs.length] = colorPick;
        }

        Button{
            id: btnAdd;
            text: "add";
            anchors.left: parent.left;
            anchors.leftMargin: 4;
            anchors.bottom: parent.bottom;
            anchors.bottomMargin: 4;
            onClicked: {
                rect1. createColorPicker(Qt.rgba(Math.random(), Math.random(), Math.random(), 1));
            }
        }
    }

    //>>>----------------------------------------------------------------------------------------------------------

    //应当通过将source设置为空串或者sourceComponent设置为undefinded触发
    //Loader销毁它们
    //delete() 不会立即删除，会在当前代码执行接受后的某个合适的时刻删除它们
    Button{
        id: btnDel;
        text: "del";
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        onClicked: {
            if(rect1.dynamicObjs.length > 0){
                var deletedObj = rect1.dynamicObjs.splice(-1,1);
                deletedObj[0].destroy();
            }
        }
    }
}
