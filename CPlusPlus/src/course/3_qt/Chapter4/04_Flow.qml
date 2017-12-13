import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width:360;
    height: 500;

    //Flow其实和Grid类似，不同之处是它没有显式的行，列数，它会计算子Item的尺寸
    //然后与自身尺寸比较，按需折行

    Flow {
        flow: Flow.TopToBottom;
        spacing: 4;
        width:360;
        height: 500;

        Rectangle { color: "red"; width: 200; height: 200 }
        Rectangle { color: "green"; width: 80; height: 100 }
        Rectangle { color: "blue"; width: 200; height: 80 }
        Rectangle { color: "cyan"; width: 100; height: 200 }
        Rectangle { color: "magenta"; width: 40; height: 40 }
        Rectangle { color: "black"; width: 40; height: 160 }
    }
}
