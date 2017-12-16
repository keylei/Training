import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow
{
    visible: true;
    width: 1300;
    height: 800;

    property url localImgPath: "../Images/cat.jpeg";

    Canvas{
        contextType: "2d";
        anchors.fill: parent;

        onPaint: {
            context.lineWidth = 2;
            context.strokeStyle = "blue";
            context.fillStyle = Qt.rgba(0.3, 0.5, 0.7, 0.3);

            context.save();
            context.beginPath();
            //绘制一个扇形
            context.arc(180,150,80,0, Math.PI * 2, true);

            context.moveTo(180, 230);
            context.lineTo(420,280);
            context.lineTo(160,320);
            context.closePath();
            context.clip();

            //绘制图像(600,600)的区域到canvas(400,400)的范围内
            context.drawImage(localImgPath, 0,0 ,600, 600,400,400);//9个参数的重载总是报错
            context.stroke();
            context.fill();

            context.rotate(Math.PI/5);
            context.font = "italic bold 32px serif";
            context.fillStyle = "red";
            context.fillText("the text fill be clipped!", 100, 70);
            context.restore();
        }

        Component.onCompleted: loadImage(localImgPath);
        onImageLoaded: requestPaint();
    }
}
