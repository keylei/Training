import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:360;
    height: 240;

    //    Row沿着一行安置它的孩子们，比锚布局更加方便，一旦你
    //    把一个Item交给Row来管理，那就不要再使用Item的x，y，anchor等
    //    属性了

    Row {
        //Row本身可以通过锚布局
        anchors.centerIn: parent;
        spacing: 4 //指定Item之间的间隔
        layoutDirection: Qt.RightToLeft;

        Rectangle { color: "red"; width: 100; height: 100 }
        Rectangle { color: "green"; width: 40; height: 100 }
        Rectangle { color: "blue"; width: 100; height: 40 }
    }
}
