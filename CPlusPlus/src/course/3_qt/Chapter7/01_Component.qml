import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3


ApplicationWindow
{
    visible: true;
    width: 400;
    height: 240;

    Canvas{
        anchors.fill: parent;

        onPaint: {
            var ctx = getContext("2d");
            ctx.lineWidth = 2;
            ctx.strokeStyle = "red";
            ctx.fillStyle = "blue";
            ctx.begin();
            ctx.rect(100, 80, 120, 80);
            ctx.fill();
            ctx.stroke();
        }
    }
}
