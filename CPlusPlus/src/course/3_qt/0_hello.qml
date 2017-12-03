 // import 类似与c++的include，它用来导入一个模块
import QtQuick 2.7 //基本模块，如Text，Rectangle，Item，Row等
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

//除window及其派生类外，QML中其它的可见元素大多是Item的派生类，
//Item及其派生类，也可以作为QML的根对象，在Qt5.3 之前，自动生成的qml文档，就是使用
//Rectangle作为根对象

//window对象用于创建一个与操作系统相关的顶层窗口，而其他元素，如Text，Rectangle，
//Image等，都是在Window提供的场景内表演的演员
ApplicationWindow {//代表了QML应用的顶层窗口，对应的C++类型为QQuickWindow
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    SwipeView {//滑动界面
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
