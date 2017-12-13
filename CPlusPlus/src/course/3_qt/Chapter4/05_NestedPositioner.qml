import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width:360;
    height: 500;

    //定位器可以嵌套，比如通过Row和Column的

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
