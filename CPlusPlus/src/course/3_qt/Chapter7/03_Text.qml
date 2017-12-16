import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow
{
    visible: true;
    width: 800;
    height: 400;

    Canvas{
        anchors.fill: parent;

        onPaint: {

            var ctx = getContext("2d");
            ctx.lineWidth = 2;
            ctx.strokeStyle = "red";
            ctx.font = "42px sans-serif";

            //创建整个窗口范围的线性渐变，范围为由绿到蓝
            var gradient = ctx.createLinearGradient( 0, 0, width, height );
            gradient.addColorStop( 0.0, Qt.rgba(0, 1 ,0, 1) );
            gradient.addColorStop( 1.0, Qt.rgba(0, 0 ,1, 1) );
            ctx.fillStyle = gradient;

            ctx.beginPath();
            //在路径上添加一串文本作为构成路径的元素之一
            ctx.text( "Fill Text on Path", 10, 50 );
            ctx.fill();

            //和text+fill一样
            ctx.fillText( "Fill Text", 10, 100 );

            ctx.beginPath();
            ctx.text( "Stroke Text on Path", 10, 150 );
            ctx.stroke();

            //和text+stroke一样
            ctx.strokeText( "Stroke Text", 10, 200 );

            ctx.beginPath();
            ctx.text("Stroke and Fill Text on Path", 10, 250);
            ctx.stroke();
            ctx.fill();
        }
    }
}
