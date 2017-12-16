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

        //paint在绘图(更新)时执行
        onPaint: {
            //Context2D是QML中负责2D图像的对象
            //有2种获取Context2D的方法：
            //1.getContext("2d");
            //2.设置对象的contextType属性，取值为"2d"
            var ctx = getContext("2d");
            ctx.lineWidth = 2;
            ctx.strokeStyle = "red";//线条为红色
            ctx.fillStyle = "blue";//矩形填充为蓝色

            //绘制的一般步骤：
            ctx.beginPath();//1.调用beginPath()
            ctx.rect(100, 80, 120, 80);//2.调用moveTo/lineTo/arcTo/rect/quadraticCurveTo等
            ctx.fill();//3.调用fill或stroke
            ctx.stroke();//4.路径绘制结束会调用strokeStyle保存颜色
        }
    }
}
