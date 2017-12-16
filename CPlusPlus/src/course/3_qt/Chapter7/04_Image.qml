import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3

//在Canvas的(0,0)位置绘制一张图像
//图像类型可以是一个Image，一个url或者一个CanvasImageData对象。
//1.当作为一个Image时，当Image没有完全加载时，不会绘制任何东西；
//2.当作为一个url时，图像首先被Canvas的loadImage调用，该方法会异步
//   记载图片，当图片记载完成时，发射imageLoaded信号。在imageLoaded
//   调用requestPaint方法来重绘Canvas。

ApplicationWindow
{
    visible: true;
    width: 800;
    height: 800;

    //>>>----------------------------------------------------------------------------------------------------------
    //1.混合使用本地图片和网络图片
    property url localImgPath: "../Images/cat.jpeg";
    property url urlImgPath: "http://tgi1.jia.com/109/975/9975117.jpg";

    //    Canvas{
    //        anchors.fill: parent;

    //        //注意: 这不是显示一张图片，显示图片使用Canvas就可以了，这是使用
    //        //Canvas绘制，可以在图片上进行绘制
    //        onPaint: {
    //            var ctx = getContext( "2d" );

    //            ctx.drawImage(localImgPath, 0, 0);
    //            ctx.drawImage(urlImgPath, 300, 300);
    //        }

    //        Component.onCompleted: {
    //            loadImage(localImgPath);
    //            loadImage(urlImgPath);
    //        }
    //        onImageLoaded: requestPaint();
    //    }

    //>>>----------------------------------------------------------------------------------------------------------
    //2.在Canvas中使用Image元素
    //    Canvas{
    //        id: canvas;
    //        anchors.fill: parent;

    //        Image{
    //            id: imgPoster;
    //            source: localImgPath;
    //            visible:  false;
    //            onStateChanged: {
    //                if( status == Image.Ready ){
    //                    canvas.requestPaint();
    //                }
    //            }
    //        }

    //        onPaint: {
    //            var ctx = getContext("2d");
    //            ctx.drawImage(imgPoster, 50, 0);
    //        }
    //    }

    //>>>----------------------------------------------------------------------------------------------------------
    //3.绘制CanvasImageData， 对象使用一维数组，按照RGBA的顺序来保存图像数据，
    //   它的width，height代表图像宽，高。data属性就是一维数组的字节数组
    Canvas{
        id: canvasRandom;
        width: 120;
        height: 100;
        contextType: "2d"; //这个使用getContext( "2d" )达到的是一样的效果

        property var imageData: null;

        onPaint: {
            if( imageData == null ){
                imageData = context.createImageData(120,100);

                var cnt = 48000;
                for (var i = 0; i < cnt; ++i) {
                    imageData.data[i] = Math.floor(Math.random()*255);
                    imageData.data[i+1] = Math.floor(Math.random()*255);
                    imageData.data[i+2] = Math.floor(Math.random()*255);
                    imageData.data[i+3] = 255;
                }
            }

            context.drawImage(imageData, 0, 0);
        }
    }

    Canvas{
        id: canvasImg;
        anchors.left: parent.left;
        anchors.top: canvasRandom.bottom;
        anchors.topMargin: 20;
        width: 200;
        height: 230;

        onPaint: {
            var ctx = getContext("2d");
            ctx.drawImage(localImgPath, 0, 0, width, height);
        }

        Component.onCompleted: loadImage(localImgPath);
        onImageLoaded: {
            requestPaint();
            canvasNegative.setImgData(getContext("2d").createImageData( "../Images/cat.jpeg"));
        }
    }

    Canvas{
        id: canvasNegative;
        anchors.left: canvasImg.right;
        anchors.leftMargin: 10;
        anchors.top:canvasImg.top;
        width: 200;
        height: 230;
        contextType: "2d";

        property var imgData: null;

        onPaint: {
            if( imgData !=null ){
                context.drawImage( imgData, 0, 0, width, height );
            }
        }

        function setImgData(data){
            imgData = data;
            var limit = data.width * data.height * 4;
            var cnt = limit ;
            for (var i = 0; i < cnt; i+=4) {
                //取反操作
                imgData.data[i] = 255 - data.data[i];
                imgData.data[i] = 255 - data.data[i+1];
                imgData.data[i] = 255 - data.data[i+2];
                imgData.data[i] = 255 - data.data[i+3];
            }
            requestPaint();
        }
    }
}
