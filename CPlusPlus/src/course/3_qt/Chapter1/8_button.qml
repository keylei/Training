import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Controls.Styles 1.4

ApplicationWindow {
    width:650;
    height:800;
    visible: true;

    Button{
        text: "Quit";
        anchors.centerIn: parent;
        checkable: true;//标示按钮是否可选
        Menu{ //允许给按钮设置一个菜单
            id: menu;
            title: "Edit"

            MenuItem {
                text: "Cut"
            }

            MenuItem {
                text: "Copy"
            }

            MenuItem {
                text: "Paste"
            }
        }

        onClicked: {
            menu.open();
        }
    }
}
