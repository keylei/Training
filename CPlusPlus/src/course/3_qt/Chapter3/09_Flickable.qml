import QtQuick 2.2
import QtQuick.Controls 2.2

ApplicationWindow
{
    visible: true;
    width:800;
    height: 600;
    Flickable{
        id: flick;
        width: 200;
        height: 200;
        contentWidth: image.width;
        contentHeight: image.height;

        Image{
            id: image;
            source: "../Images/cat.jpeg";
        }
    }
}
