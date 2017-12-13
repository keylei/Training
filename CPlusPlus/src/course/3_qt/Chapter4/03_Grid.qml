import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width:360;
    height: 500;

    //Grid是一个能够把子item放置在网格空间的定位器
    //Grid会自动建立一个足够防止item的空间，默认是从左往右，自上而下，每一个item的左上角
    //坐标默认为(0,0)
    //一个Grid默认有4列，按需会创建需要的行，行和列的数量会被相应的属性约束

    Grid {
        columns: 3;
        spacing: 2;

        //        默认的对齐，垂直方向是顶部对齐，水平方向收到layoutDirection属性设置，

        //注意: 只能设置左右方向
        //        layoutDirection : Grid.LeftToRight;//默认设置
        //        layoutDirection : Grid.RightToLeft; //右->左

        //可以设置左右和上下方向都可以设置
        horizontalItemAlignment: Grid.AlignRight;
        verticalItemAlignment: Grid.AlignVCenter;
          anchors.centerIn: parent;

        Rectangle { color: "red"; width: 50; height: 50 }
        Rectangle { color: "green"; width: 20; height: 25 }
        Rectangle { color: "blue"; width: 50; height: 20 }
        Rectangle { color: "cyan"; width: 25; height: 50 }
        Rectangle { color: "magenta"; width: 10; height: 10 }
        Rectangle { color: "black"; width: 10; height: 40 }
    }
}
