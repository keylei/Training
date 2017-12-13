import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1

ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    ProgressBar {
        x: 100;
        y: 100;
        value: 0.5;
        from: 0;
        to: 1;
    }

    ProgressBar {
        x: 100;
        y: 120;
        indeterminate: true
    }
}
