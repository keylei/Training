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

        //paint在绘图(更新)时执行
        onPaint: {
            //Context2D是QML中负责2D图像的对象
            //有2种获取Context2D的方法：
            //1.getContext("2d");
            //2.设置对象的contextType属性，取值为"2d"
            var ctx = getContext("2d");
            ctx.lineWidth = 2;
            ctx.strokeStyle = "red";//线条为红色

            //>>>----------------------------------------------------------------------------------------------------------
            //1. 设置线性渐变，并绘制矩形

            //在点(60,50)到（180,130）之间进行线性渐变，分别对应了矩形的左上角和右下角
            var gradient = ctx.createLinearGradient( 60, 50, 180, 130 );
            //添加渐变路径上关键点的颜色
            gradient.addColorStop( 0.0, Qt.rgba( 1, 0, 0, 1.0));
            gradient.addColorStop( 1.0, Qt.rgba( 0, 0, 1, 1.0));
            ctx.fillStyle = gradient;
            ctx.beginPath();
            ctx.rect(60,50,120,80);
            ctx.fill();
            ctx.stroke();

            //>>>----------------------------------------------------------------------------------------------------------
            //2. 设置环形渐变，并绘制矩形

            //起始圆中心点为(230,160),30为半径的圆，结束圆为(260.200),20为半径的圆
            //2个圆之间建立一个球形映射
            var gradient = ctx.createRadialGradient(230, 160, 30, 260, 200, 20);
            gradient.addColorStop( 0.0, Qt.rgba( 1, 0, 0, 1.0));
            gradient.addColorStop( 1.0, Qt.rgba( 0, 0, 1, 1.0));
            ctx.fillStyle = gradient;
            ctx.beginPath();
            ctx.rect(200,140,80,80);
            ctx.fill();
            ctx.stroke();

            //>>>----------------------------------------------------------------------------------------------------------
            //3. 绘制三角形
            ctx.beginPath();
            ctx.moveTo(100, 80);//2.调用moveTo/lineTo/arcTo/rect/quadraticCurveTo等
            ctx.lineTo(100,200);
            ctx.lineTo(300,200);
            ctx.closePath();
            ctx.fill();//3.调用fill或stroke
            ctx.stroke();//4.路径绘制结束会调用strokeStyle保存颜色
        }
    }
}
