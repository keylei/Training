import QtQuick 2.7
import QtQuick.Controls 2.0


ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;

    Button{
        text: "宿主对象Qt";
        onClicked:{
            //>>>----------------------------------------------------------------------------------------------------------
            //application属性
            console.log("application属性----------------------------------------------------------------");
            console.log(Qt.application.state);
            console.log(Qt.application.layoutDirection);
            console.log(Qt.application.name);

            //>>>----------------------------------------------------------------------------------------------------------
            //Qt对象
            console.log("Qt对象----------------------------------------------------------------");
            console.log(Qt.rect(0,0,2,2));
            console.log(Qt.point(1.1,2.2));
            console.log(Qt.size(1.2, 2.1));
            console.log(Qt.rgba(0.5,0.5,0.5,0.5));
            console.log(Qt.vector2d(1,2));
            console.log(Qt.vector3d(1,2,3));
            console.log(Qt.vector4d(1,1,2,1.1));
            console.log(Qt.quaternion(1,2,3,4));
            console.log(Qt.matrix4x4(1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4));

            var today = new Date();
            console.log(Qt.formatDateTime(today, "yyyy-MM-dd hh:mm:ss.zzz"));



            //Qt是QML提供的一个全局宿主对象，整合了常用的属性，方法和枚举对象
            //            Qt.quit();
        }
    }
}
