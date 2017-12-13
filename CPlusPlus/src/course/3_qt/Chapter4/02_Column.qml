import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:360;
    height: 500;

    //    Row沿着一行安置它的孩子们，比锚布局更加方便，一旦你
    //    把一个Item交给Row来管理，那就不要再使用Item的x，y，anchor等
    //    属性了

    Column {
        //Row本身可以通过锚布局
        anchors.centerIn: parent;
        spacing: 4; //指定Item之间的间隔
        focus: true;
        Keys.onSpacePressed: rectGreen.visible = !rectGreen.visible;

        //        当有元素出现或者移除时，会触发动画
        //            当空格键按下时，绿色矩形的可见状态切换，蓝色矩形发生移动，移动动画开始触发
        move: Transition {
            NumberAnimation { properties: "x,y"; duration: 1000 }
        }

        Rectangle { color: "red"; width: 100; height: 100 }
        Rectangle { id: rectGreen; color: "green"; width: 40; height: 100 }
        Rectangle { color: "blue"; width: 100; height: 40 }
    }
}
