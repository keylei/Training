import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    width:650;
    height:800;
    visible: true;

    Rectangle{
        id:rect1;
        width:100;
        height:100;
        //        QML中可以使用颜色的名字，也可以使用#RRGGBB, 还可以使用Qt.rgba(),
        //        Qt.lighter等方法构造，
        color:"blue";
        border.color: "#808080";
        border.width: 2;
        radius:12;
    }

    Rectangle{
        id:rect2;
        width:100;
        height:100;
        anchors.left: rect1.right;
        color:"#00AA00";
        border.color: "#808080";
        border.width: 2;
        radius:12;
    }

    Rectangle{
        id:rect3;
        width:100;
        height:100;
        anchors.left: rect2.right;
        color:"#800000B0";
        border.color: "#800000B0";
        border.width: 2;
        radius:12;
    }

    Rectangle{
        id:rect4;
        width:100;
        height:100;
        anchors.left: rect3.right;
        color:Qt.rgba(0.8,0.6,0.4,1.0);
        border.color: "#808080";
        border.width: 2;
        radius:12;
    }

    Rectangle{
        id:rect5;
        width:100;
        height:100;
        anchors.left: rect4.right;
        border.color: "#808080";
        border.width: 2;
        radius:12;
        gradient: Gradient{
            GradientStop{position: 0.0;color:"#202020";}
            GradientStop{position: 0.33;color:"blue";}
            GradientStop{position: 1.0;color:"#FFFFFF";}
        }
    }

    //    z属性的类型为real， 数值越小， 图元的越低
    //    x,y,width,height四个属性结合起来， 可以完成界面布局， 不过这种
    //    采用绝对坐标的布局方式， 不太容易适应多种多样的移动设备分辨率
    Rectangle{
        id:rect6;
        x:500;
        y:0;
        width:100;
        height:100;
        color:"#000080";
        z:0.5;
    }

    Rectangle{
        id:rect7;
        x:520;
        y:20;
        width:100;
        height:100;
        color:"#00c000";
        z:1;
        opacity: 0.6;/*指定一个图元的透明度， 取值在0到1之间*/
    }


}
