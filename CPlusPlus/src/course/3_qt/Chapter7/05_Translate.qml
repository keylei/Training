import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

ApplicationWindow
{
    visible: true;
    width: 1300;
    height: 800;

    property string localImgPath: "../Images/cat.jpeg";

    Canvas{
        anchors.fill: parent;
        contextType: "2d";
        property real imgWidth: 640;
        property real imgHeight: 335;

        onPaint: {
            context.lineWidth = 2;
            context.strokeStyle = "blue";
            context.fillStyle = Qt.rgba(0.3, 0.5, 0.7, 0.5);

            //关于变换细节见:
            //          http://doc.qt.io/qt-5/qml-qtquick-context2d.html#save-method

            //把当前的状态加入状态堆栈
            //当改变当前任何状态时，应该把保存当前的状态，context会维护一个绘制的状态堆栈，每一个
            //状态包含了变换矩阵，裁剪区域和其他相关属性
            context.save();
            context.translate(width/2, height/2); // 平移画布原点到中心点
            context.drawImage(localImgPath, -imgWidth/2, -imgHeight/2, imgWidth, imgHeight);//图片居中显示
            context.restore();//每次变换都要使用restore恢复原来的原点

            context.save();
            context.translate(width/2, 0);
            context.shear(0.6, 0);//左上角水平方向拉伸
            context.drawImage(localImgPath, 0, 0, imgWidth, imgHeight);//图片居中显示
            context.restore();

            context.save();
            context.translate(width/2, 0);
            context.shear(-0.6, 0);//右上角水平方向拉伸
            context.drawImage(localImgPath, -imgWidth/2, 0, imgWidth, imgHeight);//图片居中显示
            context.restore();

            //坐标系逆时针旋转60读时候在绘制
            context.save();
            context.translate(0, height/2);
            context.rotate(Math.PI / 3);
            context.drawImage(localImgPath, 0, -imgHeight/2, imgWidth, imgHeight);
            context.restore();

            //坐标系逆时针旋转90读时候在绘制
            context.save();
            context.translate(width/2, height/2);
            context.rotate(Math.PI/2);
            context.drawImage(localImgPath, imgWidth/2,-imgHeight/2, imgWidth, imgHeight);
            context.restore();

            context.save();
            //            object setTransform(real a, real b, real c, real d, real e, real f)
            //a: x方向缩放因子
            //b: y方向拉伸因子
            //c: x方向拉伸因子
            //d: y方向缩放因子
            //e: x方向的平移量
            //f: y方向的平移量
            context.setTransform(1, 0, 0, 1, 100, 100);
            context.drawImage(localImgPath, 0, 0, imgWidth/2, imgHeight/2);
            context.restore();
        }

        Component.onCompleted: loadImage(localImgPath);
        onImageLoaded: requestPaint();
    }
}
