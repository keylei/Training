import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    //关于snap 请参考：https://doc.qt.io/qt-5/qml-qtquick-controls2-slider.html
    Slider {
        x: 100;
        from: 1;
        value: 25;
        to: 100;
        snapMode: Slider.SnapOnRelease;
    }

    Slider {
        x: 150;
        y: 200;
        from: 1;
        value: 25;
        to: 100;
        orientation: Qt.Vertical;
    }
}
