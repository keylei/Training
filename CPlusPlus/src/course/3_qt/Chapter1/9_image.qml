import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    width:1000;
    height:1000;
    visible: true;

    BusyIndicator{
        id: busyindic;
        running: true;
        anchors.centerIn: parent;
        z: 2;
    }

    Text{
        id: txtState;
        visible: false;
        anchors.centerIn: parent;
        z: 3;
    }

    Image{
        id: imgViewer;
        asynchronous: true; //开启异步加载模式，不会阻塞的加载图片
        cache: false;
        anchors.fill: parent;
//        fillMode: Image.P;

        onStateChanged: {
            if( imgViewer.status === Image.Loading ){
                busyindic.running = true;
                txtState.visible = false;
            }
            else if(imgViewer.state === Image.Ready){
                busyindic.running = false;
            }
            else if(imgViewer.state === Image.Error)
            {
                busyindic.running = false;
                txtState.visible = true;
                txtState.text = "Error";
            }
        }
    }

    Component.onCompleted: {
        //这个有个问题， 为什么imgViewer状态一直没有改变，一直打圈圈
        imgViewer.source = "https://img1.qunarzz.com/travel/d1/1611/4a/53a9dd64a9b185b5.jpg_r_720x480x95_79c67f81.jpg";
        console.log(imgViewer.state);
    }
}
